#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "type.h"

int main()
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

        FILE *fp;

        printf("\n\n\t┌───────────────────────────────────────────────────────────────────────┐\n");
        printf("\t│\t\t                                       \t\t\t│\n");
        printf("\t│\t\t Welcome To the \x1b[31mS\x1b[0mecret \x1b[31mA\x1b[0msset \x1b[31mM\x1b[0management\t\t\t│\n");
        printf("\t│\t\t                                       \t\t\t│\n");
        printf("\t└───────────────────────────────────────────────────────────────────────┘\n\n");
        printf("\n\t\t\t\t  \x1b[31m 1. 자 산 관 리 \x1b[0m  \n\n ");
        printf("\t\t\t\t  \x1b[31m 2. 자 산 분 석 \x1b[0m  \n\n ");
        printf("\t\t\t\t  \x1b[31m 3. 비 밀 채 팅 \x1b[0m \n \n\n ");
        printf("\n\t\t\t\t☺ 번호를 입력하세요:___\b\b");
        scanf("%d", &choice2);
        printf("\n\n");

        switch(choice2)
        {
        case 1: //가계부 조회 및 수정
                while(1)
                {
                        A:fp = fopen("account.txt", "r");
                                if (fp == NULL)
                                {
                                        printf("ERROR\n");
                                        exit(1);
                                }

                        while(1) //파일에서 항목, 가격, 날짜를 불러와서 linked list에 저장
                        {
                                char sentence[100] = "";
                                int price;
                                int date;
                                node = (List *)malloc(sizeof(List));
                                        if (node == NULL)
                                        {
                                                printf("Error\n");
                                                exit(1);
                                        }
                                fscanf(fp,"%s %d %d", sentence, &price, &date);
                                strcpy(node->name, sentence);
                                node->price = price;
                                node->date = date;
                                if (!feof(fp))
                                {
                                        if (list == NULL)
                                                list = node;
                                        else
                                                pre->list = node;
                                        node->list = NULL;
                                        pre = node;
                                        count_++;
                                }
                                else break;
                        } fclose(fp);

                        printf("\n\tWelcome To The Credit Note \n\n");
                        printf("\t=========================");
                        printf("\n\t     Select Menu\n");
                        printf("\n\t     1.가계부 조회\n");
                        printf("\n\t     2.가계부 수정\n");
                        printf("\n\t     3.종료\n");
                        printf("\t=========================\n");
                        scanf("%d", &choice);

                        if (choice == 1) //가계부 조회
                        { Search(list); }
                        else if (choice == 2) //가계부 수정
                        { Modify(list); }
                        else if (choice == 3) //종료
                        { exit(1); }

                        node = list;
                        while (node->list != NULL) //메모리 해제를 통한 메>모리 관리
                        {
                                next = node->list;
                                free(node);
                                node = next;
                        }
                        list = NULL;
                        goto A;
                }
        case 2: //가계부 분석 및 추천
                while(1)
                {
                         B:fp = fopen("account.txt", "r");
                                if (fp == NULL)
                                {
                                        printf("ERROR\n");
                                        exit(1);
                                }

                        while(1)
                        {
                                char sentence[100] = "";
                                int price;
                                int date;
                                node = (List *)malloc(sizeof(List));
                                        if (node == NULL)
                                        {
                                                printf("Error\n");
                                                exit(1);
                                        }
                                fscanf(fp,"%s %d %d", sentence, &price, &date);
                                strcpy(node->name, sentence);
                                node->price = price;
                                node->date = date;
                                if (!feof(fp))
                                {
                                        if (list == NULL)
                                                list = node;
                                        else
                                                pre->list = node;
                                        node->list = NULL;
                                        pre = node;
                                        count_++;
                                }
                                else break;
                        } fclose(fp);

                        Analysis(list);

                        node = list;
                        while (node->list != NULL)
                        {
                                next = node->list;
                                free(node);
                                node = next;
                        }
                        list = NULL;
                        goto B;
                }
        case 3: //비밀채팅
                printf("서비스를 준비 중입니다.\n\n");
        }
}
