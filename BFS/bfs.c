#include <stdio.h>
#include <stdlib.h>

#define RELATIONS 10
#define VERTICES 20

typedef struct node{
  int data;
  struct node* adj[RELATIONS];
} node;

node* new_node(int value);
void add_adj(node *graph[], int src, int dest);

void bfs(node *graph[], int start);

//utility for emulating queue
typedef struct queue_node{
  node *data;
  struct queue_node *next;
} queue_node;

queue_node* new_q_node(node *val);
void add_q_node(queue_node **head, node *val);




int main(){

  node* graph[VERTICES];
  int i;
  for(i = 0; i < VERTICES; ++i)
  {
    graph[i] = new_node(i);
  }

  add_adj(graph, 0, 2);
  add_adj(graph, 0, 3);
  add_adj(graph, 0, 1);
  add_adj(graph, 1, 5);
  add_adj(graph, 5, 8);
  add_adj(graph, 8, 12);
  add_adj(graph, 8, 14);
  add_adj(graph, 12, 16);
  bfs(graph, 0);
  return 0;
}


void bfs(node *graph[], int start)
{
  // nodes to be proccesed are put at the end
  // next node is at the top(@head)
  queue_node* head = new_q_node(graph[start]);

  while(head != NULL)
  {
    node* current = head->data;
    head = head->next;

    int i = 0;
    //add all adjacencies of current node
    //wont work for cyclic graph, "visited" array needed for cyclic
    while(current->adj[i] != NULL)
    {
      add_q_node(&head, current->adj[i]);
      i++;
    }

    printf("%d ", current->data);
  }
  return;
}

node* new_node(int value)
{
  node* tmp = malloc(sizeof(node));
  tmp->data = value;
  for(int i = 0; i < RELATIONS; ++i)
  {
    tmp->adj[i] = NULL;
  }
  return tmp;
}

void add_adj(node *graph[], int src, int dest)
{
  if((src < 0) || (dest > VERTICES))
  {
    printf("out of bounds!\n(%d, %d)\n", src, dest);
    return;
  }
  if (!graph[src] || !graph[dest])
  {
    printf("one of nodes not defined!\n(%d, %d)\n", src, dest);
    return;
  }

  node* tmp = graph[src];
  int i = 0;
  while(tmp->adj[i] != NULL)
  {
    i++;
  }
  tmp->adj[i] = graph[dest];
}


queue_node* new_q_node(node *val)
{
  queue_node* tmp = malloc(sizeof(queue_node));
  tmp->data = val;
  tmp->next = NULL;

  return tmp;
}

void add_q_node(queue_node **head, node *val)
{
  queue_node *tmp = *head;
  if(tmp == NULL)
  {
    *head = new_q_node(val);
  }
  else
  {
    while(tmp->next != NULL)
      tmp = tmp->next;
    tmp->next = new_q_node(val);
    return;
  }
}
