// Name:    Captain Calc
// Date:    September 6, 2021
// File:    main.cpp
// Purpose: This file tests the ReadOnlyMemory::Read() function.
//          It simply tests if the function can accurately read in bytes from
//          a file. We use a file because we can write the data we want to read
//          out.


// @runtests: This file allows the test to access the main program's functions.
#include "../../test_util.h"


#include <fileioc.h>
#include <tice.h>


void print_test_results(bool result);


int main(void)
{
  const uint8_t SIZE = 8;

  bool test_succeeded = true;
  uint8_t data[SIZE] = {'\0'};
  uint8_t expected_data[SIZE] = {
    0xf3, 0xed, 0x7e, 0x5b, 0xc3, 0x15, 0xe0, 0x00
  };
  ti_var_t slot;

  // Create an appvar and write the expected_data to it, so we can be certain
  // that it exists when we read it out again.
  if (!(slot = ti_Open("HexaTest", "w+")))
  {
    test_succeeded = false;
  }
  else
  {
    ti_Write(expected_data, sizeof(uint8_t), SIZE, slot);

    // Rewind the slot so that ti_GetDataPtr() points to the start of the data
    // we just wrote.
    ti_Rewind(slot);

    // Setup a new ReadOnlyMemory at the file's location and read out the data
    // we wrote.
    ReadOnlyMemory rom((uint8_t *)ti_GetDataPtr(slot), ti_GetSize(slot));
    rom.Read(data, 0, SIZE);

    // Verify that the data is the same.
    for (uint8_t i = 0; i < SIZE; i++)
    {
      if (data[i] != expected_data[i])
      {
        test_succeeded = false;
        break;
      }
    }

    // Cleanup
    ti_Close(slot);
    ti_Delete("HexaTest");
  }

#if DEBUG
  CCDBG_DUMP_INT(test_succeeded);
#endif
  
  print_test_results(test_succeeded);
  return 0;
}


void print_test_results(bool result)
{
  os_ClrHomeFull();

  if (result)
  {
    os_PutStrLine("True");
  }
  else
  {
    os_PutStrLine("False");
  }
  
  while (!os_GetCSC());
  return;
}
