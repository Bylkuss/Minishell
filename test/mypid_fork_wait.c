#include <unistd.h>
#include <stdio.h>

/* Includes necessaires pour la fonction wait() */
#include <sys/types.h>
#include <sys/wait.h>

int
main(int argc, char *argv[], char *env[])
{
  pid_t           pid;
  int           status;

  if (argc > 1)
    {
      if ((pid = fork()) == -1)
        {
          perror("fork");
          return 1;
        }
      /* Si pid == 0, alors on est dans le process fils. */
      else if (pid == 0)
        {
          if (execve(argv[1], argv + 1, env) == -1)
            perror("execve");
          return 1; /* On termine le fils même si execve fail parce qu'on veut voir que le pid du pere*/
        }
      /* Sinon, dans le pere. */
      else
        wait(&status); /* Oui, il faudrait vérifier la valeur de retour... */
    }

  printf("My pid is: %d\n", getpid());

  return 0;
}
 


