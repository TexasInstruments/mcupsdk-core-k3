"""
Copyright (C) 2025 Texas Instruments Incorporated

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

    Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the
    distribution.

    Neither the name of Texas Instruments Incorporated nor the names of
    its contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
"""
# gen_data.py - Generate Input/Output data for FFT2D DSP offload example
import numpy as np
import struct
import os
import argparse

def generate_complex_data(rows, cols):
    """Generate complex float test data"""
    # Create random complex data
    real_part = np.random.random((rows, cols)).astype(np.float32)
    imag_part = np.random.random((rows, cols)).astype(np.float32)
    return real_part + 1j * imag_part


def save_complex_to_binary(data, filename):
    """Save complex float data to binary file in a C-readable format

    Format: Interleaved real and imaginary parts as float32
    [real0, imag0, real1, imag1, ...]
    """
    # Ensure directory exists
    os.makedirs(os.path.dirname(filename), exist_ok=True)

    # Open file for binary write
    with open(filename, "wb") as f:
        # Write interleaved real/imaginary data as flat array
        flat_data = data.flatten()
        for complex_val in flat_data:
            f.write(struct.pack("ff", complex_val.real, complex_val.imag))

    print(f"Saved {data.shape} complex matrix to {filename}")
    print(f"File size: {os.path.getsize(filename)} bytes")

    # Debug: Verify the first few values were written correctly
    with open(filename, "rb") as f:
        # Read first few complex values
        print("Debug - First 3 values written:")
        for i in range(3):
            real, imag = struct.unpack("ff", f.read(8))
            print(
                f"  {i}: {real} + {imag}j (Expected: {data.flatten()[i].real} + {data.flatten()[i].imag}j)"
            )


def load_complex_from_binary(filename, rows, cols):
    """Load complex float data from binary file"""
    print(f"Reading {rows}x{cols} complex matrix from {filename}")

    with open(filename, "rb") as f:
        # Create complex data array
        complex_data = np.zeros((rows, cols), dtype=np.complex64)

        # Read complex values directly into flattened array
        flat_data = complex_data.ravel()  # Use ravel() to get a view, not a copy
        for i in range(len(flat_data)):
            real, imag = struct.unpack("ff", f.read(8))
            flat_data[i] = complex(real, imag)

            # Debug: Print first few values
            if i < 3:
                print(f"  Read value {i}: {real} + {imag}j")

        return complex_data


def perform_2d_fft_row_col(input_data):
    """Perform 2D FFT using row-column approach (FFT -> Transpose -> FFT)"""
    # Step 1: FFT on rows
    temp = np.zeros_like(input_data)
    for i in range(input_data.shape[0]):
        temp[i, :] = np.fft.fft(input_data[i, :])

    # Step 2: Transpose
    temp = temp.T

    # Step 3: FFT on columns (now rows after transpose)
    output = np.zeros_like(temp)
    for i in range(temp.shape[0]):
        output[i, :] = np.fft.fft(temp[i, :])

    return output


def main():
    # Parameters
    parser = argparse.ArgumentParser(description="Generate complex float test data")
    parser.add_argument("--rows", type=int, required=True, help="Number of rows")
    parser.add_argument("--cols", type=int, required=True, help="Number of columns")
    args = parser.parse_args()

    rows = args.rows
    cols = args.cols
    input_file = "data/fft2d_input.bin"
    output_file = "data/fft2d_output.bin"

    # Create data directory if it doesn't exist
    os.makedirs("data", exist_ok=True)

    print(f"Generating {rows}x{cols} complex data matrix...")

    # Generate input data
    input_data = generate_complex_data(rows, cols)

    # Save input data
    save_complex_to_binary(input_data, input_file)

    # Perform 2D FFT using row-column approach
    print("\nPerforming 2D FFT using row-column approach (FFT -> Transpose -> FFT)...")
    output_data = perform_2d_fft_row_col(input_data)

    # Save output data
    save_complex_to_binary(output_data, output_file)

    # Verify by loading the saved files
    print("\nVerifying data loading...")
    input_loaded = load_complex_from_binary(input_file, rows, cols)
    output_loaded = load_complex_from_binary(output_file, rows, cols)

    print("\nVerification results:")
    input_match = np.allclose(input_data, input_loaded)
    print(f"Input data loaded correctly: {input_match}")
    if not input_match:
        # Show a few values for comparison
        print("Input comparison (first 3 values):")
        for i in range(3):
            orig = input_data.flatten()[i]
            loaded = input_loaded.flatten()[i]
            print(
                f"  Original: {orig.real:.6f} + {orig.imag:.6f}j, Loaded: {loaded.real:.6f} + {loaded.imag:.6f}j"
            )

    output_match = np.allclose(output_data, output_loaded)
    print(f"Output data loaded correctly: {output_match}")

    # Print sample values
    print("\nSample input values:")
    print(input_data[0:2, 0:2])

    print("\nSample input loaded values:")
    print(input_loaded[0:2, 0:2])

    print("\nSample output values:")
    print(output_data[0:2, 0:2])

    print("\nSample output loaded values:")
    print(output_loaded[0:2, 0:2])


if __name__ == "__main__":
    main()