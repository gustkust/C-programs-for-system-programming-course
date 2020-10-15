#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
 
 
int main(int argc, char* argv[])
{
int file1, file2;
char character;
file1 = open(argv[1], O_RDONLY);
file2 = open(argv[2], O_WRONLY | O_CREAT, 0644);
 
 
lseek(file1, -12, SEEK_END);
while (read(file1, &character, 1) > 0)
{
        write(file2, &character, 1);
}
 
write(file2, "\n", 1);
lseek(file1, -3, SEEK_END);
 
int c = 0;
while (c != 10)
{
        read(file1, &character, 1);
        if (character == ' ')
        {
                c += 1;
        }
        if (c != 10)
        {
                lseek(file1, -2, SEEK_CUR);
        }
}
 
 
while (read(file1, &character, 1) > 0)
{
        write(file2, &character, 1);
}
 
write(file2, "\n", 1);
 
 
lseek(file1, -3, SEEK_END);
 
c = 0;
while (c != 10)
{
        read(file1, &character, 1);
        if (character == '\n')
        {
                c += 1;
        }
        lseek(file1, -2, SEEK_CUR);
}
 
while (read(file1, &character, 1) > 0)
{
write(file2, &character, 1);
}
 
close(file1);
close(file2);
}
