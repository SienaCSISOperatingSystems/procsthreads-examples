/* An example of fork()
   Jim Teresco - CS 432 - Fall 2002

   Updated February 2010, January 2012, February 2012

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define AWHILE 10

int main(int argc, char *argv[]) {
  pid_t pid;
  int status;
  int retval;

  printf("The fork example is running: initial pid %d\n", getpid());

  /* sleep a little so we can see what's happening */
  sleep(AWHILE);

  /* This function is called once, but returns twice! */
  pid = fork();

  printf("We called fork(), return value is %d, pid is %d\n", pid, getpid());

  if (pid) {
    /* The parent process */
    printf("The parent (%d) is waiting for the child (%d) to terminate\n",
	   getpid(), pid);
    retval = wait(&status);
    // check for error return
    if (retval == -1) {
      perror("wait");
    }
    else {
      /* according to wait(2), we need to use this macro to extract
	 out the exit status of the child */
      printf("The child finished with status %d\n", WEXITSTATUS(status));
    }
  }
  else {
    /* The child process */
    printf("The child lives!  pid is %d, ppid is %d\n", getpid(), getppid());
    /* sleep for a little while so we can see what's happening */
    sleep(AWHILE);
    /* The value we pass here should go to the parent in the wait() call */
    exit(17);
  }

  /* Only the parent gets down here */
  return 0;
}

