#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main() {
int p1, p2, p3, p4;
int fd1[2], fd2[2], fd3[3];
int i1, i2, i3, i4;
pipe(fd1);
pipe(fd2);
pipe(fd3);

if (fork() == 0) {
        i1 = 1; i2 = 2; i3 = 3; i4 = 4;
		
		close(fd1[0]);
		
        write(fd1[1], &i1, sizeof(i1));
        write(fd1[1], &i2, sizeof(i2));
        write(fd1[1], &i3, sizeof(i3));
        write(fd1[1], &i4, sizeof(i4));

        close(fd1[1]);
		exit(0);
}

if (fork() == 0) {
		close(fd1[1]);
		
        read(fd1[0], &i1, sizeof(i1));
        read(fd1[0], &i2, sizeof(i2));
        read(fd1[0], &i3, sizeof(i3));
        read(fd1[0], &i4, sizeof(i4));

		close(fd1[0]);
		
        i1++; i2++; i3++; i4++;
		printf("Podbicie o 1.\n");
		
		close(fd2[0]);
		
        write(fd2[1], &i1, sizeof(i1));
        write(fd2[1], &i2, sizeof(i2));
        write(fd2[1], &i3, sizeof(i3));
        write(fd2[1], &i4, sizeof(i4));

        close(fd2[1]);
		exit(0);
}

if (fork() == 0) {
        close(fd2[1]);
		
        read(fd2[0], &i1, sizeof(i1));
        read(fd2[0], &i2, sizeof(i2));
        read(fd2[0], &i3, sizeof(i3));
        read(fd2[0], &i4, sizeof(i4));

		close(fd2[0]);
		
        i1++; i2++; i3++; i4++;
		printf("Podbicie o 1.\n");
		
		close(fd3[0]);
		
        write(fd3[1], &i1, sizeof(i1));
        write(fd3[1], &i2, sizeof(i2));
        write(fd3[1], &i3, sizeof(i3));
        write(fd3[1], &i4, sizeof(i4));

        close(fd3[1]);
		exit(0);
}

else {
		close(fd3[1]);
		
        read(fd3[0], &i1, sizeof(i1));
        read(fd3[0], &i2, sizeof(i2));
        read(fd3[0], &i3, sizeof(i3));
        read(fd3[0], &i4, sizeof(i4));

        close(fd3[0]);
	
		i1++; i2++; i3++; i4++;
		printf("Podbicie o 1.\n");

        printf("%d %d %d %d\n", i1, i2, i3, i4);
		exit(0);
}
}
