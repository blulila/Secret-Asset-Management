#include <stdio.h>
#include <string.h>
#include "type.h"

void Search(struct List *list) //가계부 조회
{
        int a,b;

        printf("\n");
        printf("\n\t────────────────────────────────────────────────────\n");
        printf("\t 1.항목  2.가격  3.날짜(ex:200527)  4.입출금  5.뒤로\n");
        printf("\n\t> 번호를 입력하세요: ");
        scanf("%d", &a);

        if (a == 1) //카테고리에 따른 입출금 내역
        {
		printf("\n\t────────────────────────────────────────────────────\n");
                printf("\t 1.교통  2.생활  3.문화  4.음식  5.저축\n");
                printf("\n\t> 번호를 입력하세요: ");
                scanf("%d", &b);
		printf("\n\t────────────────────────────────────────────────────");
                printf("\n\t   카테고리    가격     날짜\n");
                printf("\t┌──────────┬────────┬─────────┐\n");

                if (b == 1) //교통비
                {
                        while (list != NULL)
                        {
                                if (strcmp(list->name, "transit") == 0)
                                {
                                        printf("\t│ %8s │ %6d │  %6d │\n", list->name, list->price, list->date);
                                }
                                list = list->link;
                        }
                }
                else if (b == 2) //생활비
                {
                        while (list != NULL)
                        {
                                if (strcmp(list->name,"life") == 0)
                                {
                                         printf("\t│ %8s │ %6d │  %6d │\n", list->name, list->price, list->date);

                                }
                                list = list->link;
                        }
                }
                else if (b == 3) //문화비
                {
                        while (list != NULL)
                        {
                                if (strcmp(list->name, "culture") == 0)
                                {
                                        printf("\t│ %8s │ %6d │  %6d │\n", list->name, list->price, list->date);
                                }
                                list = list->link;
                        }
                }
                else if (b == 4) //식비
                {
                        while (list != NULL)
                        {
                                if (strcmp(list->name, "food") == 0)
                                {
                                        printf("\t│ %8s │ %6d │  %6d │\n", list->name, list->price, list->date);
                                }
                                list = list->link;
                        }
                }
                else if (b == 5) //저축
                {
                        while (list != NULL)
                        {
                                if (strcmp(list->name, "deposit") == 0)
                                {
                                        printf("\t│ %8s │ %6d │  %6d │\n", list->name, list->price, list->date);
                                }
                                list = list->link;
                        }
                }
                else
                {
                        printf("\t not valid\n\n");
                }
                printf("\t└──────────┴────────┴─────────┘\n");
        }

        else if (a == 2) //가격 상하한값에 따른 내역
        {
                int c, d;
                printf("\n\t────────────────────────────────────────────────────");
		printf("\n\t> 가격 하한값을 입력하세요: ");
                scanf("%d", &c); getchar();
                printf("\n\t> 가격 상한값을 입력하세요: ");
                scanf("%d", &d); getchar();
		printf("\n\t────────────────────────────────────────────────────");
                printf("\n\t   카테고리    가격     날짜\n");
                printf("\t┌──────────┬────────┬─────────┐\n");

                while (list != NULL)
                {
                        if (list->price >= c && list->price <= d) //가격 상하한값 입력
                        {
                                printf("\t│ %8s │ %6d │  %6d │\n", list->name, list->price, list->date);
                        }
                        list = list->link;
                }
                printf("\t└──────────┴────────┴─────────┘\n");

        }

        else if (a == 3) //날짜에 따른 내역
        {
                int c, d;
		printf("\n\t────────────────────────────────────────────────────");
                printf("\n\t> 날짜 하한을 입력하세요 (ex.200527):  ");
                scanf("%d", &c); getchar();
                printf("\n\t> 날짜 상한을 입력하세요 (ex.200527):  ");
                scanf("%d", &d); getchar();
                printf("\n\t %d ~ %d 사이 결제 정보를 검색합니다.\n", c, d);
		printf("\n\t────────────────────────────────────────────────────");
		printf("\n\t   날짜    카테고리     가격\n");
                printf("\t┌────────┬──────────┬─────────┐\n");

                while (list != NULL)
                {
                        if (c <= list->date && d >= list->date) //날짜 상하한값 입력
                        {
                                printf("\t│ %6d │ %8s │  %6d │\n", list->date, list->name, list->price);
                        }
                        list = list->link;
                }
                printf("\t└────────┴──────────┴─────────┘\n");
        }

        else if (a == 4) //입출금 내역
        {
		printf("\n\t────────────────────────────────────────────────────");
                printf("\n\t 1. 입금  2. 출금  \n");
                int check = 0;
                printf("\n\t> 번호를 입력하세요: ");
                scanf("%d", &check);
		printf("\n\t────────────────────────────────────────────────────");
                printf("\n\t   카테고리   날짜     가격\n");
                printf("\t┌────────┬──────────┬─────────┐\n");

        if (check == 1) //입금 내역
                {
                        while (list != NULL)
                        {
                                if (strcmp(list->name, "deposit") == 0)
                                {
                                        printf("\t│%6s │ %8d │ %6d  │\n", list->name, list->date, list->price);
                                }
                                list = list->link;
                        }
                }
        else if (check == 2) //출금 내역
                {
                        while (list != NULL)
                        {
                                if (strcmp(list->name, "deposit"))
                                {
                                        printf("\t│%7s │ %8d │ %6d  │\n", list->name, list->date, list->price);
                                }
                                list = list->link;
                        }
                }
                printf("\t└────────┴──────────┴─────────┘\n");
        }
}
