ulimit -s 10000

# For C/CPP
function runc {
    clear;clear
    F=`ls -t *.c* | head -n1`
    g++ $F -g -std=c++14 -Wall -Wextra -Wconversion -Wshadow -Wfatal-errors -fsanitize=address,undefined -o sol || return

    for i in *.in; do
        echo ---$F $i
        { time (./sol <$i >o 2>error) >/dev/null; } 2>timing
        cat timing | grep real | awk '{print $2}'
        cat error
        # Not required
        rm timing
        rm error
        # Required
        diff -y o ${i%in}[ao]?? >t || cat t || cat o
        # Not required
        rm o
        rm t
    done
}

# For Python3
function runp {
    clear;clear
    F=`ls -t *.py | head -n1`
    for i in *.in; do
        echo ---$F $i
        { time (python3 $F <$i >o 2>error) >/dev/null; } 2>timing
        cat timing | grep real | awk '{print $2}'
        cat error
        # Not required
        rm timing
        rm error
        # Required
        diff -y o ${i%in}[ao]?? >t || cat t || cat o
        # Not required
        rm o
        rm t
    done
}

function runtests {
    # Arguments
        # Test generator
        # Correct script
        # Test script
        # Total tests
    clear;clear
    if [[ $2 == *.c* ]];
    then
        g++ $2 -g -std=c++14 -Wall -Wextra -Wconversion -Wshadow -Wfatal-errors -fsanitize=address,undefined -o correct
    fi
    if [[ $3 == *.c* ]];
    then
        g++ $3 -g -std=c++14 -Wall -Wextra -Wconversion -Wshadow -Wfatal-errors -fsanitize=address,undefined -o test
    fi
    ITERATIONS=${4:-50}
    completed=1
    for (( i=1; i<=ITERATIONS; i++ )) do
        echo "Test #$i"
        python3 $1 > test.in
        if [[ $2 == *.c* ]];
        then
            ./correct < test.in > test.out
        fi
        if [[ $2 == *.py ]];
        then
            python3 $2 < test.in > test.out
        fi
        error=$?
        if [[ $error -ne 0 ]]
        then
            echo "Error on test case with truth script"
            completed=0
            break
        fi
        if [[ $3 == *.c* ]];
        then
            ./test < test.in > test.cmp
        fi
        if [[ $3 == *.py ]];
        then
            python3 $3 < test.in > test.cmp
        fi
        error=$?
        if [[ $error -ne 0 ]]
        then
            echo "Error on test case with test script"
            completed=0
            break
        fi
        diff test.cmp test.out > /dev/null 2>&1
        difference=$?
        if [[ $difference -eq 1 ]]
        then
            echo "Difference found:"
            echo "test.cmp | test.out"
            diff test.cmp test.out
            completed=0
            break
        fi
    done
    rm test
    rm correct
    if [[ $completed -eq 1 ]]
    then
        echo "Completed $ITERATIONS tests successfuly."
        rm test.cmp
        rm test.in
        rm test.out
    fi
}
