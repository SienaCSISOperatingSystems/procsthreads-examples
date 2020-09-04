/* Example showing more about the amount of shared context when using
   fork() and pthreads.

   Jim Teresco, CS 432, Fall 2002, Spring 2005
   CS 338, Spring 2003
   CS 322, Mount Holyoke College, Spring 2010
   CS 330, Siena College, Spring 2012 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* A global variable, so we can see who shares it */
int this_is_global;

void *thread_func( void *ptr ); 
  
int main()  {
  /* a variable local to main - on the call stack */
  int local_main;
  int pid, status;
  pthread_t thread1, thread2;
  int threadnums[] = {1, 2};
  
  printf("First, we create two threads to see better what context they share...\n");
  this_is_global=1000;
  printf("Set this_is_global=%d\n",this_is_global);
  pthread_create( &thread1, NULL,
                  thread_func, (void*)&(threadnums[0]));
  pthread_create(&thread2, NULL,
                 thread_func, (void*)&(threadnums[1]));
  
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  printf("After threads, this_is_global=%d\n",this_is_global);
  printf("\n");
  printf("Now that the threads are done, let's call fork..\n");
  local_main=17; this_is_global=17;
  printf("Before fork(), local_main=%d, this_is_global=%d\n",local_main,
         this_is_global);
  pid=fork();
  if (pid == 0) {  /* this is the child */
    printf("In child, pid %d: &global: %tX, &local: %tX\n", getpid(),
           (ptrdiff_t)&this_is_global, (ptrdiff_t)&local_main);
    local_main=13; this_is_global=23;
    printf("Child set local_main=%d, this_is_global=%d\n",local_main,
           this_is_global);
    exit(0);
  }
  else { /* this is parent */
    printf("In parent, pid %d: &global: %tX, &local: %tX\n", getpid(),
           (ptrdiff_t)&this_is_global, (ptrdiff_t)&local_main);
    wait(&status);
    printf("In parent, local_main=%d, this_is_global=%d\n",local_main,
           this_is_global);
  }
  exit(0);
}

void *thread_func(void *ptr) {
  /* a variable local to thread_func */
  int local_thread;
  int threadnum = *((int *)ptr);

  printf("Thread %d, pid %d, addresses: &global: %tX, &local: %tX\n",
         threadnum, getpid(),
	 (ptrdiff_t)&this_is_global, (ptrdiff_t)&local_thread);
  this_is_global++;
  printf("In Thread %d, incremented this_is_global=%d\n",
	 threadnum, this_is_global);
  pthread_exit(0);
}
