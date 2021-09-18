// Name:    Captain Calc
// Date:    September 18, 2021
// File:    memory.h
// Purpose: This file declares the derived wrapper classes for the base classes
//          declared in abc_memory.h.


#ifndef MEMORY_H
#define MEMORY_H


#include "abc_memory.h"


// Description: ReadOnlyMemory (parameterized constructor) creates a new
//              instance of the class.
// Pre:         <addr> + <size> must not overflow and both variables must
//              correspond to a valid memory area.
// Post:        New instance of ReadOnlyMemory created.


// Description: Read() reads a number of bytes from an offset in the memory
//              area.
// Pre:         <offset> should be less than or equal to the memory size.
//              <offset> + <size> should not extend beyond the memory area.
//              <size> should be equal to or less than the size of <data>.
// Post:        If successful, <size> bytes read from <offset> into <data>.
//              Otherwise, exception raised.


// Description: ReadByte() reads a byte from an offset in the memory area.
// Pre:         <offset> should be less than or equal to the memory size - 1.
// Post:        If successful, byte at <offset> returned.
//              Otherwise, exception raised.


// Description: FindAll() finds a byte sequence in a memory range within the
//              memory area starting at an offset.
// Pre:         <max_matches> must be the size of the <matches> array.
//              <len> must be the size of the <seq> array.
//              <offset> should be less than the memory size.
// Post:        If successful, <matches> holds pointers to all matching byte
//              sequences in the given range of memory and the number of
//              pointers in <matches> returned.
//              Otherwise, exception raised.


// Description: ~ReadOnlyMemory() destroys a ReadOnlyMemory instance.
// Pre:         None
// Post:        Class instance destroyed.


class ReadOnlyMemory: public ABC_ReadOnlyMemory
{
  public:
    ReadOnlyMemory(uint8_t *addr, uint24_t size):
    ABC_ReadOnlyMemory(addr, size) {}

    void Read(
      uint8_t *data,
      const uint24_t offset,
      const uint24_t size
    );
    uint8_t ReadByte(const uint24_t offset);
    uint8_t FindAll(
      uint8_t **matches,
      const uint8_t max_matches,
      const uint8_t seq[],
      const uint8_t len,
      const uint24_t offset,
      const uint24_t range
    );
    
    ~ReadOnlyMemory() {}
};

#endif