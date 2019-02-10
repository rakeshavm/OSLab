#include<stdio.h>
#include<stdlib.h>

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


int main()

{
  enqueue(&front,67,1);
  enqueue(&front,67,2);
  enqueue(&front,67,5);
  enqueue(&front,67,4);
  enqueue(&front,67,3);
  for(Node *temp=front;temp!=NULL;temp=temp->next)
    printf("%d  ---> %d\n",temp->data,temp->bt);
}
