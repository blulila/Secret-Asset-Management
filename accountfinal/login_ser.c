#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h> 

pthread_t pid;
void *do_keyboard(void *);
void *do_socket(void *);
pthread_t thr_id[2];

void *input(void *);
char *UserDataCompare(char *, void *);
char *UserDataInput(char *);

char out[] = "exit";
char quit[] = "quit";
char modfi[] = "modf";
char end[] = "end";
char user_chat[10];

int main(int argc, char *argv[]) {

	int thr_id;
	int status;

	int listenSock, connSock;
	struct sockaddr_in client_addr, server_addr;

	int len;
	int num;
	char buf[64];

	if (argc < 2) {
		printf("Usage : talk_server port_num\n");
		return -1;
	}

	if ((listenSock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Server : Can't open socket\n");
		return -1;
	}

	memset((char *)&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(argv[1]));

	if (bind(listenSock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		printf("talk Server Can't bind\n");
		return -1;
	}

	listen(listenSock, 1);

	len = sizeof(client_addr);

	while(1) {
		if ((connSock = accept(listenSock, (struct sockaddr *) &client_addr, &len)) < 0) {
			printf("Talk Server failed in accepting\n");
			return -1;
		}

		printf("Talk Server accept new request\n");

		thr_id = pthread_create(&pid, NULL, input, (void *) &connSock);

		if(thr_id != 0) {
			perror("Thread Create Error");
			exit(1);
		}
	}

	close(listenSock);
	close(connSock);
}

void *input(void *data) {
	
	int status;
	int n;
	char* file;
	char buf[64];
	int connSock = *((int*)data);
	
	char chat[] = "chat";
	char sentence[256];
	char *rst;
	FILE *fp;
	FILE *fp2;

	while ((n = read(connSock, buf, BUFSIZ)) > 0) {
		buf[n] = '\0';
		strcpy(user_chat, buf);
		file = UserDataCompare(buf, (void *) &connSock);
		break;
	}
		fp = fopen(file, "r+");

		if(fp == NULL) {
			printf("ERROR\n");
			exit(1);
		}
		
		while((n = read(connSock, buf, BUFSIZ)) > 0) {
			if(strncmp(buf, modfi, 4) == 0) { // ?????? ????????? ??????
				// txt ????????? ?????? ??? ??? ????????? ????????? ????????? ????????? ???????????? ????????? ?????? ?????? ???????????? ????????? ???????????? ?????????.
			}
			if(strncmp(buf, chat, 4) == 0) { // ?????? ??????
		
				buf[0] = '\0';
	
				printf("\n?????? ????????? ??????????????????.\n");
				printf("????????? ?????? ?????? ????????? ");

				while(1) {
					if(read(connSock, buf, 1) > 0) {
						printf("%d", (int) *buf);
						break;
					}
				}

				printf("??? ?????????.\n");
				printf("????????? ???????????????.\n\n");

				pthread_create(&thr_id[0], NULL, do_keyboard, (void *) &connSock);
				pthread_create(&thr_id[1], NULL, do_socket, (void *) &connSock);
				pthread_join(thr_id[0], (void **)&status);
				pthread_join(thr_id[1], (void **)&status);
			}	
			else if (n > 10) { // ?????? ????????? ????????? ??????
				fputs(buf, fp);
			}
			if(fgets(sentence, sizeof(sentence), fp) != NULL) { 
				write(connSock, sentence, 256);
			}
			else{
				write(connSock, out, 4);
			}
		}
		fclose(fp);
}

void *do_keyboard(void *data) { // ????????? ?????? ????????? ?????? ??????
	int n;
	char sbuf[BUFSIZ];
	int connSock = *((int*) data);
	
	while ((n = read(0, sbuf, BUFSIZ)) > 0) {
		if (write(connSock, sbuf, n) != n) {
			printf("Talk Server fail in sending\n");
		}
	}
}

void *do_socket(void *data) { // ?????? ?????? ??????
	int n;
	char rbuf[BUFSIZ];
	int connSock = *((int*) data);
	int count = 0;
	while(1) {
		count++;

		if (((n = read(connSock, rbuf, BUFSIZ)) > 0)&&count>1) {
			rbuf[n] = '\0';
			printf("%s : ", user_chat);
			printf("%s", rbuf);
			if (strncmp(rbuf, quit, 4) == 0) {
				printf("????????? ?????????????????????.\n");
			}
		}
	}	
}

char *UserDataCompare(char *user, void *socket) { // ?????? ????????? ?????? ??????

	char auth[20] = "Authentication\n";
	char fail[50] = "??? ???????????? ?????????????????????.\n";
	char *username;
	char txt[10] = ".txt";
	char buffer[20];

	int connSock = *((int *) socket);
	
	FILE *fp;
	fp = fopen("UserData.txt", "r");
	
	if (fp == NULL) {
		printf("ERROR\n");
		exit(1);
	}

	while(1) {
		fgets(buffer, sizeof(buffer), fp);
		buffer[strlen(buffer) - 1] = '\0';
		if(strcmp(buffer, user)==0) {
			write(connSock, auth, 20);
			strcat(user,txt); 
			return user;
			break;
		}
		if(feof(fp)) {
			write(connSock, fail, 50);
			username = UserDataInput(user);
			return username;
			break;
		}
	}
	fclose(fp);
}

char *UserDataInput(char *user) { // ????????? ???????????? ???????????? ????????? ?????? ??????

	char txt[10] = ".txt";
	char null[10] = "null";

	FILE *fp;
	FILE *UserData;

	UserData = fopen("UserData.txt", "a");	

	fputs(user, UserData);
	fputc('\n', UserData);

	strcat(user, txt);	
	fp = fopen(user, "w");
	fprintf(fp, "%s %d %d\n", null, 0, 0);	
	fclose(fp);
	fclose(UserData);

	return user;
}
