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
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <openssl/evp.h>
#include <openssl/aes.h>


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


void AES_encryption(char plainfn[], char cipherfn[], unsigned char key[],unsigned char iv[]);
void AES_decryption(char cipherfn[], char plainfn[], unsigned char key[], unsigned char iv[]);





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
			if(strncmp(buf, modfi, 4) == 0) { // 수정 데이터 반영
				// txt 파일을 열어 한 줄 단위로 데이터 수정을 시도해 보았으나 정확한 값을 찾아 수정하기 어려워 구현하지 못했다.
			}
			if(strncmp(buf, chat, 4) == 0) { // 채팅 연결
		
				buf[0] = '\0';
	
				printf("\n상담 요청이 들어왔습니다.\n");
				printf("고객의 상담 요청 내용은 ");

				while(1) {
					if(read(connSock, buf, 1) > 0) {
						printf("%d", (int) *buf);
						break;
					}
				}

				printf("번 입니다.\n");
				printf("상담을 시작합니다.\n\n");

				pthread_create(&thr_id[0], NULL, do_keyboard, (void *) &connSock);
				pthread_create(&thr_id[1], NULL, do_socket, (void *) &connSock);
				pthread_join(thr_id[0], (void **)&status);
				pthread_join(thr_id[1], (void **)&status);
			}	
			else if (n > 10) { // 입력 데이터 파일에 반영
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

void *do_keyboard(void *data) {
        int n;
        int m;
        char sbuf[BUFSIZ];
        char enc[BUFSIZ];
        int connSock = *((int*)data);
        unsigned char mykey[] = "01234567890123456789012345678\0";
        unsigned  char iv[] = "0123456789012\0";

        while ((n = read(0, sbuf, BUFSIZ)) > 0) {
		printf("입력하신 메시지내용을 암호화하여 안전하게 전송합니다\n");
                AES_encryption(sbuf,enc,mykey,iv);
                m=sizeof(enc);
                enc[m]='\0';
		printf("암호화한 메시지 : %s\n\n\n",enc);
                write(connSock, enc, m);
		enc[0]='\0';
		sbuf[0]='\0';
                }
        }


	

		

void *do_socket(void *data) {
        int n;
        char rbuf[BUFSIZ];
        char dec[BUFSIZ];
        int connSock = *((int*) data);
        unsigned char mykey[] = "01234567890123456789012345678\0";
        unsigned  char iv[] = "0123456789012\0";
	int count=0;

        while (1) {
	
		count++;
                if (((n = read(connSock, rbuf, BUFSIZ)) > 0)&&count>1) {
                        rbuf[n] = '\0';
			AES_decryption(rbuf,dec,mykey,iv);
			if (strncmp(rbuf, quit, 4) == 0)
			{
                                printf("상담이 종료되었습니다,\n");
				count = 0;
				rbuf[0]='\0';
				dec[0]='\0';
			
                        }
			else
			{
				printf("암호화된 메시지가 도착했습니다\n");
                        	printf("암호문 : %s\n",rbuf);
                        	printf("복호화를 진행합니다\n");
                        	printf("%s : ",user_chat);
                        	printf("%s\n\n\n", dec);
				rbuf[0]='\0';
				dec[0]='\0';
			}
                }


        }

}


void AES_encryption(char plainfn[], char cipherfn[], unsigned char key[],unsigned char iv[])
{

        EVP_CIPHER_CTX ctx;
        int in_len, out_len, len_final=0;
        in_len=strlen(plainfn);
        EVP_CIPHER_CTX_init(&ctx);
        EVP_CipherInit_ex(&ctx,EVP_aes_128_cbc(),NULL,key,iv,AES_ENCRYPT);
        EVP_CipherUpdate(&ctx,cipherfn,&out_len,plainfn,in_len);
        len_final=out_len;
        EVP_CipherFinal_ex(&ctx,cipherfn+out_len,&out_len);
        out_len += len_final;
        EVP_CIPHER_CTX_cleanup(&ctx);
}

void AES_decryption(char cipherfn[], char plainfn[], unsigned char key[], unsigned char iv[])
{

        EVP_CIPHER_CTX ctx;
        int in_len, out_len,len_final=0;
        in_len=strlen(cipherfn);
        EVP_CIPHER_CTX_init(&ctx);
        EVP_CipherInit_ex(&ctx,EVP_aes_128_cbc(),NULL,key,iv,AES_DECRYPT);
        EVP_CipherUpdate(&ctx,plainfn,&out_len,cipherfn,in_len);
        len_final=out_len;
        EVP_CipherFinal_ex(&ctx,plainfn+out_len,&out_len);
        out_len += len_final;
        EVP_CIPHER_CTX_cleanup(&ctx);
}





char *UserDataCompare(char *user, void *socket) {

	char auth[20] = "Authentication\n";
	char fail[50] = "새 사용자가 생성되었습니다.\n";
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

char *UserDataInput(char *user) {

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
