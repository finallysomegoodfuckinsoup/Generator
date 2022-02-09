#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

float harmNum(int n) {
    return 1.0/n;
}
float harmSum(int n) {
    if (n <= 1) return 1;
    printf("\nadding harmNum(%d) %f to harmNum(%d) %f\n", n, harmNum(n), n, harmNum(n - 1));
    return harmNum(n) + harmSum(n - 1);
}

int main (int argc, char **argv) {
    int num = atoi(argv[1]);
    printf("[HarmonicSeries] [%ld]: The sum of the first %d numbers of the harmonic series is %f\n", (long)getpid(), num, harmSum(num));
    exit(harmSum(num));
}