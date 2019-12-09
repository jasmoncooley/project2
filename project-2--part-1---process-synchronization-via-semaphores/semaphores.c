/*------------------------------------------------------*/
/* Skeleton for the synchronization Lab .   assignment 	*/
/*------------------------------------------------------*/
/* Note:						                        */
/* -----						                        */
/* 1. E = Elephant					                    */
/* 2. D = Dog						                    */
/* 3. C = Cat					                    	*/
/* 4. M = Mouse						                    */
/* 5. P = Parrot					                    */
/*------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHILD 0 /* Return value of child proc from fork call */

int main()
{
  sem_t *elephant_mice; /* semaphore to keep Elephants and Mice separate */
  sem_t *dog_cats;      /* semaphore to keep Dog and Cat separate  */
  sem_t *cat_parrots;   /* semaphore to keep Cat and Parrot separate  */
  sem_t *mouse_parrots; /* semaphore to keep Mouse and Parrot separate  */
  sem_t *cat_mice;      /* semaphore to keep Cat and Mice separate  */

sem_t * mutex[5];

  int pid;    /* Process id after fork call */
  int i;      /* Loop index. */
  int N;      /* Number of requests to process */
  int status; /* Exit status of child process. */
  int type;   /* Type of animal */

  /*   Initialization of the semaphores   */
  if ((mutex[0] = sem_open("/elephant_mice_sem", O_CREAT, 0644, 1)) == SEM_FAILED)
  {
    perror("Failed to open/initialize semphore for elephant_mice.");
    exit(-1);
  }

  if ((mutex[1] = sem_open("/dog_cat_sem", O_CREAT, 0644, 1)) == SEM_FAILED)
  {
    perror("Failed to open/initialize semphore for dog_cat.");
    exit(-1);
  }

  if ((mutex[2] = sem_open("/cat_parrot_sem", O_CREAT, 0644, 1)) == SEM_FAILED)
  {
    perror("Failed to open/initialize semphore for cat_parrot.");
    exit(-1);
  }

  if (((mutex[3] = sem_open("/mouse_parrot_sempahore", O_CREAT, 0644, 1)) == SEM_FAILED)
  {
    perror("Failed to open/initialize semphore for mouse_parrot.");
    exit(-1);
  }

  if (((mutex[4] = sem_open("/cat_mice_sempahore", O_CREAT, 0644, 1)) == SEM_FAILED)
  {
    perror("Failed to open/initialize semphore for cat_mice.");
    exit(-1);
  }

  printf("How many requests to be processed: \n");
  scanf("%d", &N);

  for (i = 1; i <= N; i++)
  {
    printf("Who wants in (E=1)(D=2)(C=3)(M=4)(P=5): \n");
    fflush(stdout);
    scanf("%d", &type);
    if ((pid = fork()) == -1)
    {
      /* Fork failed! */
      perror("fork");
      exit(1);
    }

    if (pid == CHILD)
    {
      pid = getpid();
      switch (type)
      {

      case 1: /* Elephant code*/
        printf("     Elephant process with pid %d wants in.\n", pid);
        fflush(stdout);
        sem_wait(mutex[0]);
        printf("     Elephant process with pid %d is in.\n", pid);
        fflush(stdout);
        sleep(rand() % 10);
        printf("     Elephant process with pid %d is out.\n", pid);
        fflush(stdout);
        sem_post(mutex[0]);
        break;

      case 2: /*Dog code*/
        printf("     Dog process with pid %d wants in.\n", pid);
        fflush(stdout);
        sem_wait(mutex[1]);
        printf("     Dog process with pid %d is in.\n", pid);
        fflush(stdout);
        sleep(rand() % 10);
        printf("     Dog process with pid %d is out.\n", pid);
        fflush(stdout);
        sem_post(mutex[1]);
        break;

      case 3: /*Cat Code*/
        printf("     Cat process with pid %d wants in.\n", pid);
        fflush(stdout);
        sem_wait(mutex[1]);
        sem_wait(mutex[2]);
        sem_wait(mutex[4]);
        printf("     Cat process with pid %d is in.\n", pid);
        fflush(stdout);
        sleep(rand() % 10);
        printf("     Cat process with pid %d is out.\n", pid);
        fflush(stdout);
        sem_post(mutex[1]);
        sem_post(mutex[2]);
        sem_post(mutex[4]);
        break;

      case 4: /*Mouse code*/
        printf("     Mouse process with pid %d wants in.\n", pid);
        fflush(stdout);
        sem_wait(mutex[3]);
        sem_wait(mutex[0]);
        sem_wait(mutex[4]);
        printf("     Mouse process with pid %d is in.\n", pid);
        fflush(stdout);
        sleep(rand() % 10);
        printf("     Mouse process with pid %d is out.\n", pid);
        fflush(stdout);
        sem_post(mutex[3]);
        sem_post(mutex[0]);
        sem_post(mutex[4]);
        break;

      case 5: /*Parrot  Code*/
        printf("     Parrot process with pid %d wants in.\n", pid);
        fflush(stdout);
        sem_wait(mutex[3]);
        sem_wait(mutex[2]);
        printf("     Parrot process with pid %d is in.\n", pid);
        fflush(stdout);
        sleep(rand() % 10);
        printf("     Parrot process with pid %d is out.\n", pid);
        fflush(stdout);
        sem_post(mutex[3]);
        sem_post(mutex[2]);
        break;
      }
      exit(0);
    }
  }

  /* Now wait for the child processes to finish */
  for (i = 1; i <= N; i++)
  {
    pid = wait(&status);
    printf("Child (pid = %d) exited with status %d.\n", pid, status);
    fflush(stdout);
  }
}
