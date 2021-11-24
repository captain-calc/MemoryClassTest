// Name:    Captain Calc
// Date:    September 11, 2021
// File:    abc_memory.cpp
// Purpose: This file provides the definitions of the class member functions
//          declared in abc_memory.h.


#include <stdint.h>

#include "ccdbg.h"
#include "abc_memory.h"
#include "asmutil.h"


void ABC_ReadOnlyMemory::Read(
  uint8_t *data,
  const uint24_t size,
  const uint24_t offset
)
{
  uint8_t *offset_addr = m_Addr + offset;

CCDBG_CHKPT_START("ABC_ReadOnlyMemory::Read");
CCDBG_DUMP_PTR(offset_addr);
CCDBG_DUMP_UINT(offset);
CCDBG_DUMP_UINT(size);
CCDBG_CHKPT_END;
  
  for (size_t i = 0; i < size; i++)
  {
    data[i] = offset_addr[i];
  }
  
  return;
}


uint8_t ABC_ReadOnlyMemory::ReadByte(const uint24_t offset)
{
  uint8_t byte;
  Read(&byte, 1, offset);
  return byte;
}


uint8_t ABC_ReadOnlyMemory::FindAll(
  uint8_t **matches,
  const uint8_t max_matches,
  const uint8_t seq[],
  const uint8_t len,
  const uint24_t offset,
  const uint24_t range
)
{
  uint8_t num_matches = 0;
  uint24_t range_from_start;


CCDBG_CHKPT_START("ABC_ReadOnlyMemory::FindAll");
CCDBG_DUMP_PTR(matches);

  // Case 1: (<offset> + <range>) <= memory size
  // The <range> can be wildly irrational, but the <offset> will be less than
  // <m_Size>, thus this comparison must be written so:
  if (range <= (m_Size - offset))
  {

CCDBG_PRINT_MSG("Case 1");
CCDBG_DUMP_PTR(m_Addr + offset);
CCDBG_DUMP_PTR(m_Addr + range);

    num_matches = asm_BFind_All(
      m_Addr + offset,
      m_Addr + range,
      seq,
      len,
      matches,
      max_matches
    );
  }
  else
  {
    // Case 2: (<offset> + <range>) > m_Size

CCDBG_PRINT_MSG("Case 2");
CCDBG_DUMP_PTR(m_Addr + offset);
CCDBG_DUMP_PTR(m_Addr + m_Size);

    num_matches = asm_BFind_All(
      m_Addr + offset,
      m_Addr + m_Size,
      seq,
      len,
      matches,
      max_matches
    );

    range_from_start = range - (m_Size - offset);

    // Case 2a: <range_from_start> < <offset>
    // Loop around to the start of the memory and end before the <offset>.
    if (range_from_start < offset)
    {

CCDBG_PRINT_MSG("Case 2a");
CCDBG_DUMP_PTR(m_Addr);
CCDBG_DUMP_PTR(m_Addr + range_from_start);

      num_matches += asm_BFind_All(
        m_Addr,
        m_Addr + range_from_start,
        seq,
        len,
        matches,
        max_matches
      );
    }
    else
    {
      // Case 2b: <range_from_start> > <offset>
      // Loop around to the start of memory and end at the <offset>.

CCDBG_PRINT_MSG("Case 2b");
CCDBG_DUMP_PTR(m_Addr);
CCDBG_DUMP_PTR(m_Addr + offset - 1);

      num_matches += asm_BFind_All(
        m_Addr,
        m_Addr + offset - 1,
        seq,
        len,
        matches,
        max_matches
      );
    }
  }

CCDBG_CHKPT_END;

  return num_matches;
}