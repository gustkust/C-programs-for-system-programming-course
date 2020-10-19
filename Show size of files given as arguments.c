
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>


int main(int argc, char* argv[])
{
int file_r;
char character;
int c = 1;
int cl = 0;

while (c < argc)
{
        file_r = open(argv[c], O_RDONLY);
        while (read(file_r, &character, 1) > 0)
        {
                cl += 1;
        }
        printf("File number %d: %d \n", c, cl);
        cl = 0;
        close(file_r);
        c += 1;
}
}
