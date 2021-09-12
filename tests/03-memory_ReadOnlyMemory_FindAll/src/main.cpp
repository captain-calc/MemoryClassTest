// Name:    Captain Calc
// Date:    September 11, 2021
// File:    main.cpp
// Purpose: This file tests the ReadOnlyMemory::FindAll() function on edge
//          cases and for returning the proper number of matches.


// @runtests: This file allows the test to access the main program's functions.
#include "../../test_util.h"


#include <fileioc.h>
#include <tice.h>


// The maximum length of a byte sequence.
#define MAX_SEQ_LEN 8


// A simple class to hold the expected value of matches given certain arguments
// to the FindAll() class. All members are public for easy access.
class SeqMatches
{
  public:
    SeqMatches(
      uint8_t len,
      uint24_t offset,
      uint24_t range,
      uint8_t num_matches,
      uint8_t seq[]
    ):
      m_Len(len),
      m_Offset(offset),
      m_Range(range),
      m_NumMatches(num_matches)
      {
        for (uint8_t i = 0; i < len; i++)
          m_Seq[i] = seq[i];
      }

    uint8_t m_Len;
    uint24_t m_Offset;
    uint24_t m_Range;
    uint8_t m_NumMatches;
    uint8_t m_Seq[MAX_SEQ_LEN];
};


void print_test_results(bool result);


int main(void)
{
  // This test uses an old version of HexaEdit as a controlled data source. The
  // autotester transfers this program when running the test.


  const uint8_t NUM_DATA = 6;

  bool test_succeeded = true;
  ti_var_t slot;

  // The byte sequences that FindAll() will be looking for.
  uint8_t seq_one[] = {0xef, 0x7b};
  uint8_t seq_two[] = {0xff, 0xff};
  uint8_t seq_three[] = {0x48, 0x65, 0x78, 0x61, 0x45, 0x64, 0x69, 0x74};

  // Only created because FindAll() requires an uint8_t * array.
  const uint8_t MAX_NUM_MATCHES = 255;
  uint8_t *matches[MAX_NUM_MATCHES] = {nullptr};

  uint8_t num_matches;

  // Counter variable
  uint8_t data_num = 0;


#if DEBUG
  CCDBG_CHKPT_START("main");
#endif

  
  if ((slot = ti_OpenVar("HEXAEDIT", "r", TI_PPRGM_TYPE)))
  {

    // First, start-to-end memory search.
    SeqMatches seq_match_one(2, 0, ti_GetSize(slot),   3, seq_one);

    // Second, the same type but longer search.
    SeqMatches seq_match_two(2, 0, ti_GetSize(slot), 172, seq_two);

    // Third, offset in the middle of the file and loop around to start of the
    // memory, ending at the offset.
    SeqMatches seq_match_three(2, 30000, ti_GetSize(slot), 3, seq_one);

    // Fourth, offset in the middle of the file and loop around to start of the
    // memory, ending before the offset.
    SeqMatches seq_match_four(8, 30000, 2000, 2, seq_three);

    // Fifth, a <range> that when added to valid <offset> overflows an
    // uint24_t.
    SeqMatches seq_match_five(2, 30000, 0xffffff, 3, seq_one);

    // Sixth, offset outside of the file. The maximum file size on the CE is
    // ~65,000, so 70,000 is definitely outside of the file.
    SeqMatches seq_match_six(2, 70000, 2000, 0, seq_one);

    SeqMatches *data[NUM_DATA] = {
      &seq_match_one,
      &seq_match_two,
      &seq_match_three,
      &seq_match_four,
      &seq_match_five,
      &seq_match_six
    };

    ReadOnlyMemory rom((uint8_t *)ti_GetDataPtr(slot), ti_GetSize(slot));

    while (data_num < NUM_DATA - 1)
    {
      num_matches = rom.FindAll(
        matches,
        MAX_NUM_MATCHES,
        data[data_num]->m_Seq,
        data[data_num]->m_Len,
        data[data_num]->m_Offset,
        data[data_num]->m_Range
      );

#if DEBUG
  CCDBG_DUMP_INT(num_matches);
  CCDBG_DUMP_INT(data[data_num]->m_NumMatches);
#endif

      if (num_matches != data[data_num]->m_NumMatches)
      {
        test_succeeded = false;
        break;
      }

      data_num++;
    }

    // Run the sixth test only if the first five ran successfully.
    if (test_succeeded)
    {
      num_matches = rom.FindAll(
        matches,
        MAX_NUM_MATCHES,
        data[data_num]->m_Seq,
        data[data_num]->m_Len,
        data[data_num]->m_Offset,
        data[data_num]->m_Range
      );

      if (Exception::Catch())
      {
        if (Exception::Is("ROM_FIND_ALL_OUT_OF_BOUNDS"))
          test_succeeded = true;
      }
    }

    // Cleanup
    ti_Close(slot);
    //ti_DeleteVar("HEXAEDIT", TI_PPRGM_TYPE);
  }


#if DEBUG
  CCDBG_DUMP_INT(test_succeeded);
  CCDBG_CHKPT_END;
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
