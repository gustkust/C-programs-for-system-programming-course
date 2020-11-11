#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main() {
int fd[2];
pipe(fd);
char messege[] = "Hello";
char readstr[100];
if (fork() == 0) {
        close(fd[0]);
        write(fd[1], messege, strlen(messege) + 1);
        close(fd[1]);
        exit(0);
}
else if (fork() == 0) {
        close(fd[1]);
        read(fd[0], readstr, 100);
        close(fd[0]);
        printf("%s\n", readstr);
        exit(0);
}
}