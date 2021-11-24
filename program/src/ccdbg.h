// Name:    Captain Calc
// Date:    November 24, 2021
// File:    ccdbg.h
// Purpose: ccdbg provides macros for pretty-printing variable values.
// Version: 0.1.1


// CHANGE LOG
//
//   Version    Description
//     0.1.0    Added CCDBG_DUMP_BIN()
//     0.1.1    Added USE_CCDBG. This flag removes the necessity to put
//              #if NDEBUG \ #endif commands around debug statements. This was
//              necessary in version 0.1.0 if the programmer wanted to run
//              make without debug and leave the debugging statements in the
//              program code.
//


#ifndef CCDBG_H
#define CCDBG_H

#ifdef __cplusplus
extern "C" {
#endif


#include <string.h>  // For strlen()
#include <stdio.h>


#ifndef NDEBUG
  #define USE_CCDBG 1
#endif


#if USE_CCDBG

  #define dbgout ((char*)0xFB0000)
  #define dbgerr ((char*)0xFC0000)
  #define dbg_sprintf sprintf


  #define BLOCK_INDENT  4
  #define VALUE_INDENT 50
  extern unsigned int g_ccdbg_chkpt_indent;


  #define CCDBG_PRINT_CHKPT_INDENT                            \
    do {                                                      \
      for (unsigned int i = 0; i < g_ccdbg_chkpt_indent; i++) \
      {                                                       \
        ( (i && (!(i % BLOCK_INDENT))) ? dbg_sprintf(dbgout, "|") : dbg_sprintf(dbgout, "") ); \
        dbg_sprintf(dbgout, " ");                             \
      }                                                       \
      dbg_sprintf(dbgout, "|");                               \
    } while(0)


  #define CCDBG_CHKPT_START(name)                  \
    do {                                           \
      CCDBG_PRINT_CHKPT_INDENT;                    \
      dbg_sprintf(dbgout, "\n");                   \
      g_ccdbg_chkpt_indent += BLOCK_INDENT;        \
      CCDBG_PRINT_CHKPT_INDENT;                    \
      dbg_sprintf(dbgout, " %s()\n", name);        \
      CCDBG_PRINT_CHKPT_INDENT;                    \
      for (int i = VALUE_INDENT + 15; i > 0; i--)  \
      {                                            \
        dbg_sprintf(dbgout, "-");                  \
      }                                            \
      dbg_sprintf(dbgout, "\n");                   \
    } while (0)


  #define CCDBG_CHKPT_END                         \
    do {                                          \
      CCDBG_PRINT_CHKPT_INDENT;                   \
      for (int i = VALUE_INDENT + 15; i > 0; i--) \
      {                                           \
        dbg_sprintf(dbgout, "-");                 \
      }                                           \
      dbg_sprintf(dbgout, "\n");                  \
      g_ccdbg_chkpt_indent -= BLOCK_INDENT;       \
      CCDBG_PRINT_CHKPT_INDENT;                   \
      dbg_sprintf(dbgout, "\n");                  \
    } while (0)


  #define CCDBG_PRINT_SECTION_HEADER(name)   \
    do {                                     \
      CCDBG_PRINT_CHKPT_INDENT;              \
      dbg_sprintf(dbgout, "  %s\n", name);   \
    } while (0)


  #define CCDBG_PRINT_MSG(msg)            \
    do {                                  \
      CCDBG_PRINT_CHKPT_INDENT;           \
      dbg_sprintf(dbgout, "  %s\n", msg); \
    } while (0)


  #define CCDBG_DUMP_PTR(varname)                               \
    do {                                                        \
      CCDBG_PRINT_CHKPT_INDENT;                                 \
      dbg_sprintf(dbgout, "  %s", #varname);                    \
      for (int i = VALUE_INDENT - strlen(#varname); i > 0; i--) \
      {                                                         \
        dbg_sprintf(dbgout, " ");                               \
      }                                                         \
      dbg_sprintf(dbgout,"= 0x%6x\n", (unsigned int)varname);   \
    } while (0)


  #define CCDBG_DUMP_UINT(varname)                              \
    do {                                                        \
      CCDBG_PRINT_CHKPT_INDENT;                                 \
      dbg_sprintf(dbgout, "  %s", #varname);                    \
      for (int i = VALUE_INDENT - strlen(#varname); i > 0; i--) \
      {                                                         \
        dbg_sprintf(dbgout, " ");                               \
      }                                                         \
      dbg_sprintf(dbgout,"= %u\n", varname);                    \
    } while (0)


  #define CCDBG_DUMP_INT(varname)                               \
    do {                                                        \
      CCDBG_PRINT_CHKPT_INDENT;                                 \
      dbg_sprintf(dbgout, "  %s", #varname);                    \
      for (int i = VALUE_INDENT - strlen(#varname); i > 0; i--) \
      {                                                         \
        dbg_sprintf(dbgout, " ");                               \
      }                                                         \
      dbg_sprintf(dbgout,"= %d\n", varname);                    \
    } while (0)


  #define CCDBG_DUMP_STR(varname)                               \
    do {                                                        \
      CCDBG_PRINT_CHKPT_INDENT;                                 \
      dbg_sprintf(dbgout, "  %s", #varname);                    \
      for (int i = VALUE_INDENT - strlen(#varname); i > 0; i--) \
      {                                                         \
        dbg_sprintf(dbgout, " ");                               \
      }                                                         \
      dbg_sprintf(dbgout,"= %s\n", varname);                    \
    } while (0)


  #define CCDBG_DUMP_BIN(varname, type)                          \
    do {                                                         \
      CCDBG_PRINT_CHKPT_INDENT;                                  \
      dbg_sprintf(dbgout, "  %s", #varname);                     \
      for (int i = VALUE_INDENT - strlen(#varname); i > 0; i--)  \
      {                                                          \
        dbg_sprintf(dbgout, " ");                                \
      }                                                          \
      dbg_sprintf(dbgout, "= ");                                 \
      char b_char;                                               \
      for (int byte = sizeof(#type) - 1; byte > -1; byte--)      \
      {                                                          \
        b_char = ((varname & (1 << byte)) ? '1' : '0');          \
        dbg_sprintf(dbgout, "%c", b_char);                       \
        if (!(byte % 4))                                         \
        {                                                        \
          dbg_sprintf(dbgout, " ");                              \
        }                                                        \
      }                                                          \
      dbg_sprintf(dbgout,"\n");                                  \
    } while (0)

#else

  #define CCDBG_CHKPT_START(name)
  #define CCDBG_CHKPT_END
  #define CCDBG_PRINT_SECTION_HEADER(name)
  #define CCDBG_PRINT_MSG(msg)
  #define CCDBG_DUMP_PTR(varname)
  #define CCDBG_DUMP_UINT(varname)
  #define CCDBG_DUMP_INT(varname)
  #define CCDBG_DUMP_STR(varname)
  #define CCDBG_DUMP_BIN(varname, type)

#endif

#if __cplusplus
}
#endif

#endif
