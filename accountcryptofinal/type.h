typedef struct List //항목, 가격, 날짜를 입력받기 위한 구조체 선언
{
        char name[100];
        int price;
        int date;
        struct List *link;
} List;

void chatting(void *);
void monitor(void *);
void Search(struct List *list);
void Analysis(List *list);
void Modify(List *list, void *);
void DoLogin(void *);
