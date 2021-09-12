// Name:    <name>
// Date:    <date>
// File:    <filename>
// Purpose: <description>


// @runtests: This file allows the test to access the main program's functions.
#include "../../test_util.h"


#include <tice.h>


void print_test_results(bool result);


int main(void)
{
  bool test_succeeded = true;
  
  
  // Put test code here...
  
  
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
