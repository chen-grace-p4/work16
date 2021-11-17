#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main() {
   //before forking print out some initial message
   printf("forking is starting now\n");

   int child1;
   int child2;

   child1 = fork();

   srand(time(NULL));

   //checking that the process running is the parent so that when child1 goes here, it returns 0 and doesn't fork() again
   if(child1) {
      //fork for second child
      child2 = fork();

      //increments rand() seed for child2 so it sleeps for diff amount of time
      rand();
   }

   //if the process running is the parent
   if (child1 && child2){
    int status;
    //stops parent from running until any child has exited
    int cpid = wait(&status);
    //child returns the amount of time it was asleep for (see else statement)
    int time_slept = WEXITSTATUS(status);

    //print out pid of completed child and how many seconds it was asleep
    printf("completed child pid is %d and it was asleep for %d secs\n", cpid, time_slept);

    //doesn't wait for other child since it's fine for parent to finish before other child finishes

    //print a message that the parent is done
    printf("parent process is done\n");
    //ends the program
    return 0;
  }
  //if the process running is child1 or child2, returns time it slept for
  else{
     //prints child pid
     printf("child pid is %d\n", getpid());

     //sleep for random number of secs in range [2,5]
     // (rand() % (max - min + 1)) + min
     int rand_secs = (rand() % (5 - 2 + 1)) + 2;
     sleep(rand_secs);

     //print a message that it is finished
     printf("child process %d has finished.\n", getpid());

     //returns time slept for so WEXITSTATUS works for parent process
     return rand_secs;
  }

  return 0;
}
