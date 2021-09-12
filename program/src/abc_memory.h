// Name:    Captain Calc
// Date:    September 9, 2021
// File:    abc_memory.h
// Purpose: This file provides the abstract data classes that represent
//          read-only, read-write, and "variable" memory.


// TYPES OF ABSTRACT MEMORY CLASSES
//
//     "read-only"  = Only allows reading bytes out of the memory.
//     "read-write" = Allows both reading from and writing to the memory.
//     "variable"   = Allows reading from, writing to, and inserting bytes into
//                    the memory.
//


#ifndef ABC_MEMORY_H
#define ABC_MEMORY_H


#include <stdint.h>


#define ROM_MIN_ADDRESS  ((uint8_t *)0x000000)
#define ROM_MAX_ADDRESS  ((uint8_t *)0x400000)
#define ROM_SIZE         ((size_t)ROM_MAX_ADDRESS)

#define RAM_MIN_ADDRESS  ((uint8_t *)0xd00000)
#define RAM_MAX_ADDRESS  ((uint8_t *)0xd65000)
#define RAM_SIZE         ((size_t)(RAM_MAX_ADDRESS - RAM_MIN_ADDRESS))

#define PORTS_MIN_ADDRESS  ((uint8_t *)0xe00000)
#define PORTS_MAX_ADDRESS  ((uint8_t *)0xffffff)
#define PORTS_SIZE         ((size_t)(PORTS_MAX_ADDRESS - PORTS_MIN_ADDRESS))


class ABC_ReadOnlyMemory
{
  protected:
    uint8_t *m_Addr;
    size_t m_Size;
    
  public:
    ABC_ReadOnlyMemory(uint8_t *addr, uint24_t size):
    m_Addr(addr), m_Size(size) {}
    
    virtual void Read(
      uint8_t *data,
      const uint24_t size,
      const uint24_t offset
    );
    virtual uint8_t ReadByte(const uint24_t offset);
    virtual uint8_t FindAll(
      uint8_t **matches,
      const uint8_t max_matches,
      const uint8_t seq[],
      const uint8_t len,
      const uint24_t offset,
      const uint24_t range
    );
    
    virtual ~ABC_ReadOnlyMemory() = default;
};


typedef struct
{
  uint24_t offset;
  uint24_t size;
} byte_seq_t;


class ABC_ReadWriteMemory: public ABC_ReadOnlyMemory
{
  protected:
    static const uint8_t m_MAX_NUM_WRITE_PROTECTED_ADDRS = 10;
    byte_seq_t *m_WriteProtectedAddrs[m_MAX_NUM_WRITE_PROTECTED_ADDRS];
    uint8_t m_NumWriteProtectedAddrs;
    bool m_IsSuperuser;

  public:
    ABC_ReadWriteMemory(uint8_t *addr, uint24_t size):
      ABC_ReadOnlyMemory(addr, size),
      m_NumWriteProtectedAddrs(0),
      m_IsSuperuser(false)
      {
        for (uint8_t i = 0; i < m_MAX_NUM_WRITE_PROTECTED_ADDRS; i++)
        {
          m_WriteProtectedAddrs[i] = nullptr;
        }
      }

/*
      // Derived versions will block writes to write-protected addresses unless
      // <m_Superuser> is true.
      virtual void Write(
        uint8_t *data,
        const uint24_t size,
        const uint24_t offset
      );
      virtual void WriteByte(uint8_t byte, const uint24_t offset);
      virtual void WriteNibble(const uint24_t offset, bool high_nibble);

      // Derived version will prevent adding address to a full array.
      virtual void AddWriteProtectedAddr(
        const uint24_t offset,
        const uint24_t size
      );
      void ActivateSuperuser() { m_IsSuperuser = true; };
      void DeactivateSuperuser() { m_IsSuperuser = false; };
*/

    virtual ~ABC_ReadWriteMemory() = default;
};


class ABC_VariableMemory : public ABC_ReadWriteMemory
{
  public:
    ABC_VariableMemory(uint8_t *addr, uint24_t size):
      ABC_ReadWriteMemory(addr, size) {}

/*
    void InsertBytes(
      const uint24_t size,
      const uint8_t value,
      const uint24_t offset
    );
    void DeleteBytes(const uint24_t size, const uint24_t offset);
*/

    virtual ~ABC_VariableMemory() = default;
};


#endif
