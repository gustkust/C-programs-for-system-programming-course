#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
        int fd1[2], fd2[2];
        int file1 = open("grupy.txt", O_WRONLY | O_CREAT, 0644);

        pipe(fd1);
        if (fork() == 0) {
                close(fd1[0]);
                dup2(fd1[1], 1);
                execlp("cat", "cat", "/etc/group", NULL);
                close(fd1[1]);
                exit(0);
        }
        close(fd1[1]);

        pipe(fd2);
        if (fork() == 0) {
                close(fd2[0]);
                dup2(fd1[0], 0);
                dup2(fd2[1], 1);
                dup2(file1, 1);
                execlp("head", "head", "-5", NULL);
                close(fd2[1]);
                exit(0);
        }
        close(fd2[1]);
        return 0;
}
