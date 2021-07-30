#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "type.h"

#define IPADDR "127.0.0.1"

void DoLogin(void *);

int main(int argc, char *argv[]) {

	int connSock;
	struct sockaddr_in server_addr;
	char *serverAddr;
	int serverPort;

	int thr_id, status;
	int len;
	int num;

	if (argc != 3) {
		printf("Usage : talk_client server_ip port_num");
		return -1;
	}
	else {
		serverAddr = argv[1];
		serverPort = atoi(argv[2]);
	}

	if ((connSock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Talk Client Can't open socket\n");
		return -1;
	}

	memset((char *)&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(IPADDR);
	server_addr.sin_port = htons(serverPort);

	if (connect(connSock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		printf("talk Client Can't bind\n");
		return -1;
	}
	
	printf("Talk client accept new request\n\n");

	DoLogin((void *)&connSock);

	close(connSock);
}

void DoLogin(void *data) {
	
	char buf[1024];
	char id[20];
	int connSock = *((int*)data);
	int n;

	printf("LOGIN : ");
	scanf("%s", id);

	write(connSock, id, 20);

	while((n = read(connSock, buf, BUFSIZ)) > 0) {
			buf[n] = '\0';
			printf("%s", buf);
			break;
	}
	
	monitor((void *) &connSock);
}

