/*
----------------- COMP 310/ECSE 427 Winter 2018 -----------------
I declare that the awesomeness below is a genuine piece of work
and falls under the McGill code of conduct, to the best of my knowledge.
-----------------------------------------------------------------
*/ 
/*File Name: a1_redirection.c
Developers: <<Serge Jabo Byusa>>
Student ID: 2060612575
Purpose: <<Redirecting the output to redirectout.txt>>
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    
    int  fileDesc;
    int ret;
    
    printf("First : Print to stdout \n");

    fileDesc = open("redirectout.txt", O_RDWR | O_CREAT); //open and create or readwrite
    if(fileDesc < 0) //checking for openning fileDescriptor errors
    {
        perror("There is an error in opening the file");
        exit(1);
    }

    int copyStdOut= dup(1); //copy whatever that is in 1 and save it in copyStdOut
    if( copyStdOut< 0) 
    {
        perror("there is an error in dup2");
        exit(1);
    }

    dup2(fileDesc, 1); //then keep filedescriptors in position 1

    printf("Second : Print to redirectout.txt \n"); //print it in out at position 1 in that file

    dup2(copyStdOut,1); //put back what was in 1(out)

    close(copyStdOut); //close what was in 1 and filedescriptor
    close(fileDesc);

    printf("Third : Print to stdout \n");
    
    
    return 0;
}
