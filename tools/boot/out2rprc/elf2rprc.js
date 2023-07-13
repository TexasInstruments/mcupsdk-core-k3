// Copyright (c) 2022-2023, Texas Instruments Incorporated
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// *  Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// *  Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// *  Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.)

const fs        = require('fs');
const path      = require('path');
const commander = require('commander');
const et        = require('elf-tools');
const pkg       = require('./package.json');

const fileHdrSize  = 20;
const rangeHdrSize = 20;
const version      = 1;
const reserved     = 0;
const roundup4     = (val) => Math.ceil(val/4)*4;

//------------------------------------------------------------------------------
// Main routine
//------------------------------------------------------------------------------
commander.program
    .description('Convert an Elf file to an RPRC file.')
    .version (pkg.version)
    .argument('<elfFile>',  'The input ELF (.out) file')
    .argument('[rprcFile]', 'The output RPRC (.rprc) file')
    //.option  ('-e, --bigEndian', 'Generate a Big Endian RPRC file', false)
    .action  ((elfFile, rprcFile, opts) => elf2rprc(elfFile, rprcFile, opts.bigEndian))
    .parse   ();

//------------------------------------------------------------------------------
// Convert an ELF file to an RPRC file
//------------------------------------------------------------------------------
function elf2rprc(elfFile, rprcFile, bigEnd=false)
{
    try {
        if (!rprcFile) rprcFile = path.parse(elfFile).name + '.rprc';
        fs.mkdirSync(path.dirname(rprcFile), {recursive:true});

        const elfRaw = fs.readFileSync(elfFile);
        const elf    = et.parse(elfRaw);
        const fdo    = fs.openSync(rprcFile, 'w');
        const write4 = bigEnd ? 'writeUInt32BE' : 'writeUInt32LE';

        // Eliminate memory ranges with uninitialized data and sort by address.
        const ranges = elf.programs
            .filter((x)=> x.header.filesz)
            .sort((a,b)=> a.header.paddr - b.header.paddr) ;

        // Write the RPRC File Header
        const fileHdr = Buffer.alloc(fileHdrSize);
        fileHdr.write('RPRC');                 // magic word
        fileHdr[write4](elf.header.entry, 4);  // entry point
        fileHdr[write4](reserved,         8);  // reserved
        fileHdr[write4](ranges.length,   12);  // segment count
        fileHdr[write4](version,         16);  // version
        fs.writeSync(fdo, fileHdr, 0, fileHdrSize);

        // Write the range Header and range Content for each range
        for (const rng of ranges) {
            const rangeSize = roundup4(rng.header.filesz);
            const rangeAddr = rng.header.paddr;
            const sectHdr   = Buffer.alloc(rangeHdrSize);
            const sectData  = Buffer.alloc(rangeSize);
            rng.data.copy(sectData);

            sectHdr[write4](rangeAddr,   0);  // segment run address
            sectHdr[write4](reserved,    4);  // reserved
            sectHdr[write4](rangeSize,   8);  // section size
            sectHdr[write4](reserved,   12);  // reserved
            sectHdr[write4](reserved,   16);  // reserved
            fs.writeSync(fdo, sectHdr,  0, rangeHdrSize);
            fs.writeSync(fdo, sectData, 0, rangeSize);
        }

        fs.closeSync(fdo);

    } catch(e) {
        console.error(e.message);
        process.exit(1);
    }
}