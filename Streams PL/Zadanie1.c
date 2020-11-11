#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>


int main() {
int fd[2];
pipe(fd);
int prs1 = fork();
int prs2 = fork();
char messege[] = "Hello";
char readstr[100];
if (prs1 > 0 && prs2 > 0) {
        close(fd[0]);
        printf("Wpisanie do potoku.\n");
        write(fd[1], messege, strlen(messege) + 1);
        close(fd[1]);
}
else if (prs1 == 0 && prs2 > 0) {
        close(fd[1]);
        printf("Odczytanie z potoku.\n");
        read(fd[0], readstr, 100);
        close(fd[0]);
        printf("%s\n", readstr);
}
}
