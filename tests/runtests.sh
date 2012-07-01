#!/bin/sh

LOGFILE=/tmp/minipack-test.log

echo ""
echo "Unit Tests"

# Loop over compiled tests and run them.
for test_file in tests/*_tests
do
    # Only execute if result is a file.
    if test -f $test_file
    then
        # Log execution to file.
        if ./$test_file 2>&1 > $LOGFILE
        then
            rm -f $LOGFILE
        else
            # If error occurred then print off log.
            cat $LOGFILE
            exit 1
        fi
    fi
done

echo ""
