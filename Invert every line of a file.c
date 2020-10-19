include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>


int main(int argc, char* argv[])
{
int file = open(argv[1], O_RDWR);
char character;
int c = 0;
int move;
while(read(file, &character, 1) > 0)
{
        if(character != '\n')
        {
                c += 1;
        }
        else
        {
                char l[c];
                move = -c - 1;
                lseek(file, move, SEEK_CUR);
                read(file, l, c);
                lseek(file, -c, SEEK_CUR);
                while(c > 0)
                {
                        write(file, l - 1 + c, 1);
                        c -= 1;
                }
                lseek(file, 1, SEEK_CUR);
        }
}
        close(file);
}
