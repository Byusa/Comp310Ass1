/*File Name: a1_command_piping.c
Developers: <<Serge Jabo Byusa>>
Student ID: 2060612575
Purpose: <<InterProcess Communication, it execute an ls command in the child process,
and prints the output of the command in the parent process.>>
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main (int argc, char *args[])
{
  pid_t pid;
  int mypipefd[2];
  int retPipeFd;
  char things[8192];
  retPipeFd = pipe (mypipefd);
  if (retPipeFd == -1)
    {
      perror ("pipe error");
      exit (1);
    }

  pid = fork ();

  if (pid == -1) 
    {
      perror ("fork error");
      exit (1);
    }

  if (pid == 0)
    {
      //Child : executels using execvp
      char *Mycmd[2];
      close (1);		//closing stdout
      dup (mypipefd[1]);	//replacing stdout with pipe write 

      Mycmd[0] = "ls";
      Mycmd[1] = NULL;
      close (mypipefd[0]);	//closing pipe read
      close (mypipefd[1]);
      execvp ("ls", Mycmd); //
    }

  else
    {
      // Parent : print output from ls here
      close (0);		//closing stdin
      dup (mypipefd[0]);	//lets replace stdin with pipe read
      int countBytes = read (mypipefd[0], things, sizeof (things));
      printf ("%.*s\n", countBytes, things); //print(list) list directory contents 
      close (mypipefd[1]);	//close pipe write
      close (mypipefd[0]);
    }
  return 0;

}
