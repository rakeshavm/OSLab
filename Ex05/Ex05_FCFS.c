#include<stdio.h>
#include<stdlib.h>
char pid[10][10];
int at[10];
int bt[10];
int st[10];
int ft[10];
int tat[10];
int rt[10];
int wt[10];
int curr;
int n;
int p_done[10];
struct node { 
  int data; 
  int bt; 
  struct node* next;   
};
typedef struct node Node;  
Node *front=NULL;
Node *rear=NULL;
Node* newNode(int d, int p); 
void dequeue(Node** front);
void enqueue(Node** front, int d, int p);
void initialise()
{
  for(int i=0;i<n;i++)
    {
      wt[i]=-1;
      p_done[i] = 0;
    }
}

// this function is used to check whether all the process are over or not
int is_all_process_done()
{
  for (int i=0;i<n;i++)
    {
      if(p_done[i]==0)
	return 0;
    }
  return 1;
}


Node* add_process_to_queue(int time)
{
  for(int i=0;i<n;i++)
   {
     if(at[i]==time)
       {
        enqueue(&front,i,bt[i]);
       }  
   }
  return front;
}

int main()
{

  /*
    variable meanings
    pid : it is a 2D character array that will the process name 
          (the program uses the index at which a particular process id is stored to do caculations.)
    at : array of arrival time of the processes
    bt : array of burst time of the processes
    st : array of starting time of the processes
    ft : array of finishing time of the processes
    wt : array of waiting time of the processes
    tat : array of turn around time for the processes 
    rt : array of response time for the processes
    p_done : the reference array that is used to check whether the particular processes is arrived or not.
    time : time elapsed
    w : this variable will contain the total waiting time 
        (this is used to calculate the average waiting time)
    t :  this variable will contain the sum of total turn around time 
        (this is used to calculate the average TAT)  
    r : this variable will contain the total response time 
        (this is used to calculate the average response time)
    curr: this will hold the index of the current process that is being executed.


    A priority Queue is maintained to push the store the pre-emited process 
    front pointer of the queue will have the most prior process to be executed next.

   */

  // Initialising all variables.
  int time=0;
  int w=0,t=0,r=0;
  printf("Enter the number of process to be executed: ");
  scanf("%d",&n);
  for(int i=0;i<n;i++)
   {
     printf("Enter process id: ");
     scanf("%s",pid[i]);
     printf("Enter arrival time: ");
     scanf("%d",&at[i]);
     printf("%d",at[i]);
     printf("Enter burst time: ");
     scanf("%d",&bt[i]);
   } 
  initialise();
  
  front= add_process_to_queue(time);
  if (front != NULL)
    {
      curr = front->data; 
      dequeue(&front);
    }
  int pt=0;
  while(!is_all_process_done()||front!=NULL)
    {

      
      pt=time;
      st[curr]=time;

      
      while(bt[curr]!=0)
	{
	  if(front!=NULL && bt[curr]-time>bt[front->data])
	     break;
          time++;
          front= add_process_to_queue(time);
          bt[curr]--;
	}

      
      if(bt[curr]-time<bt[front->data])
	{
          time--;
	}
      if(wt[curr]==-1)
	{
	  rt[curr]=st[curr]-at[curr];
	  r+=rt[curr];
	}
      if(wt[curr]==-1)
	wt[curr]=st[curr]-at[curr];
      else
	wt[curr] = wt[curr]+(pt-ft[curr]);
      ft[curr]=time;
      if(bt[curr]==0)
	{
	  tat[curr]=ft[curr]-at[curr];
	  t+=tat[curr];
	  w+=wt[curr];
	}
      else
	{  
	  enqueue(&front,curr,bt[curr]);
	}
      
      printf("%s \t %d \t %d \t %d \t %d \t %d \t",pid[curr],at[curr],bt[curr],st[curr],ft[curr],wt[curr] );
      if(wt[curr]==-1)
	{
	  printf("--\t");
	  p_done[curr]=1;
	}
      else 
	{
	  printf("%d\t",tat[curr]);
	}
      if(wt[curr]==-1)
	{
	  printf("%d\n",rt[curr]);
	}
      else 
	{
	  printf("--\n");
	}
      if(front!=NULL)
	{
	  curr=front->data;
	  dequeue(&front);
       }
      time++;
      
    }
  
}

/* ======================================================== 
   Priority Queue Implementation
   ========================================================== */

Node* newNode(int d, int p) 
{ 
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = d; 
    temp->bt = p; 
    temp->next = NULL;
    return temp; 
} 
void dequeue(Node** front) 
{ 
  Node* temp = *front; 
  (*front) = (*front)->next; 
  free(temp); 
} 
void enqueue(Node** front, int d, int p) 
{ 
  Node* start = (*front);  
  Node* temp = newNode(d, p);
  if(start==NULL)
    {
      *front=temp;
    }
  else if ((*front)->bt > p)
    {
      temp->next = *front; 
      (*front) = temp; 
    } 
  else { 
    while (start->next != NULL &&  start->next->bt <p)
      { 
	start = start->next; 
      } 
    temp->next = start->next; 
    start->next = temp; 
  } 
}

