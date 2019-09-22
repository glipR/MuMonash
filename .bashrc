ulimit -s 10000

# For C/CPP
function runc {
    clear;clear
    F=`ls -t *.c* | head -n1`
    g++ $F -g -std=c++14 -Wall -Wextra -Wconversion -Wshadow -Wfatal-errors -fsanitize=address,undefined -o sol || return

    for i in *.in; do
        echo ---$F $i
        { time (time ./sol <$i >o) >/dev/null; } 2>&1 | grep real | awk '{print $2}'
        (diff -y o ${i%in}[ao]?? >t || cat t) || cat o
    done
}

# For Python3
function runp {
    clear;clear
    F=`ls -t *.py | head -n1`
    for i in *.in; do
        echo ---$F $i
        { time (time python3 $F <$i >o) >/dev/null; } 2>&1 | grep real | awk '{print $2}'
        (diff -y o ${i%in}[ao]?? >t || cat t) || cat o
    done
}
