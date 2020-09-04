/* Jim Teresco, Computer Science 421, Fall 1999
   Project 1 sample solution - pthreads version */

/* updated for Fall 2001, CS 432, Williams College */
/* updated again for Spring 2003, CS 338, Williams College */
/* updated again for Spring 2005, CS 432, Williams College */
/* updated again for Spring 2010, CS 322, Mount Holyoke College */
/* updated again for Spring 2012, CS 330, Siena College */

/*
  Note: it is poor practice (but we do it anyway and ignore the
  potential compiler warnings) to print out the pthread_t returned by
  pthread_self and in the first parameter to pthread_create, as it may
  be a number, a structure, an array, pretty much anything a
  particular pthreads implementation decides.  So we print it as a hex
  value so we can at least see something to indicate which thread are
  which.  It would be nice if there was a function to print out a
  meaningful thread id along the lines of the PIDs we can print as
  returned by getpid() for processes.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/* use a global variable - not nice but it makes life easier */
int max_tree_depth;

/* also have a global for thread attributes */
pthread_attr_t thread_attr;

/* function to print count spaces to stdout */
void indent(int count) {
  int i;

  for (i=0;i<count;i++) printf("  ");
}

/* recursive function - build the tree

   tree_depth is the depth of the current call, max_tree_depth
   is the maximum tree depth to build */
void *split_proc(void *tree_depth_voidptr) {

  int tree_depth=*((int *)tree_depth_voidptr);
  int tree_depth_plus_1 = tree_depth+1;
  pthread_t child1, child2;
  int rc;

  indent(tree_depth);
  printf("[%p] new thread, pid=%d\n", pthread_self(),getpid());
    
  if (tree_depth < max_tree_depth) { /* we want to make child threads */

    /* create child 1 ("left" child) */
    rc=pthread_create(&child1, &thread_attr,
                      split_proc, (void *)&tree_depth_plus_1);
    if (rc==0) {
      indent(tree_depth);
      printf("[%p] created \"left\" child, thread_id=%p\n",
             pthread_self(), child1);
    }
    else {
      printf("[%p] could not create \"left\" child\n",pthread_self());
      exit(1);
    }
    
    /* create child 2 ("right" child) */
    rc=pthread_create(&child2, &thread_attr,
                      split_proc, (void *)&tree_depth_plus_1);
    if (rc==0) {
      indent(tree_depth);
      printf("[%p] created \"right\" child, thread_id=%p\n",
             pthread_self(), child2);
    }
    else {
      printf("[%p] could not create \"left\" child\n",pthread_self());
      exit(1);
    }
    /* wait for our children to go away */
    pthread_join(child1,NULL);
    pthread_join(child2,NULL);
  }
  indent(tree_depth);
  printf("[%p] exiting\n", pthread_self());
  pthread_exit(0);
}

int main(int argc, char *argv[]) {
  int initial_tree_depth = 0;

  if (argc != 2) {
    fprintf(stderr,"Usage: %s tree_depth\n",argv[0]);
    exit(1);
  }

  max_tree_depth=atoi(argv[1]);

  pthread_attr_init(&thread_attr);
  pthread_attr_setscope(&thread_attr, PTHREAD_SCOPE_PROCESS);
  /*pthread_attr_setscope(&thread_attr, PTHREAD_SCOPE_SYSTEM);*/

  printf("[1] pid=%d, original parent child of ppid=%d\n", getpid(),
         getppid());

  /* start the building - this is level 0, going to max_tree_depth */

  split_proc((void *)&initial_tree_depth);
  return 0;
}
