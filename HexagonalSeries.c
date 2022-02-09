#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int hexNum(int n) {
    return (((2 * n) * (2 * n - 1)) / 2);
}
int hexSum (int n) {
    if (n == 1) return 1;
    return hexNum(n) + hexSum(n -1);
}
int main (int argc, char **argv) {
    if (argc != 2) fprintf(stderr, "Wrong number of arguments. Needs 1. Found %d\n", argc - 1);
    int num = atoi(argv[1]);
    printf("[HexagonalSeries] [%ld]: The sum of first %d hexagonal numbers is:%d\n", (long)getpid(), num, hexSum(num));
    printf("[HexagonalSeries] [%ld]: The nth number in the Hexagonal series is %d\n", (long)getpid(), hexNum(num));
    if (hexSum(num) > 100)
        exit(num);
    else
        exit(hexSum(100));
}