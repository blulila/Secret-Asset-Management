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

#define IPADDR "127.0.0.1"

void *do_keyboard(void *);
void *do_socket(void *);

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
        while(buf[0] <= 0 || buf[0] >= 5)
        {
                printf("\t\t\t\t > 다시 입력하세요 : ");
                scanf("%d", &buf[0]);
                getchar();
                continue;
        }

        write(connSock, buf, sizeof(buf));

        printf("\n\t\t\t\t> 상담을 시작합니다.\n\n");
	printf("상담을 종료할려면 quit을 입력하세요\n\n\n");
        thr_id = pthread_create(&pid[0], NULL, do_keyboard, (void *)&connSock);
        thr_id = pthread_create(&pid[1], NULL, do_socket, (void *)&connSock);

        pthread_join(pid[0], (void **)&status);
}

void *do_keyboard(void *data) {
	int n;
	char sbuf[BUFSIZ];
	int connSock = *((int*)data);

	while ((n = read(0, sbuf, BUFSIZ)) > 0) {
		if (write(connSock, sbuf, n) != n) {
			printf("Talk Server fail in sending\n");
		}
		if (strncmp(sbuf, quit, 4) == 0) {
			pthread_exit(0);
		}
	}
}

void *do_socket(void *data) {
	int n;
	char rbuf[BUFSIZ];
	int connSock = *((int *)data);

	while (1) {
		if ((n = read(connSock, rbuf, BUFSIZ)) > 0) {
			rbuf[n] = '\0';
			printf("server : ");
			printf("%s", rbuf);
			if (strncmp(rbuf, quit, 4) == 0) {
				pthread_kill(pid[0], SIGINT);
				break;
			}
		}
	}
}
