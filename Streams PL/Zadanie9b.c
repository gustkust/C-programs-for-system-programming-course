#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
        int fd1[2], fd2[2];

        pipe(fd1);
        if (fork() == 0) {
                close(fd1[0]);
                dup2(fd1[1], 1);
                execlp("ls", "ls", "-l", NULL);
                close(fd1[1]);
                exit(0);
        }
        close(fd1[1]);

        pipe(fd2);
        if (fork() == 0) {
                close(fd2[0]);
                dup2(fd1[0], 0);
                dup2(fd2[1], 1);
                execlp("grep", "grep", "^d", NULL);
                close(fd2[1]);
                exit(0);
        }
		close(fd2[1]);
        
		close(fd1[0]);
        dup2(fd2[0], 0);
        execlp("more", "more", NULL);
        return 0;
}