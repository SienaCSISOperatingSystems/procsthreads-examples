/*
  Simple "forkbomb" demo program

  Jim Teresco, Williams College
  February, 2005

  Updated January 2012, Siena College, CSIS 330
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  int numprocs;
  pid_t pid;
  int created;

  if (argc < 2) {
    fprintf(stderr,"Usage: %s numprocs\n", argv[0]);
    return 1;
  }

  numprocs = atoi(argv[1]);

  if (numprocs < 0) {
    fprintf(stderr,"%s: numprocs must be nonnegative\n", argv[0]);
    return 1;
  }

  created = 0;

  while (created < numprocs) {
    pid = fork();

    /* if the fork failed, print why and stop trying (hopefully this would
       happen before the OS crashes) */
    if (pid == -1) {
      perror("forkbomb");
      printf("Could not create child %d, aborting.\n", created+1);
      break;
    }

    /* fork was successful, see if we are now the child or the parent */
    if (pid == 0) {
      /* child */
      created++;
      printf("Created child %d, pid %d\n", created, getpid());
    }
    else {
      /* parent process */
      /* just wait for the child to exit */
      waitpid(pid,NULL,0);
      break;
    }
  }
  return 0;
}
