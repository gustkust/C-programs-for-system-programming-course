#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/time.h>
#include <sys/wait.h>


int main(int argc, char* argv[]) {
float t;
struct timeval start, stop;

gettimeofday(&start, NULL);

if(fork() == 0) {
        execvp(argv[1], argv+1);
}
else {
        wait(NULL);
        gettimeofday(&stop, NULL);
        t = (stop.tv_sec - start.tv_sec) * 1000000u + stop.tv_usec - start.tv_usec;
        t = t/1000000;
        printf("Czas: %f s.\n", t);
}
}