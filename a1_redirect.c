#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include  <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    
    int  fileDesc;
    int ret;
    fileDesc = open("redirectout.txt", O_RDWR | O_CREAT| O_APPEND); //create  or append or writeonly
    if(fileDesc < 0)
    {
        perror("There is an error in opening the file");
        exit(1);
    }
    int copyDesc = dup(fileDesc);
    write(copyDesc, "Second : Print to redirectout.txt \n", 46);
    //ret = return
    ret = dup2(fileDesc,1);//at position 1 for out
    
    if(ret < 0)
    {
        perror("there is an error in dup2");
        exit(1);
    }
    //system("ls /tmp");
    close(fileDesc);
    //printf("First : Print to stdout \n");
    //..........done......printf("Second : Print to redirectout.txt \n");
    //printf("Third : Print to stdout \n");

    return 0;
}



