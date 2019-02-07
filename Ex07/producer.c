#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h> // for semaphore operations sem_init,sem_wait,sem_post
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <sys/types.h>
#include<unistd.h>
extern int errno;
#define SIZE 10 /* size of the shared buffer*/
#define VARSIZE 1 /* size of shared variable=1byte*/
#define INPUTSIZE 20
#define SHMPERM 0666 /* shared memory permissions */
int segid; /* id for shared memory bufer */
int empty_id;
int full_id;
int mutex_id;
char * buff;
char * input_string;
sem_t *empty;
sem_t *full;
sem_t *mutex;
int p=0;

int main()
{
  int i=0;
  pid_t temp_pid;
  segid = shmget (100, SIZE, IPC_CREAT | IPC_EXCL | SHMPERM );
  empty_id=shmget(101,sizeof(sem_t),IPC_CREAT|IPC_EXCL|
		  SHMPERM);
  full_id=shmget(102,sizeof(sem_t),IPC_CREAT|IPC_EXCL|
		 SHMPERM);
  mutex_id=shmget(103,sizeof(sem_t),IPC_CREAT|IPC_EXCL|
		  SHMPERM);
  buff = shmat( segid, (char *)0, 0 );
  empty = shmat(empty_id,(char *)0,0);
  full = shmat(full_id,(char *)0,0);
  mutex = shmat(mutex_id,(char *)0,0);
  // Initializing Semaphores Empty , Full & Mutex
  sem_init(empty,1,1);
  sem_init(full,1,0);
  sem_init(mutex,1,1);
  printf("\n Producer Process Started \n");
 
  while (i<10)
    {
      int val = random()%10;
      printf("\nProducer %d trying to aquire Semaphore Empty \n",getpid());
      sem_wait(empty);
      
      printf("\nProducer %d successfully aquired Semaphore Empty \n",getpid());
      printf("\nProducer %d trying to aquire Semaphore Mutex \n",getpid());
      sem_wait(mutex);
      
      printf("\nProducer %d successfully aquired Semaphore Mutex \n",getpid());
      buff[p]=(char)val;
      printf("\nProducer %d Produced Item [ %d ] \n",getpid(),val);
      i++;
      p++;
      printf("\nItems in Buffer %d \n",p);
      sem_post(mutex);
      printf("\nProducer %d released Semaphore Mutex \n",getpid());

      sem_post(full);
      printf("\nProducer %d released Semaphore Full \n",getpid());
      sleep(2/random());
    } //while




  
  
  shmdt(buff);
  shmdt(empty);
  shmdt(full);
  shmdt(mutex);
  
  printf("\n Producer process exited \n\n");
  return(0);
} //main
