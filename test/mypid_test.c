/* $> gcc -o example1 example1.c */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *env[])
{
  pid_t         pid;
  int           pipe_fd[2];

  if (argc < 2)
    return 1;

  if (pipe(pipe_fd) == -1)
  {
      perror("pipe");
      return 1;
  }
  if ((pid = fork()) == -1)
  {
      perror("fork");
      return 1;
  }
  else if (pid == 0)
  {
      close(pipe_fd[0]);
      if (dup2(pipe_fd[1], 1) == -1)
      perror("dup2");
      else if (execve(argv[1], argv + 1, env) == -1)
      perror("execve");
      return 1;
  }
  else
  {
      char      buffer[1024];
      int       ret;
      // int       status;

      close(pipe_fd[1]);

      while ((ret = read(pipe_fd[0], buffer, 1023)) != 0)
	    {
        printf("%d\n", ret);
        buffer[ret] = 0;
        printf("%s\n", buffer);
      }
  }
  return 0;
}
 

