#include <sys/ipc.h> 
# define NULL 0 
#include <sys/shm.h> 
#include <sys/types.h> 
# include<unistd.h> 
# include<stdio.h> 
# include<stdlib.h> 
# include<string.h> 
#include <sys/wait.h> 
#include <stdio_ext.h> 

int main() 
{ 
  int pid; 
  char *a;
  int id,n,i;
  int flag=0;
  char temp[50];
  id=shmget(111,50, 00666);
  a=shmat(id,NULL,0); 
 char *s=(char*)malloc(50);
  strcpy(s,"*");
  char k='*';
  while(1)
    {
      while(k=='*')
	{
	  k=a[0];
	 
	}
      printf("Your friend: ");
      for(int i=1;a[i]!='\0';i++)
      printf("%c",a[i]);
      printf("\n");
     

      printf("YOU: ");
      scanf("%s",temp);
      
     
   
      strcpy(s,"*");
      strcat(s,temp);
      strcpy(a,s);
       k='*';
       if(strcmp("bye",temp)==0 || strcmp("#bye",a)==0 ||strcmp("*bye",a) ==0)
	flag=1;
    
       if(flag==1)
	{
	  // strcpy(a,"*bye");
	  shmdt(a);
	  sleep(10);
	  shmctl(id, IPC_RMID,NULL);
	  exit(0);
	}
   
      flag=0;
    }
}
