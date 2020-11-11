#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main() {
int fd[2];
pipe(fd);

if (fork() == 0) {
        close(fd[0]);
        dup2(fd[1],1);
        execlp("finger","finger",NULL);
		close(fd[1]);
        exit(0);
}
close(fd[1]);
dup2(fd[0],0);
execlp("cut", "cut", "-d", " ", "-f1", NULL);
return 0;
}

