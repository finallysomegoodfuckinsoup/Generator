#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int lucasNumberSum(int n) {
    int sum = 0;
    int l1 = 2, l2 = 1, run;
    sum += l1;
    while (l2 <= n) {
        sum += l2;
        run = l1 + l2;
        l1 = l2;
        l2 = run;
    }
    return sum;
}
int lucasNumber(int n) {
    if (n == 0) return 2;
    if (n == 1) return 1;
    return lucasNumber(n - 1) + lucasNumber(n - 2);
}

int main (int argc, char *argv[]) {
    if (argc != 2) fprintf(stderr, "Wrong number of arguments. Needs 1. Found %d\n", argc - 1);

    int num = atoi(argv[1]);
    printf("[Lucas] [%ld]: The sum of the first %d numbers of the Lucas series is %d\n", (long)getpid(), num, lucasNumberSum(num));
    printf("[Lucas] [%ld]: The nth number in the lucas series is %d\n", (long)getpid(), lucasNumber(num - 1));
    if (lucasNumberSum(num) > 50)
        exit(num);
    else
        exit(lucasNumberSum(num));
}