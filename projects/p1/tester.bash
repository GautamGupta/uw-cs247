#! /bin/bash

# Rudimentary test framework script to run unit tests on a 'subject'
# executable and compare its output to a 'control' executable
#
# In a test directory, add test files. The name of a test file should
# start with the TEST_FILE_PREFIX, ex: test_all_cpus_no_seed

####################################################
# Configuration
####################################################

# Particular constants (modify)
PROJECT_DIR=`pwd`
TESTS_DIR=$PROJECT_DIR/tests
TESTS_RESULTS_DIR=$TESTS_DIR/results
SUBJECT_EXE=$PROJECT_DIR/straights
CONTROL_EXE=$PROJECT_DIR/bin/straights

# Checking for memory leaks slows down this script
# Must use lowercase 'true' to enable
CHECK_LEAKS=true

# Common constants (don't modify unless broken)
VALGRIND=/usr/bin/valgrind
VALGRIND_FLAGS='--leak-check=full'
TEST_FILE_PREFIX=test_

####################################################
# Run Unit Tests
####################################################

# Clear results directory
mkdir -p $TESTS_RESULTS_DIR
rm -rf $TESTS_RESULTS_DIR/*

for TEST_FILE in $TESTS_DIR/$TEST_FILE_PREFIX*
do
	TEST_FILE_NAME=${TEST_FILE##*/}
	TEST_RESULT=$TESTS_RESULTS_DIR/$TEST_FILE_NAME

	# Check for memory leaks
	if [ $CHECK_LEAKS = true ]; then
		$VALGRIND $VALGRIND_FLAGS $SUBJECT_EXE < $TEST_FILE > $TEST_RESULT.valgrind.out 2>&1
		grep -q "ERROR SUMMARY: 0 errors" $TEST_RESULT.valgrind.out

		# If leak detected, go to next test
		# Else clean up valgrind output
		if [ $? -ne 0 ]; then
			echo FAILED $TEST_FILE_NAME \(memory leak\)
			continue
		else
			rm $TEST_RESULT.valgrind.out
		fi
	fi

	# Compare subject's output to the control's
	$SUBJECT_EXE < $TEST_FILE > $TEST_RESULT.subject.out
	$CONTROL_EXE < $TEST_FILE > $TEST_RESULT.control.out
	diff $TEST_RESULT.subject.out $TEST_RESULT.control.out > $TEST_RESULT.diff.out

	# If program outputs are different, go to next test
	# Else clean up diff output
	if [ $? -ne 0 ]; then
		echo FAILED $TEST_FILE_NAME \(output mismatch\)
		continue
	else
		rm $TEST_RESULT.subject.out $TEST_RESULT.control.out $TEST_RESULT.diff.out
	fi

	# The program passed the test
	echo PASSED $TEST_FILE_NAME
done
