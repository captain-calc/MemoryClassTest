// Name:    Captain Calc
// Date:    November 24, 2021
// File:    ccdbg.cpp
// Purpose: ccdbg provides macros for pretty-printing variable values.
// Version: 0.1.1


// NOTE
//
//     Changing this file's extension from ".cpp" to ".c" breaks running
// "make debug" in each of the test directories. According to the compiliation
// record produced by make, "ccdbg.c" will not be compiled, but "ccdbg.cpp"
// will be.
//


#include "ccdbg.h"

#if USE_CCDBG

unsigned int g_ccdbg_chkpt_indent = 0;

#endif