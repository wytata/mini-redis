#include "stdio.h"
#include "stdlib.h"
#include "sys/socket.h"
#include "sys/errno.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "string.h"

void EXITONERROR(char* message) {
	printf("%s\n", message);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sock;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		EXITONERROR("Error: Failed to create socket.");
	}

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8000);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	if ((bind(sock, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr))) != 0) {
		EXITONERROR("Error: Failed to bind socket.");
	}

	if (listen(sock, 10) != 0) {
		EXITONERROR("Error: Failed to listen on socket.");
	}

	while (1) {
		struct sockaddr_in clientAddr;
		socklen_t clientSize = sizeof(clientAddr);
		if (accept(sock, (struct sockaddr*)&clientAddr, &clientSize) == -1) {
			EXITONERROR("Error: failed to accept incoming request.");
		}
		printf("Received connection from host %s\n", inet_ntoa(clientAddr.sin_addr));
	}


	return 0;
}
