

import os
from sys import argv
import time


TEST_UTIL_FILENAME: str        = "test_util.h"
RUNTESTS_COMMENT_PREFIX: str = "// @runtests"
RUNTESTS_SKIP_LINE: str      = "@runtests-skip-line"


def add_test_util_include(abs_file_path: str, depth: int) -> None:
    """
    Prepends the test_util.h include directive to the test's main file.
    
    test_util.h is in the tests/ directory. It includes all of the header
    files in the program's root src/ directory so that the tests will have
    access to the program's functions (If they did not have this access, they
    could not test the functions at all.).
    
    The include directive is written after any comment headers and before the
    rest of the code.
    
    Pre:  <abs_file_path> should be absolute system path to file, including file
          name.
          <depth> must be the number of directories that separate the test's
          root directory from the program's "tests/" directory.
    """
    
    lines: list[str] = []
    line_num: int = 0
    directive_nonexistant: bool = True
    spurious_include_found: bool = False
    
    
    with open(abs_file_path, "r+") as f:
        lines = f.readlines()
        
        # Skip the comment header.
        while lines[line_num].startswith("//"):
            line_num += 1
        
        # Skip any blank lines.
        while lines[line_num] == '\n':
            line_num += 1

        # Build the "#include" directive.
        include_directive: str = "#include \"" + ("../" * depth) \
                                 + TEST_UTIL_FILENAME + "\"\n"

        # If the "#include" directive does not exist or is an old one, write
        # new one.
        if lines[line_num].startswith(RUNTESTS_COMMENT_PREFIX):
            line_num += 1
            
            # Do not delete the "old" directive if it does not include the
            # TEST_UTIL_FILENAME.
            if lines[line_num].find(TEST_UTIL_FILENAME) != -1:
                if (lines[line_num].strip() != include_directive.strip()):
                    del lines[line_num]
                else:
                    directive_nonexistant = False
        else:
            lines.insert(
                line_num,
                RUNTESTS_COMMENT_PREFIX
                + ": This file allows the test to access the main program's " \
                "functions.\n",
            )
            
            line_num += 1
            
            # Insert two blank lines between the "#include" directive and the
            # rest of the code.
            lines.insert(line_num, '\n')
            lines.insert(line_num + 1, '\n')
    
    # Preserve line_num so we can write the directive after searching the rest
    # of the file.
    include_dir_line_num = line_num
    
    # If the file is perfect, the correct #include will occur at line_num.
    # Increment it so that the spurious #include detection code does not delete
    # it.
    line_num += 1
    
    # Search the rest of the file for spurious test_util.h includes and
    # delete them. If a user is including their own file with the same
    # name as the autotester's include file, they can put the
    # AUTOTESTER_SKIP_LINE directive on the line above the include to
    # keep it from being deleted.
    while line_num < len(lines) - 1:
    
        # Deleting a line from the list "moves" line_num forward without its
        # value having to change.
        if lines[line_num].startswith("#include \"") and lines[line_num].find(TEST_UTIL_FILENAME) != -1:
            del lines[line_num]
            spurious_include_found = True
        else:
            line_num += 1
        
        if lines[line_num].find(RUNTESTS_SKIP_LINE) != -1:
            line_num += 2
    
    # Add "#include" directive and overwrite old file.
    # If directive exists and and the file does not need to be changed
    # otherwise, the file will not be altered.
    if directive_nonexistant or spurious_include_found:
        lines.insert(include_dir_line_num, include_directive)
        
        with open(abs_file_path, "w") as f:
            f.writelines(lines)
    
    return


if __name__ == "__main__":
    add_test_util_include(argv[1], int(argv[2]))