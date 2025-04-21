#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#include <pthread.h>

typedef struct node
{
  struct node* next;
  int *client_socket;
}node_t;

node_t* g_head = NULL;
node_t* g_tail = NULL;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
/* condition variable: lets threads wait until
    something happens and it can do useful work. */
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

void enqueue(int *data)
{
  node_t *new_node = malloc(sizeof(node_t));
  new_node->client_socket = data;
  new_node->next = NULL;
  if(g_tail==NULL)
  {
    g_head = new_node;
  }else{
    g_tail->next = new_node;
  }
  g_tail = new_node;
}

int* dequeue()
{
  int* result;
  if(g_head!=NULL)
  {
    result =g_head->client_socket;
    g_head = g_head->next;
    if(g_head == NULL)
    {
      g_tail = NULL;
    }
  }else{
    result =  NULL;
  }
  return result;
}

void* handle_connection(void* client_socket)
{
  char server_message[256]= "HTTP/1.1 200 OK\nContent-Type:text/plain\nContent-Length:12\n\n helloworld!";
  int client = *(int*)client_socket;
  char buffer[256] = {0};
  read(client, buffer,256);
  printf("server read %s\n", buffer);
  write(client, server_message, 256);
  printf("-----------hello from server send ------\n");
  return NULL;
}

void* thread_function(void *arg)
{
  while(1)
  {
    pthread_mutex_lock(&mutex);
    int *pclient = dequeue();
    if( pclient ==NULL)
    {
      pthread_cond_wait(&condition_var, &mutex);
      pclient = dequeue();
    }
    pthread_mutex_unlock(&mutex);
    if (pclient!=NULL)
    {
      /* There is a connection. */
      handle_connection(pclient);
    }
  }
  return NULL;
}

int main(){

  // createing the server socket
  int server_socket = socket(AF_INET, SOCK_STREAM,0);
  // define the server address
  struct sockaddr_in server_address;
  socklen_t addrlen =sizeof(server_address);

  pthread_t thread_pool[5];
  /* Create a bunch of threads to handle future connections. */
  for(int i =0; i<5;i++)
  {
    pthread_create(&thread_pool[i], NULL, thread_function, NULL);
  }

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8080);
  server_address.sin_addr.s_addr =INADDR_ANY;

  // bind the IP and port to the server
  bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

  // liste at the port
  listen(server_socket,5);
  int client_socket;
  while(1)
  {
    client_socket = accept(server_socket, (struct sockaddr*)&server_address, &addrlen);

    int *pclient = malloc(sizeof(int));
    *pclient = client_socket;
    pthread_mutex_lock(&mutex);
    enqueue(pclient);
    pthread_cond_signal(&condition_var);
    pthread_mutex_unlock(&mutex);

    #if 0
    pthread_t t;
    int *pclient = malloc(sizeof(int));
    *pclient = client_socket;
    pthread_create(&t, NULL, handle_connection, pclient);
    #endif
    //handle_connection(client_socket);

    //send the meesgae on the client address
    //send(client_socket,server_message, sizeof(server_message),0);
  }
  return 0;
}

