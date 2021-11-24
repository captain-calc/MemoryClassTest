// Name:    Captain Calc
// Date:    September 11, 2021
// File:    main.cpp
// Purpose: This test checks edge cases for the ReadOnlyMemory::Read()
//          function.


// @runtests: This file allows the test to access the main program's functions.
#include "../../test_util.h"


#include <stdint.h>

#include <tice.h>


void print_test_results(bool result);


int main(void)
{
  const uint8_t SIZE = 10;

  bool test_succeeded = false;
  uint8_t data[SIZE] = {'\0'};
  
  // Use the "Ports" memory to test edge cases since anything above its max
  // address (0xffffff) will overflow.
  ReadOnlyMemory rom(PORTS_MIN_ADDRESS, PORTS_SIZE);
  

CCDBG_PRINT_MSG("First Ports read");


  // First, an irrational offset.
  rom.Read(data, 16777215, SIZE);

  if (Exception::Catch())
  {
    if (Exception::Is("ROM_READ_OUT_OF_BOUNDS"))
      test_succeeded = true;
  }


CCDBG_DUMP_INT(test_succeeded);
CCDBG_PRINT_MSG("Second Ports read");

  // Second, a rational offset and a rational size that sum to an irrational
  // read location.
  rom.Read(data, ((uint24_t)(PORTS_MAX_ADDRESS - 5)), SIZE);

  if (Exception::Catch())
  {
    if (Exception::Is("ROM_READ_OUT_OF_BOUNDS"))
      test_succeeded = test_succeeded & true;
  }

  // Note that we do not test for an irrational <SIZE>. This is because
  // Read()'s precondition states that <SIZE> should be the size of <data>. If
  // preconditions cannot be fullfilled with absolute certainity, the function
  // should not be called.
  

  // Test a custom range encompassing 0x000000 to 0xd00000 to test the event
  // that both the offset and the size are valid, but their sum results in an
  // overflow. This is the same as the previous test, but this one focuses on
  // checking for overflow cases in the operations used to determine invalid
  // reads.
  ReadOnlyMemory rom_two(((uint8_t *)0x000000), ((uint24_t)0xd00000 - 0x000000));


CCDBG_DUMP_INT(test_succeeded);
CCDBG_PRINT_MSG("First custom read");


  // 0xc00000 < 0xd00000, so the offset is valid.
  // 0xc00000 as <SIZE> is also valid.
  rom_two.Read(data, (uint24_t)0xc00000, (uint24_t)0xc00000);

  if (Exception::Catch())
  {
    if (Exception::Is("ROM_READ_OUT_OF_BOUNDS"))
      test_succeeded = test_succeeded & true;
  }


CCDBG_DUMP_INT(test_succeeded);


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
