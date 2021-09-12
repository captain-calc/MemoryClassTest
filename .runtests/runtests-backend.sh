#!/bin/bash

# Date:    September 11, 2021
# Version: 0.0.2

# Console output colors
BLACK=$(tput setaf 0)
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
BLUE=$(tput setaf 4)
MAGENTA=$(tput setaf 5)
CYAN=$(tput setaf 6)
LT_GRAY=$(tput setaf 7)
ORANGE=$(tput setaf 202)
RESET=$(tput sgr0)


output_section()
{
  tput setaf 3
  echo "======================================================================"
  tput sgr0
}


output_subsection()
{
  tput setaf 202
  echo "----------------------------------------------------------------------"
  tput sgr0
}


# Arguments:
#   $1 = absolute path to the directory that contains the tests
#   $2 = absolute path to the directory that contains the program's source
#        files
#
build_tests()
{
  tests_path=$1
  
  echo -e "\nBuilding unit tests..."
  output_section
  
  for test in $(ls $tests_path)
  do
    test_abs_path="$tests_path/$test"
  
    if [ -d "$test_abs_path" ]
    then
      echo -e "\n\nCompiling: $CYAN $test $RESET"
      output_subsection
    
      # Add the "test_util.h" to each test's main file so it can access program
      # functions.
      python3 .runtests/test_util_include.py "$test_abs_path/src/main.cpp" 2

      # Make sure each makefile has the correct EXTRA_CPPSOURCES and
      # EXTRA_ASMSOURCES.
      python3 .runtests/extra_sources_makefile.py $test_abs_path $2
    
      # Spawn a new shell so we preserve our current working directory and
      # build each test program.
      (
        cd "$test_abs_path"
        make
      )
    fi
  done
}


# Arguments:
#   $1 = absolute path to the directory that contains the tests
#   $2 = absolute path to a valid TI-84 Plus CE ROM file.
#
run_tests()
{
  tests_path=$1
  total_num_tests=0
  num_tests_passed=0
  autotest_file="autotest.json"
  
  echo -e "\nRunning unit tests..."
  output_section
  
  for test in $(ls $tests_path)
  do
  
    test_abs_path="$tests_path/$test"
    
    if [ -d "$test_abs_path" ]
    then
      echo -e "\n\nRunning: $CYAN $test $RESET"
      output_subsection
      
      # Write the appropriate ROM path to the autotest file if necessary.
      python3 .runtests/autotest_rom_path.py "$test_abs_path/$autotest_file" $2

      # Run the unit test.
      1>/dev/null autotester "$test_abs_path/$autotest_file"
      #autotester -d "$test_abs_path/autotest.json"

      if [ $? -eq 0 ]
      then
        echo -e "$GREEN""Test passed. $RESET"
        ((num_tests_passed++))
      else
        echo -e "$RED""Test failed. $RESET"
      fi

      ((total_num_tests++))
    fi
  done

  echo ""
  output_section
  echo "$num_tests_passed out of $total_num_tests tests passed."
  percentage=$(awk "BEGIN { printf \"%.2f\", 100*$num_tests_passed/$total_num_tests}")
  echo -e "Finished running unit tests ($percentage% coverage).\n"
}


# Main code execution starts here
#=================================


# Clear the console
tput reset

# Store the path to the tests
tests_path=$1

build_tests $tests_path $program_src_path
echo ""
run_tests $tests_path $ti84pce_rom_path
