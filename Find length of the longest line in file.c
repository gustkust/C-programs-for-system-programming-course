include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
 
 
int main(int argc, char *argv[])
{
int file, length, maxlength;
char character;
 
file = open(argv[1], O_RDONLY);
 
length = 0;
maxlength = 0;
 
while (read(file, &character, 1) > 0)
{
        if (character != '\n')
        {
                length += 1;
        }
        else
    {
                if (length > maxlength)
                {
                        maxlength = length;
                }
                length = 0;
        }
}
printf("\n Max line length is:");
printf("\n %d \n \n", maxlength);
 
}
