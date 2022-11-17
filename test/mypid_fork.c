#include <unistd.h>
#include <stdio.h>

int
main(void)
{
  pid_t          pid;

  if ((pid = fork()) == -1)
    {
      perror("fork");
      return 1;
    }
  else if (pid == 0)
    printf("Je suis le fils, et mon pid = %d\n", getpid());
  else
    printf("Je suis le pere, et mon pid = %d. Le pid de mon fils = %d\n", getpid(), pid);

  return 0;
}
 

