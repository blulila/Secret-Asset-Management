#define ANSI_COLOR_BLUE "\x1b[94m"
#define ANSI_COLOR_RESET "\x1b[0m"
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
#include <openssl/evp.h>
#include <openssl/aes.h>

#define IPADDR "127.0.0.1"

void *do_keyboard(void *);
void *do_socket(void *);
void AES_encryption(char plainfn[], char cipherfn[], unsigned char key[],unsigned char iv[]);
void AES_decryption(char cipherfn[], char plainfn[], unsigned char key[], unsigned char iv[]);
char quit[] = "quit";
pthread_t pid[2];

void chatting(void *socket) {

	int thr_id, status;
	int buf[1];	
	int connSock = *((int *) socket);
	
	printf("\n\n\t┌───────────────────────────────────────────────────────────────────────┐\n");
	printf("\t│\t\t                                       \t\t\t│\n");
	printf("\t│\t\t\t   Welcome to the "ANSI_COLOR_BLUE" 비밀 채팅 " ANSI_COLOR_RESET"\t\t\t│\n");
	printf("\t│\t\t                                       \t\t\t│\n");
	printf("\t└───────────────────────────────────────────────────────────────────────┘\n\n");
	printf(ANSI_COLOR_BLUE"\n\t\t\t\t  1. 가계부 이용법 문의  \n\n "ANSI_COLOR_RESET);
	printf(ANSI_COLOR_BLUE"\t\t\t\t  2. 소비 습관 분석 및 개선점  \n\n "ANSI_COLOR_RESET);
	printf(ANSI_COLOR_BLUE"\t\t\t\t  3. 추천 금융상품 안내  \n\n "ANSI_COLOR_RESET);
	printf(ANSI_COLOR_BLUE"\t\t\t\t  4. 기타 문의  \n\n "ANSI_COLOR_RESET);
	printf("\n\t\t\t\t☺ 번호를 입력하세요:___\b\b");
        scanf("%d", &buf[0]);
	getchar();
        while(buf[0] <= 0 || buf[0] >= 5) {
                        printf("\t\t\t\t > 다시 입력하세요 : ");
                        scanf("%d", &buf[0]);
        		getchar();
			continue;
	}

	write(connSock, buf, sizeof(buf));

	printf("\n\t\t\t\t> 상담을 시작합니다.\n\n");
	printf("상담을 종료하실려면 quit을 입력해주세요\n\n\n");

	buf[0] = '\0';
	thr_id = pthread_create(&pid[0], NULL, do_keyboard, (void *)&connSock);
	thr_id = pthread_create(&pid[1], NULL, do_socket, (void *)&connSock);

	pthread_join(pid[0], (void **)&status);
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
		if (strncmp(sbuf, quit, 4) == 0) 
		{
                       	write(connSock, sbuf, n);
			pthread_exit(0);
			sbuf[0]='\0';
                }
		else
		{
		printf("입력하신 메시지내용을 암호화하여 안전하게 전송합니다\n");
                AES_encryption(sbuf,enc,mykey,iv);
                m=sizeof(enc);
                enc[m]='\0';
		printf("암호화한 메시지 :  %s\n\n\n", enc);
                write(connSock, enc, m);
		enc[0]='\0';
		sbuf[0]='\0';
		}
        }
}





void *do_socket(void *data) {
        int n;
        char rbuf[BUFSIZ];
        char dec[BUFSIZ];
        int connSock = *((int*) data);
        unsigned char mykey[] = "01234567890123456789012345678\0";
        unsigned  char iv[] = "0123456789012\0";

        while (1) {
                if ((n = read(connSock, rbuf, BUFSIZ)) > 0) {
			printf("암호화된 메시지가 도착했습니다\n");
			printf("암호문 : %s\n",rbuf);
			printf("복호화를 진행합니다\n");
                        AES_decryption(rbuf,dec,mykey,iv);
			printf("server : ");
                        printf("%s\n\n\n", dec);
                        if (strncmp(dec, quit, 4) == 0) {
                                pthread_kill(pid[0], SIGINT);
                                break;
                        }
		dec[0]='\0';
		rbuf[0]='\0';
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








