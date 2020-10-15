#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
 
 
int main(int argc, char* argv[])
{
int file_r, file_w;
char character;
int c = 1;
int last = argc - 1;
file_w = open(argv[last], O_WRONLY | O_CREAT, 0644);
 
while (c < last)
{
        file_r = open(argv[c], O_RDONLY);
        while (read(file_r, &character, 1) > 0)
        {
                write(file_w, &character, 1);
        }
        close(file_r);
        c += 1;
}
close(file_w);
 
}
