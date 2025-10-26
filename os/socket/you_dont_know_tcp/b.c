#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

char buffer[4096];

int main()
{
  struct sockaddr_in local;  
  local.sin_family = AF_INET;
  local.sin_port = htons(8080);
  inet_pton(AF_INET, "10.0.0.193", &local.sin_addr);

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	bind(sock, (void*)&local, sizeof(local));
	listen(sock, 128);
	int client = accept(sock, NULL, NULL);
	write(client, "220 Welcome\r\n", 13);

	int bytesRead=0, res;
	for(;;) {
			res = read(client, buffer, sizeof(buffer));
			if(res < 0)  {
					perror("read");
					break;
			}
			if(!res)
					break;
			bytesRead += res;
	}
	printf("%d\n", bytesRead);
	return 0;
}
