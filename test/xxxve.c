  #include <sys/types.h>
  #include <unistd.h>
  #include <stdio.h>

  int main(void)
  {
     pid_t pid;
     char *const parmList[] = {"/bin/ls", "-l", "/u/userid/dirname", NULL};
     char *const envParms[2] = {"STEPLIB=SASC.V6.LINKLIB", NULL};

     if ((pid = fork()) ==-1)
        perror("fork error");
     else if (pid == 0) {
        execve("/usr/bin", parmList, envParms);
        printf("Return not expected. Must be an execve error.n");
     }
     return(0);
  }

 
