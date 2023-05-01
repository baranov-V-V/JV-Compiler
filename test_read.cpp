#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  int  stdout_bk; //is fd for stdout backup

  printf("this is before redirection\n");
  stdout_bk = dup(fileno(stdout));

  int pipefd[2];
  pipe2(pipefd, 0); // O_NONBLOCK);

  // What used to be stdout will now go to the pipe.
  dup2(pipefd[1], fileno(stdout));

  //printf("this is printed much later!\n");
  system("./a.out");
  fflush(stdout); //flushall();
  write(pipefd[1], "good-bye", 9); // null-terminated string!
  close(pipefd[1]);

  dup2(stdout_bk, fileno(stdout));//restore
  printf("this is now\n");

  char buf[101];
  read(pipefd[0], buf, 100);
  printf("got this from the pipe >>>%s<<<\n", buf);
}