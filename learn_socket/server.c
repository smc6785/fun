#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
int main(){
  char server_message[256]= "HTTP/1.1 200 OK\nContent-Type:text/plain\nContent-Length:12\n\n helloworld!";

  // createing the server socket
  int server_socket = socket(AF_INET, SOCK_STREAM,0);
  // define the server address
  struct sockaddr_in server_address;
  int addrlen =sizeof(server_address);

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
    char buffer[256] = {0};
    read(client_socket, buffer,256);
    printf("server read %s\n", buffer);
    write(client_socket, server_message, 256);
    printf("-----------hello from server send ------\n");

    // sned the meesgae on the client address
    //send(client_socket,server_message, sizeof(server_message),0);
  }
  return 0;
}

