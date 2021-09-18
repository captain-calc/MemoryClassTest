# Contributing

## Introduction

**TODO**


## General Source Code Guidelines


All guidelines herein specified apply to both program code and test code.


### Line Length

Lines should be 80 characters or less.


### Tabs or Spaces in Source Code

All C/C++ files, including header files, should only use spaces. Code blocks should be indented with 2 spaces. Tabs should be used instead of spaces in assembly source files.


### Comments

All comments should use `//`. This restriction allows the programmer to comment out blocks of code or even entire functions with `/**/` without having worry about conflicts with other `/**/`-style comments.

There should be one space between the `//` and the rest of the comment for legibility.

Strictly avoid all "conversational" or otherwise useless comments. They obscure the code's clarity and are unprofessional.


### Comment Headers

Every source file should have a comment header. This header gives the name/pseudonym of the author, the date the file was last modified, the name of the file, and a short description of what the file is for.

The format of the comment header is as follows:
```
// Name:    ...
// Date:    ...
// File:    ...
// Purpose: ...
```

All fields should be lined up one space away from the longest line.


### Function Documentation

Every function declaration should have its documentation in the same source file. Documentation for regular functions should immediately precede the function declaration. Documentation for class member functions should go immediately above the class declaration and should be in the same order as the declarations.

Function documentation should have at least three parts: a description, preconditions, and postconditions. The description is a brief explanation of what the function does. The preconditions specify what must be true in order for the function to execute properly (specifying valid/invalid arguments, etc.). Postconditions state what will be true after the function executes, assuming that the preconditions have been met. If a functions preconditions are not met, the postconditions *cannot* be guaranteed.

The format for the function documentation is as follows:
```
// Description: ...
// Pre:         ...
// Post:        ...
```

All fields should be lined up one space away from the longest line.


### C++ Class Declarations

`private` precedes `protected` which precedes `public`.

All non-`const` class variables should have the prefix `m_`, the first letter of the variable capitalized, and the rest of the variable in camel-case. All `const` variables should be prefixed with `m_` and be in uppercase snake-case. The `m_` prefix helps the programmer identify which variables are member variables.


### `#define` and `#ifndef` Declarations

`#defines` and `#ifndefs` should be in uppercase snake-case.


### Global Variable Declarations

All global variables should be prefixed with `g_`. Non-`const` global variables should be in lowercase snake-case. `const` global variables should be in uppercase snake-case.


### Local Variable Declarations

All non-`const` variables should be in lowercase snake-case. `const` variables should be in uppercase snake-case.


## Tests


### Tests' Location

Tests should go into the tests/ directory.


### Test Naming

Test names follow this format:
`<test id>-<name of file that contains the function being tested>_<class name (if function is a member function)>_<function name>`

| **test-id**       | A unique two-digit number. This gives a unique id to each test in the list and orders the list of tests in a file explorer.
| **name of file**  | The name of the source file that contains the function's *declaration*.
| **class name**    | If the function is a member function, specify the class.
| **function name** | Name of the function.


