#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "type.h"

void Modify(List *list, void* socket) //가계부 수정
{
        List *newnode; //새로운 목록을 받기 위한 하나의 구조체 선언
        List *head = NULL;
        head = list;
	List *l = list;

        int choice = 0;
	int count_ = 0;
	int n;
	int len;
	int connSock = * ((int *) socket);
	
	char rst[128];
	char modf[] = "modf";
	char end[] = "end";
	char buf[64];

        while (1)
        {
        	printf("\n\n\t────────────────────────────────────────────────────\n");
                printf("\t 1.추가  2.수정  3.뒤로\n");
                printf("\n\t> 번호를 입력하세요: ");
                scanf("%d", &choice);

                if (choice == 1)
                {
                        newnode = (List*)malloc(sizeof(List)); //입금 목록>을 위한 구조체 newnode에 메모리 할당
                        newnode->link = NULL;
			printf("\n\t────────────────────────────────────────────────────\n");
                        printf("\t(항목)\t 1.교통  2.생활  3.문화  4.음식  5.저축 \n");
                        int choice;
                        printf("\n\t> 번호를 입력하세요: ");

                        scanf("%d", &choice); getchar();

                        if (choice == 1)
                                strcpy(newnode->name, "transit"); //교통비>에 대한 값 삽입
                        else if (choice == 2)
                                strcpy(newnode->name, "life"); //생활비에 >대한 값 삽입
                        else if (choice == 3)
                                strcpy(newnode->name, "culture"); //문화비>에 대한 값 삽입
                        else if (choice == 4)
                                strcpy(newnode->name, "food"); //음식에 대>한 값 삽입
                        else if (choice == 5)
                                strcpy(newnode->name, "deposit"); //입금에 대한 값 삽입

                        printf("\n\t> 가격을 입력하세요: ");
                        scanf("%d", &newnode->price); //돈 입력
                        getchar();

                        printf("\n\t> 날짜를 입력하세요: ");
                        scanf("%d", &newnode->date); //날짜 입력
                        getchar();

                        while (head->link != NULL) //linked list의 마지막 노드 검색
                        {
                              head = head->link;
                        }
                        head->link = newnode; //마지막 노드의 포인터에 newnode 연결
			
			sprintf(rst, "%s %d %d\n", newnode->name, newnode->price, newnode->date);
			send(connSock, rst, sizeof(rst), 0);
			printf("\n\t%s", rst);
                        
			head = list;
			count_++;
                }
                else if (choice == 2)
                {
			struct List tmp;
			int check = 0;

			printf("\n\t   카테고리    가격     날짜\n");
			printf("\t┌──────────┬────────┬─────────┐\n");

			while (list != NULL)
                	{
                                printf("\t│ %8s │ %6d │  %6d │\n", list->name, list->price, list->date);
                        list = list->link;
                	}
			printf("\t└──────────┴────────┴─────────┘\n");

                        printf("\n\t────────────────────────────────────────────────────\n");
			printf("\n\t> 수정할 내역을 입력하세요.\n");
                        printf("\t(항목)  transit / life / culture / food / deposit\n");

			send(connSock, modf, 4, 0);

			while(1) {
			
				printf("\n\t항목: "); scanf("%s", tmp.name);
                        	printf("\t가격: "); scanf("%d", &tmp.price);
                        	printf("\t날짜: "); scanf("%d", &tmp.date);

				while (l != NULL)
        	                {
                	               	if (!strcmp(l->name, tmp.name) && l->price == tmp.price && l->date == tmp.date)
                        	       	{
                                	       	printf("\t수정할 항목: "); scanf("%s", l->name);
                                       		printf("\t수정할 가격: "); scanf("%d", &l->price);
                                       		printf("\t수정할 날짜: "); scanf("%d", &l->date);
						check++;
					}
                               		l = l->link;
				}
				l = list;
				if(check == 1) break;
				printf("INPUT AGAIN!"); // 데이터 비교 실패 시 출력
			}

			l = list;
			while (l != NULL)
                        {
				len = sprintf(rst, "%s %d %d\n", l->name, l->price, l->date);
				rst[len] = '\0';
				printf("%s\n", rst);
				l = l->link;
			}
			break;
		}
                else break;
        }
}
