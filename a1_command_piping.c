#include<stdio.h>
#include<unistd.h>

int main()
{
  if(fork()==0)
  {
   //Child : executels using execvp
  }
  else
  {
  // Parent : print output from ls here
  }
  return 0;
}
