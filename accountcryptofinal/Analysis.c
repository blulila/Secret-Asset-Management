#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "type.h"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_BLUE "\x1b[94m"
#define ANSI_COLOR_RESET "\x1b[0m"

void Analysis(List *list) //가계부 분석 및 추천
{
        List *head = NULL;
        List *Recent = NULL;
        List *update = NULL;
        List *temp;
        head = list;

        int money[5] = {0,0,0,0,0};
        int part[5] = {0};
        int a;
        int use = 0;
        int get = 0;
        int i = 0;

        while (head != NULL)
        {
                if (strcmp(head->name, "transmit") == 0) //교통비 합계 저장 및 카테고리 사용빈도 측정
                {
                        money[0] = money[0] + head->price;
                        part[0]++;
                        use = use + head->price;
                }
                else if (strcmp(head->name, "life") == 0)//생활비 합계 저장 및 카테고리 사용빈도 측정

                {
                        money[1] = money[1] + head->price;
                        part[1]++;
                        use = use + head->price;
                }


                if (strcmp(head->name, "culture") == 0)//문화비 합계 저장 >및 카테고리 사용빈도 측정
                {
                        money[2] = money[2] + head->price;
                        part[2]++;
                        use = use + head->price;
                }

                else if (strcmp(head->name, "food") == 0)//식비 합계 저장 >및 카테고리 사용빈도 측정

                {
                       money[3] = money[3] + head->price;
                       part[3]++;
                       use = use + head->price;
               }
                else if (strcmp(head->name, "deposit") == 0)//입금 합계 저>장 및 카테고리 사용빈도 측정
               {
                        money[4] = money[4] + head->price;
                        part[4]++;
                        get = get + head->price;
                }
                i++;
                head = head->link;
        }

	while(1) {
	        printf("\n\n\t┌───────────────────────────────────────────────────────────────────────┐\n");
		printf("\t│\t\t                                       \t\t\t│\n");
		 printf("\t│\t\t\t   Welcome to the "ANSI_COLOR_BLUE" B A N K " ANSI_COLOR_RESET"\t\t\t│\n");
        	printf("\t│\t\t                                       \t\t\t│\n");
        	printf("\t└───────────────────────────────────────────────────────────────────────┘\n\n");
        	printf(ANSI_COLOR_BLUE"\n\t\t\t\t  1. 최고금액 소비항목  \n\n "ANSI_COLOR_RESET);
        	printf(ANSI_COLOR_BLUE"\t\t\t\t  2. 최다횟수 소비항목  \n\n "ANSI_COLOR_RESET);
        	printf(ANSI_COLOR_BLUE"\t\t\t\t  3. 소비내역 합계  \n\n "ANSI_COLOR_RESET);
		printf(ANSI_COLOR_BLUE"\t\t\t\t  4. 최근내역 조회  \n\n "ANSI_COLOR_RESET);
		printf(ANSI_COLOR_BLUE"\t\t\t\t  5. 종료  \n\n "ANSI_COLOR_RESET);
        	printf("\n\t\t\t\t☺ 번호를 입력하세요:___\b\b");
        
	int choice;
	scanf("%d", &choice);
        getchar();
        int check = 0;

        if (choice == 1)
        {
                int max = 0; //정해진 카테고리 내에서 가장 많은 돈 출력
                for (int i = 0; i < 4; i++)
                {
                        if (max < money[i])
                        {
                                max = money[i];
                                a = i;
                        }
                }

		if (a == 0)
                {
   			printf("\n\n\n\t┌───────────────────────────────────────────────────────────────────────┐\n");
        		printf("\t│\t\t                                       \t\t\t│\n");
        		printf("\t│\t\t             교통비 : %d               \t\t\t│\n",money[0]);
        		printf("\t│\t => 교통비가 많이 나오는 사람들을 위한 Transit Card                        │\n");
        		printf("\t│\t 혜택 1:  교통비가 월 10만원>이상 나오는 고객에게 2%% 캐시백│\n");
        		printf("\t│\t 혜택 2:  택시비 야간할증 면제                                             │\n");
        		printf("\t│\t 혜택 3:  환승 5번 가능                                                    │\n");
			printf("\t│\t >  절약 가능 금액 : %.f\t\t\t\t\t│\n", (float)(money[0] * 2 / 100));
			printf("\t└───────────────────────────────────────────────────────────────────────┘\n\n");
                }
                else if (a == 1)
                {
                        printf("\n\n\n\t┌───────────────────────────────────────────────────────────────────────┐\n");
                        printf("\t│\t\t                                       \t\t\t│\n");
                        printf("\t│\t\t             생활비 : %d    \t\t\t│\n",money[1]);
                        printf("\t│\t => 소소한 절약을 위한 선택 Discount  Card\t\t\t│\n");
                        printf("\t│\t 혜택 1:  가맹점 이용시 추가할인(세부정보에서 가맹점 확인 요망) │\n");
                        printf("\t│\t 혜택 2:  결제금액의 0.1 포인트 적립                            │\n");
                        printf("\t│\t         (해당카드 온라인 포인트 매장에서 사용가능)             │\n");
			printf("\t│\t 혜택 3:  다이쏘 전매장 5% 추가할인                             │\n");
                        printf("\t│\t   >  절약 가능 금액 : %.f\t\t\t\t\t│\n", (float)(money[1] * 0.002));
                        printf("\t└───────────────────────────────────────────────────────────────────────┘\n\n");
                }
                else if (a == 2)
                {
                        printf("\n\n\n\t┌───────────────────────────────────────────────────────────────────────┐\n");
                        printf("\t│\t\t                                       \t\t\t│\n");
                        printf("\t│\t\t             문화비 : %d    \t\t\t│\n",money[2]);
                        printf("\t│\t => 문화를 즐기는 사람을 위한 Culture Card\t\t\t│\n");
                        printf("\t│\t 혜택 1:  문화와 관련된 결제시  포인트 적립\t\t\t│\n");
                        printf("\t│\t 혜택 2:  CGB에서 영화 10회 관람시 1회 무료 관람   \t\t│\n");
                        printf("\t│\t          (무료 관람은 월 1회 가능)                \t\t│\n");
			printf("\t│\t 혜택 3:  각종 콘서트 추가 할인(세부사항 확인 요망)\t\t│\n");
                        printf("\t│\t  >  절약 가능 금액 : %.f \t\t\t\t\t│\n", (float)(money[2] * 0.001));
			printf("\t└───────────────────────────────────────────────────────────────────────┘\n\n");
                }
                else if (a == 3)
                {
                        printf("\n\n\n\t┌───────────────────────────────────────────────────────────────────────┐\n");
                        printf("\t│\t\t                                       \t\t\t│\n");
                        printf("\t│\t\t             음식비 : %d    \t\t\t│\n",money[3]);
                        printf("\t│\t => 맛집 투어를 위한 Culture Card                 \t\t│\n");
                        printf("\t│\t 혜택 1:  음식점에서 결제시 0.2% 적립             \t\t│\n");
                        printf("\t│\t 혜택 2:  VIPSS에서 결제시 와인 서비스            \t\t│\n");
                        printf("\t│\t 혜택 3:  식비합 100.000 이상 결제시 여행 자동응모\t\t│\n");
                        printf("\t│\t >  절약 가능 금액 : %.f\t\t\t\t\t│\n", (float)(money[3] * 0.001));
                        printf("\t└───────────────────────────────────────────────────────────────────────┘\n\n");
			
                }
		continue;
        }

        else if (choice == 2) //카테고리 빈도를 통한 가장많은 카테고리 사용빈도 출력
        {
                printf("\n\t> 최다횟수 소비항목: ");

                int max = 0;
                for (int i = 0; i < 4; i++)
                {
                        if (max < part[i])
                        {
                                max = part[i];
                                a = i;
                        }
                }

                if (a == 0)
                {
                        printf(" 교통비 (%d 회)\n", part[0]);
                }
                else if (a == 1)
                {
                        printf(" 생활비 (%d 회)\n", part[1]);

                }
                else if (a == 2)
                {
                        printf(" 음식비 (%d 회)\n", part[2]);
                }
                else if (a == 3)
                {
                        printf(" 문화비 (%d 회)\n", part[3]);
                }
		continue;
        }

        else if (choice == 3) //총 수입 지출로 자신의 입금 출금 내역 비교
        {
                printf("\n\t> 지출 : %d\n", use);
                printf("\t> 수입 : %d\n", get);
		continue;
        }

        else if (choice == 4) //최근내역만 출금으로 자신의 최근 소비패턴 파악가능
        {
                head = list;
                int count = 0;
                while (head != NULL)
                {
                        check++;
                        if (head->date > 200501)
                        {
                                count++;
                        }
                        head = head->link;
                }
                head = list;
                Recent = (List*)malloc(sizeof(List)*count); //최근 정보만 >받기 위한 어레이로 메모리 할당
                int i = 0;

                printf("\n\n\t   카테고리   날짜     가격\n");
                printf("\t┌────────┬──────────┬─────────┐\n");
                while (head != NULL)
                {
                        if (head->date > 200501)
                        {
                                Recent[i] = *head;
                                i++;
                        }
                        head = head->link;
                }
                for (int i = count - 1; i >= 0; i--) //stack을 구현으로 최>근 목록을 출력
                {
                        printf("\t│%7s │ %8d │ %6d  │\n", Recent[i].name, Recent[i].date, Recent[i].price);
                }
                printf("\t└────────┴──────────┴─────────┘\n"); //최근내역
                free(Recent);
		continue;
        }
	else if (choice == 5)
	{
		return;
	}

        else	{
               	printf("\n\t\t> 번호를 다시 입력해주세요. \n");
               	continue;               }
	}
}
