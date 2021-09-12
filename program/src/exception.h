// Name:    Captain Calc
// Date:    September 11, 2021
// File:    exception.h
// Purpose: This file declares the Exception class, a work-around for the
//          unavailable built-in try-throw-catch functionality of C++.


// NOMENCLATURE
//
//     Since this Exception class is a work-around for another common C++
// feature, we must define what we mean when we use terms borrowed from the
// actual feature to describe the Exception class.
//
// "exception"            - An error identified by the function.
// "raising an exception" - Storing an error message in the Exception singleton
//                          and setting the <m_Fresh> flag.
//


// RECOMMENDED USAGE
//
//     Error messages should be in snake-case and all capital letters. Is()
// functions should be nested in a Catch() function like so:
//
//
// uint8_t divide(uint8_t a, uint8_t b)
// {
//   if (b == 0)
//   {
//     exception.Raise("DIVIDE_BY_0");
//     return;
//   }
//
//   return a / b;
// }
//
//
// int main()
// {
//   divide();
//  
//   if (exception.Catch())
//   {
//     if (exception.Is("DIVIDE_BY_0"))
//       cout << "Division by zero is illegal." << endl;
//
//       // Handle other exceptions if necessary.
//
//       // Put a debug print function at the end of the series of Is()'s
//       // so if an unhandled exception occurs, you will be notified.
//       return 1;
//   }
//
//   return 0;
// }
//
//
//     If a function raises an exception, any return values from the function
// should be considered meaningless.
//


#ifndef EXCEPTION_H
#define EXCEPTION_H


#include <stdint.h>

// Description: Exception() (default constructor) initializes the Exception
//              class.
// Pre:         None
// Post:        <m_Fresh> set to false.
//              <m_Msg> initialized as null array.


// Description: Raise() changes the error message and sets <m_Fresh> so that
//              it will be caught by the next Catch().
// Pre:         Size of <msg> must be less than <m_MSG_SIZE>.
// Post:       <m_Fresh> set.
//             <m_Msg> set to <msg>.


// Description: Catch() determines if a fresh exception has occurred and resets
//              <m_Fresh> so that the exception appears as handled.
// Pre:         None
// Post:        <m_Fresh> reset.
//              Value of <m_Fresh> before reset returned.


// Description: Is() determines if the specified <msg> matches the error
//              message of the exception.
// Pre:         The message comparison is case-sensitive.
// Post:        True returned if messages match.
//              False returned if messages do not match.


class Exception
{
  private:
    static const uint8_t m_MSG_SIZE = 30;
    static bool m_Fresh;
    static char m_Msg[m_MSG_SIZE];
    static Exception instance;

    Exception() {}
    ~Exception() {}

  public:
    static void Raise(const char *msg);
    static bool Catch();
    static bool Is(const char *msg);
};

#endif