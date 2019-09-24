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
