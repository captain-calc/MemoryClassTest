// Name:    Captain Calc
// Date:    September 5, 2021
// File:    main.cpp
// Purpose: Creates and tests the Memory-derived classes.


#include <stdint.h>
#include <stdlib.h>

#include "abc_memory.h"


int main(void)
{
  const uint8_t SIZE = 10;
  
  uint8_t data[SIZE] = {'\0'};
  ABC_ReadOnlyMemory rom(ROM_MIN_ADDRESS, ROM_SIZE);
  
  rom.Read(data, 0, SIZE);
  
  return 0;
}
