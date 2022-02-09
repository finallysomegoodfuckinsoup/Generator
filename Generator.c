#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) fprintf(stderr, "Wrong number of arguments. Needs 1. Found %d\n", argc - 1);
    pid_t pid;
    FILE *f = fopen(argv[1], "r");

    char buf[256];
    pid_t childLuc;
    pid_t childHex;
    pid_t childHarm;
    int status;
    char *tmpStor;

    while (fgets(buf, sizeof(buf), f)) {
        pid = fork();
        if (pid < 0) fprintf(stderr, "Error running child process");
        else if (pid == 0) { //if it's the child process (lucas)
            pid = fork();
            childLuc = getpid();
            int lucRet = execlp("./Lucas", buf, NULL); //run the lucas process
            if (pid < 0) fprintf(stderr, "Error running child process");
            else if (pid == 0) { //if it's the child process (hexagonal)
                pid = fork();
                childHex = getpid();
                tmpStor = NULL; // reset the value to be returned
                sprintf(tmpStor, "%d", lucRet);
                int hexRet = execlp("./HexagonalSeries", tmpStor, NULL);
                if (pid < 0) fprintf(stderr, "Error running child process");
                else if (pid == 0) { //if it's the child process (harmonic)
                    pid = fork();
                    childHarm = getpid();
                    tmpStor = NULL; // reset the value to be returned
                    sprintf(tmpStor, "%d", hexRet);
                    execlp("./HarmonicSeries", tmpStor, NULL);
                } else { // if it's the parent process (hexagonal)
                    printf("3a:[Generator] [%ld]: Waiting for the child process %ld\n", (long) getpid(), (long)childHarm);
                    wait(&status);
                    printf("3b:[Generator] [%ld]: The child process %ld returned %d\n", (long)getpid(), (long)childHarm, WEXITSTATUS(childHarm));
                }
            } else { // if it's the parent process (lucas)
                printf("2a:[Generator] [%ld]: Waiting for the child process %ld\n", (long) getpid(), (long)childHex);
                wait(&status);
                printf("2b:[Generator] [%ld]: The child process %ld returned %d\n", (long)getpid(), (long)childHex, WEXITSTATUS(childHex));
            }
        } else { // if it's the parent process (generator)
            printf("1a:[Generator] [%ld]: Waiting for the child process %ld\n", (long) getpid(), (long)childLuc);
            wait(&status);
            printf("1b:[Generator] [%ld]: The child process %ld returned %d\n", (long)getpid(), (long)childLuc, WEXITSTATUS(childLuc));
        }
    }
}

