#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    
    int  fileDesc;
    int ret;
    
    printf("First : Print to stdout \n");
    fileDesc = open("redirectout.txt", O_RDWR | O_CREAT| O_APPEND); //create  or append or writeonly
    if(fileDesc < 0)
    {
        perror("There is an error in opening the file");
        exit(1);
    }
    int copyStdOut= dup(1); //Takes whatever it to the next available position
    if( copyStdOut< 0)
    {
        perror("there is an error in dup2");
        exit(1);
    }
    dup2(fileDesc, 1); //then 2 goes to 1
    printf("Second : Print to redirectout.txt \n");
    dup2(copyStdOut,1);//at position 1 for out
    close(copyStdOut);
    printf("Third : Print to stdout \n");
    close(fileDesc);
    
    return 0;
}



