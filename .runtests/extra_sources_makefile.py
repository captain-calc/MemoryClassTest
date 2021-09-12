
import os
import sys
from typing import Dict


def check_makefile_extra_sources(
    test_abspath: str,
    program_srcdir_abspath: str
) -> None:
    """
    Determines if the test's makefile has the proper EXTRA_***SOURCES.
    
    Pre:  <test_abspath> must be the absolute system path to the test's main
          directory.
          <program_srcdir_abspath> must be the absolute system path to the
          program's src/ directory.
    Post: Correct extra source variables written to the makefile if necessary.
    """

    relative_source_path: str = os.path.relpath(program_srcdir_abspath, start=test_abspath)

    extra_sources_dict: Dict[str, str] = {
        "EXTRA_CPPSOURCES":
            "$(filter-out "
            + os.path.join(relative_source_path,"main.cpp")
            + ", $(wildcard "
            + os.path.join(relative_source_path, "*.cpp")
            + "))",
        "EXTRA_ASMSOURCES":
            "$(wildcard " + os.path.join(relative_source_path, "*.asm") + ")",
    }

    file_changed: bool = False
    line_num: int = 0
    lines: list[str] = []

    with open(os.path.join(test_abspath, "makefile"), "r") as f:
        lines = f.readlines()

        for source_type, source_target in extra_sources_dict.items():

            while not lines[line_num].startswith(source_type) and line_num < (len(lines) - 1):
                line_num += 1;

            if line_num < (len(lines) - 1):
                read_source_target = lines[line_num][lines[line_num].find("=") + 1:].strip()

                if read_source_target != source_target:
                    lines[line_num] = source_type + " = " + source_target + "\n"
                    file_changed = True

    if file_changed:
        with open(os.path.join(test_abspath, "makefile"), "w") as f:
            f.writelines(lines)

    return


if __name__ == "__main__":
    check_makefile_extra_sources(sys.argv[1], sys.argv[2])