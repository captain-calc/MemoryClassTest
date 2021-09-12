// Name:    Captain Calc
// Date:    September 9, 2021
// File:    memory.h
// Purpose: 


#ifndef MEMORY_H
#define MEMORY_H


#include "abc_memory.h"


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