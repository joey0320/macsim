#include <iostream>
#include <fstream>
#include "pin.H"

using std::cerr;
using std::ofstream;
using std::ios;
using std::string;
using std::endl;


ofstream OutFile;

static UINT64 icount = 0;

VOID docount() { icount++; }

// pin calls this function every time a new instruction is executed
VOID Instruction(INS ins, VOID *v) {
  // Insert a call to docount before every instruction, no arguments are passed
  INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)docount, IARG_END);
}

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
    "o", "inscount.out", "specify output file name");

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v) {
  OutFile.setf(ios::showbase);
  OutFile << "count" << icount << endl;
  OutFile.close();
}

INT32 Usage() {
  cerr << "This tool counts the number of dynamic instructions executed" << endl;
  cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
  return -1;
}

int main (int argc, char * argv[]) {
  // initialize pin
  if (PIN_Init(argc, argv))
    return Usage();

  OutFile.open(KnobOutputFile.Value().c_str());

  // register callback to be called to instrument instructions
  INS_AddInstrumentFunction(Instruction, 0);

  // register fini to be called when the application exits
  PIN_AddFiniFunction(Fini, 0);

  // start the program
  PIN_StartProgram();

  return 0;
}
