if [ $# -ne 1 ]; then
    echo "Usage: ./valgrind_test.sh <executable>"
    exit 0
fi

valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind.out \
         --error-exitcode=-1 \
         $1

if [ $? -eq -1 ]; then
    echo "Valgrind found errors. Check valgrind.out for further info"
else
    echo "Valgrind did not find any issues"
fi
