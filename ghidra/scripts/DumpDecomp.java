// Dump every function's decompilation to the file named in arg 0.
//@category DOS
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import java.io.*;
public class DumpDecomp extends GhidraScript {
    public void run() throws Exception {
        DecompInterface di = new DecompInterface(); di.openProgram(currentProgram);
        try (PrintWriter w = new PrintWriter(new FileWriter(getScriptArgs()[0]))) {
            for (Function fn : currentProgram.getFunctionManager().getFunctions(true)) {
                DecompileResults r = di.decompileFunction(fn, 30, monitor);
                w.println("//// " + fn.getName() + " @ " + fn.getEntryPoint());
                w.println(r.getDecompiledFunction() != null ? r.getDecompiledFunction().getC() : "// FAILED");
            }
        }
    }
}
