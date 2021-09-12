// Name:    Captain Calc
// Date:    September 11, 2021
// File:    memory.cpp
// Purpose: 


#include <stdint.h>

#include "abc_memory.h"
#include "exception.h"
#include "memory.h"


void ReadOnlyMemory::Read(
  uint8_t *data,
  const uint24_t size,
  const uint24_t offset
)
{
  // <offset> must be cast to a int32_t because an uint24_t cannot fit into an
  // int24_t when <offset> is greater than or equal to 0x800000 (sets the MSB,
  // or sign bit).
  if (
    (offset > m_Size)
    || (size > m_Size)
    || ((int32_t)offset > ((int32_t)(m_Size - size)))
  )
  {
    Exception::Raise("ROM_READ_OUT_OF_BOUNDS");
    return;
  }

  ABC_ReadOnlyMemory::Read(data, size, offset);
  return;
}


uint8_t ReadOnlyMemory::ReadByte(const uint24_t offset)
{
  uint8_t byte;
  Read(&byte, 1, offset);
  return byte;
}


uint8_t ReadOnlyMemory::FindAll(
  uint8_t **matches,
  const uint8_t max_matches,
  const uint8_t seq[],
  const uint8_t len,
  const uint24_t offset,
  const uint24_t range
)
{
  uint8_t num_matches = 0;

  // Largest values allowed with preconditions fulfilled:
  //   <m_Size> = 0xffffff
  //   <offset> = 0xffffff
  //   <range>  = 0xffffff
  //   (<offset> + <range>) can be held in an uint32_t.

  if (offset > m_Size)
  {
    Exception::Raise("ROM_FIND_ALL_OUT_OF_BOUNDS");
    return 0;
  }

  num_matches = ABC_ReadOnlyMemory::FindAll(
    matches,
    max_matches,
    seq,
    len,
    offset,
    range
  );

  return num_matches;
}