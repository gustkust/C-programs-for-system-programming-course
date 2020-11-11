#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>


int main() {
int fd[2];
pipe(fd);
char messege1[] = "Hello";
char messege2[] = "Bye";
char readstr[100];
int p1 = fork();
int p2 = fork();

if (p1 == 0 && p2 > 0) {
        close(fd[0]);
        printf("Wpisanie do potoku wiadomosci 1.\n");
        write(fd[1], messege1, strlen(messege1) + 1);
        close(fd[1]);
}
if (p1 > 0 && p2 == 0) {
        close(fd[0]);
        printf("Wpisanie do potoku wiadomosci 2.\n");
        write(fd[1], messege2, strlen(messege2) + 1);
        close(fd[1]);
}
if (p1 > 0 && p2 > 0) {
        close(fd[1]);
        printf("Odczytanie z potoku wiadomosci.\n");
        read(fd[0], readstr, 100);
        close(fd[0]);
        printf("%s\n", readstr);
}
}
