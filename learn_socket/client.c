#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <unistd.h>
int main(){

  // create a socket
  int network_socket = socket(AF_INET, SOCK_STREAM,0);

  // specify the address for the socket 
  struct sockaddr_in server_address;  
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8080);
  server_address.sin_addr.s_addr = INADDR_ANY;

  // connection request
  int connection_status;
  connection_status = connect(network_socket,(struct sockaddi*) &server_address, sizeof(server_address));
  
  if(connection_status == -1){
    printf("error\n\n");
  }

  // receive the data from the server
  char msg[256];
  recv(network_socket, &msg,sizeof(msg),0);

  printf("received --> %s\n",msg);
  close(network_socket);
  return 0;
} 
