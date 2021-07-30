#define _CRT_SECURE_NO_WARNINGS
#define ANSI_COLOR_BLUE "\x1b[94m"
#define ANSI_COLOR_RESET "\x1b[0m"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "type.h"

void monitor(void* socket)
{
        char menu [4][50] = {"Search", "Modify", "Analysis", "Exit"};
        List *node = NULL;
        List *pre = NULL;
        List *list = NULL;
        List *next = NULL;

        char sentence = '\0';
        int choice = 0;
        int choice2 = 0;
        int key = 0;
        int i=0;
	int count_=0;
	int recv_len;
	char quit[] = "exit";
	int connSock = *((int *) socket);
	char buf[64];
	char tmp[64];
	char chat[] = "chat";

        FILE *fp;

		while(1) {
			char *sentence;
			char *ptr;
			int price = 0;
			int date = 0;

			node = (List *)malloc(sizeof(List));
                        if (node == NULL)
			{
				printf("Error\n");
				exit(1);
			}
				
			send(connSock, (char *) &choice2, sizeof(int), 0);
			if((recv_len = read(connSock, buf, BUFSIZ)) > 0) {
					
					if(strncmp(buf, quit, 4) == 0) break;
	
					buf[recv_len] = '\0';
					strcpy(tmp, buf);
	
					ptr = strtok(tmp," ");
					sentence = ptr;

					ptr = strtok(NULL, " ");
					price = atoi(ptr);
					ptr = strtok(NULL, " ");
					date = atoi(ptr);

				
			strcpy(node->name, sentence);
			node->price = price;
			node->date = date;

			if (list == NULL) list = node;
			else pre->link = node;
			node->link = NULL;
			pre = node;
			count_++;
			}
	}
	while(1) {
        printf("\n\n\t┌───────────────────────────────────────────────────────────────────────┐\n");
        printf("\t│\t\t                                       \t\t\t│\n");
        printf("\t│\t\t Welcome To the \x1b[31mS\x1b[0mecret \x1b[31mA\x1b[0msset \x1b[31mM\x1b[0management\t\t\t│\n");
        printf("\t│\t\t                                       \t\t\t│\n");
        printf("\t└───────────────────────────────────────────────────────────────────────┘\n\n");
        printf("\n\t\t\t\t  \x1b[31m 1. 자 산 관 리 \x1b[0m  \n\n ");
        printf("\t\t\t\t  \x1b[31m 2. 자 산 분 석 \x1b[0m  \n\n ");
        printf("\t\t\t\t  \x1b[31m 3. 비 밀 채 팅 \x1b[0m \n\n ");
        printf("\t\t\t\t  \x1b[31m 4. 종 료       \x1b[0m \n \n\n ");
        printf("\n\t\t\t\t☺ 번호를 입력하세요:___\b\b");
        scanf("%d", &choice2);
	getchar();
        printf("\n\n");
	
	if (choice2 == 1) //가계부 조회 및 수정
	{
                while(1)
                {
                        
        		printf("\n\n\t┌───────────────────────────────────────────────────────────────────────┐\n");
        		printf("\t│\t\t                                       \t\t\t│\n");
        		printf("\t│\t\t\t   Welcome to the "ANSI_COLOR_BLUE" B A N K " ANSI_COLOR_RESET"\t\t\t│\n");
        		printf("\t│\t\t                                       \t\t\t│\n");
        		printf("\t└───────────────────────────────────────────────────────────────────────┘\n\n");
        		printf(ANSI_COLOR_BLUE"\n\t\t\t\t  1. 가계부 조회  \n\n "ANSI_COLOR_RESET);
        		printf(ANSI_COLOR_BLUE"\t\t\t\t  2. 가계부 수정  \n\n "ANSI_COLOR_RESET);
        		printf(ANSI_COLOR_BLUE"\t\t\t\t  3. 종료  \n\n "ANSI_COLOR_RESET);
        		printf("\n\t\t\t\t☺ 번호를 입력하세요:___\b\b");
			scanf("%d", &choice);
			getchar();
                        if (choice == 1) //가계부 조회
                        { Search(list); }
                        else if (choice == 2) //가계부 수정
                        { Modify(list, (void *) &connSock); }
                        else if (choice == 3) { break; }
			else {
 				printf("\n\t\t> 번호를 다시 입력해주세요. \n");
                		continue;               }
                }
		continue;
	}
	else if (choice2 == 2) //가계부 분석 및 추천
        {        while(1)
                {
                      	Analysis(list);
			break;
         	}
		continue;
	}
	else if (choice2 == 3)//비밀채팅
	{
		send(connSock, chat, 4, 0);
		chatting((void *) &connSock);
		continue;	
	}
	else if (choice2 == 4)
	{	exit(1);
		break;	}
	else
	{	printf("\n\t\t> 번호를 다시 입력해주세요. \n");
		continue;		}
	}
}
