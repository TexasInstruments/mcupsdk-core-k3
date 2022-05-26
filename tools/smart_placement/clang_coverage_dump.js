var scriptEnv = Packages.com.ti.ccstudio.scripting.environment.ScriptingEnvironment.instance();
var server = scriptEnv.getServer("DebugServer.1");
var session = server.openSession("Texas Instruments XDS110 USB Debug Probe_0/MAIN_Cortex_R5_0_0");

session.target.halt();

var cntStart = session.symbol.getAddress("__start___llvm_prf_cnts");
var cntStop = session.symbol.getAddress("__stop___llvm_prf_cnts");

var cntContent = session.memory.readData(0, cntStart, 8, cntStop - cntStart);

var executable = session.symbol.getSymbolFileName();
var outFile = new Packages.java.io.RandomAccessFile(executable + ".cnt" , "rw");

outFile.setLength(0);
for each (var val in cntContent) {
    outFile.writeByte(Number(val));
}
outFile.close();
