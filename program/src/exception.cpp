// TODO: Add comment header


#include <string.h>

#include "exception.h"

Exception Exception::instance;
bool Exception::m_Fresh(false);
char Exception::m_Msg[] = {'\0'};


void Exception::Raise(const char *msg)
{
  m_Fresh = true;

  // Plus 1 to include the NULL character.
  strncpy(m_Msg, msg, strlen(msg) + 1);

  return;
}


bool Exception::Catch()
{
  bool fresh = m_Fresh;
  m_Fresh = false;
  return fresh;
}


bool Exception::Is(const char *msg)
{
  return !strncmp(m_Msg, msg, strlen(msg));
}