#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main() {
int fd1[2], fd2[2], fd3[2], fd4[2], fd5[2], fd6[2];

pipe(fd1);
if (fork() == 0) {
        close(fd1[0]);
        dup2(fd1[1],1);
        execlp("ps", "ps", "-ef", NULL);
        exit(0);
}
close(fd1[1]);

pipe(fd2);
if (fork() == 0) {
        close(fd2[0]);
        dup2(fd1[0],0);
        dup2(fd2[1],1);
        execlp("tr", "tr", "-s", "' '", ":", NULL);
        exit(0);
}
close(fd2[1]);

pipe(fd3);
if (fork() == 0) {
        close(fd3[0]);
        dup2(fd2[0],0);
        dup2(fd3[1],1);
        execlp("cut", "cut", "-d:", "-f1", NULL);
        exit(0);
}
close(fd3[1]);

pipe(fd4);
if (fork() == 0) {
        close(fd4[0]);
        dup2(fd3[0],0);
        dup2(fd4[1],1);
        execlp("sort", "sort", NULL);
        exit(0);
}
close(fd4[1]);

pipe(fd5);
if (fork() == 0) {
        close(fd5[0]);
        dup2(fd4[0],0);
        dup2(fd5[1],1);
        execlp("uniq", "uniq", "-c", NULL);
        exit(0);
}
close(fd5[1]);

close(fd1[0]);
close(fd2[0]);
close(fd3[0]);
close(fd4[0]);

dup2(fd5[0],0);
execlp("sort", "sort", "-n", NULL);
return 0;
}
