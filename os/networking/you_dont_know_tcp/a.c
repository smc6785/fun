// POSIX operating system API.
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

char buffer[1000000];

int main()
{
	memset(buffer, 'a', sizeof(buffer));
	int sock = socket(AF_INET, SOCK_STREAM, 0);  

  struct sockaddr_in remote;  
  remote.sin_family = AF_INET;
	// htons for hostshort to netshort.
	// ntohs for netshort to hostshort.
  remote.sin_port = htons(8080);
  remote.sin_addr.s_addr = INADDR_ANY;
  inet_pton(AF_INET, "127.0.0.1", &remote.sin_addr);

	connect(sock, (void*)&remote, sizeof(remote));
	write(sock, buffer, sizeof(buffer));
	close(sock);
	return 0;
}


/*
	Test one:
		nc -l -p 8080
		telnet localhost 8080
	Test two:
		nc -l -p 8080
		./a
	
    clone from other machine directly.
    git clone ssh://10.0.0.193:8022/data/data/com.termux/files/home/fun/.git
 */
