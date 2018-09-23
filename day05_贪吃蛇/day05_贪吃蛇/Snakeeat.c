#include "Snakeeat.h"

////��ӡ��Ϸ�˵�
//void PrintMenu(Game *game)
//{
//	int i = 0;
//	int j = 0;
//	COORD pos;
//	for (; i <= game->width + 1; i++)
//	{
//		for (; j <= game->height + 1; j++)
//		{
//			if ((0 == i) || (game->width + 1 == i))
//			{
//				pos.X = j;
//				pos.Y = i;
//				HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//				SetConsoleCursorPosition(handle, pos);
//				printf("��");
//			}
//			else{
//				if ((0 == j) || (game->width + 1 == j))
//				{
//					pos.X = j;
//					pos.Y = i;
//					HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//					SetConsoleCursorPosition(handle, pos);
//					printf("��");
//				}
//			}
//		}
//	}
//}

//��ӡ��Ϸ�˵�
void PrintMenu(Game *game)
{
	printf("������������������������������������������     ����������������\n");
	printf("��                                      ��     ��            ��\n");
	printf("��                                      ��     ����������������\n");
	printf("��                                      ��\n");
	printf("��                                      ��\n");
	printf("��                                      ��\n");
	printf("��                                      ��\n");
	printf("��                                      ��\n");
	printf("��                                      ��\n");
	printf("��                                      ��\n");
	printf("��                                      ��\n");
	printf("��                                      ��\n");
	printf("��                                      ��\n");
	printf("��                                      ��\n");
	printf("��                                      ��\n");
	printf("��                                      ��\n");
	printf("��                                      ��\n");
	printf("��                                      ��\n");
	printf("��                                      ��\n");
	printf("��                                      ��\n");
	printf("������������������������������������������\n");
}

//�������ͷ��
void SnakePushfront(Node **shead, int x, int y)
{
	//���һ���½ڵ�
	Node *node = (Node *)malloc(sizeof(Node));
	node->pos.x = x;
	node->pos.y = y;
	node->next = *shead;
	*shead = node;
}

//�������βɾ
void SnakePopback(Node **shead)
{
	Node *newtail = *shead;
	while (!(newtail->next->next == NULL)){
		newtail = newtail->next;
	}
	Node *wfree = newtail->next;
	COORD pos;
	pos.X = wfree->pos.x;
	pos.Y = wfree->pos.y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
	printf("  ");
	free(wfree);
	newtail->next = NULL;
}

//���߽��г�ʼ��
/*
	���ǵ����ǵ��ߵ��ƶ�ʵ���Ͼ���һ������ͷ�壬βɾ�Ķ�̬��ʾ��
	�������ǻὫ�����ͷ�壬βɾ��װΪ�������������Դ˴��ĳ�ʼ��ʹ��ͷ���ʼ����
*/
void SnakeInit(Game *game)
{
	//�����ʼ��̰���ߵĳ�ʼ����Ϊ����2,3��,(4,3),(6,3)
	game->Snake.shead = NULL;
	SnakePushfront(&game->Snake.shead, 2, 3);
	SnakePushfront(&game->Snake.shead, 4, 3);
	SnakePushfront(&game->Snake.shead, 6, 3);
	game->Snake.direc = RIGHT;

	//������ʼ��Ϊ0�����ʼ��Ϊ20���߳�ʼ��Ϊ20,�ٶȳ�ʼ��Ϊһ��������
	game->score = 0;
	game->width = 20;
	game->height = 20;
	game->speed = 500;
}

//��������
void SnakeDeatory(Game *game)
{
	Node *cur = game->Snake.shead;
	Node *last = cur;
	while (cur!=NULL)
	{
		last = cur;
		cur = cur->next;
		free(last);
	}
}

//���һ��ʳ��
void GetFood(coor *food, Game *game)
{
	srand((unsigned int)time(NULL));
	do{
		food->x = rand() % (2 * game->width);
		food->y = rand() % (game->height);
	}while (!((0 == food->x % 2)&&(food->x >= 2)&&(food->y >= 2)));
}

//�õ�̰���ߵ���һ�����ꣻ
coor Gtenextcoor(Game *game)
{
	coor nextcoor;
	switch (game->Snake.direc)
	{
	case UP:
	{
		nextcoor.x = game->Snake.shead->pos.x;
		nextcoor.y = game->Snake.shead->pos.y - 1;
	}
	break;
	case DOWN:
	{
		nextcoor.x = game->Snake.shead->pos.x;
		nextcoor.y = game->Snake.shead->pos.y + 1;
	}
	break;
	case LEFT:
	{
		nextcoor.x = game->Snake.shead->pos.x - 2;
		nextcoor.y = game->Snake.shead->pos.y;
	}
	break;
	case RIGHT:
	{
		nextcoor.x = game->Snake.shead->pos.x + 2;
		nextcoor.y = game->Snake.shead->pos.y;
	}
	break;
	}
	return nextcoor;
}

//�ж��Ƿ�����
BOOL Ishitwall(coor nextcoor, Game *game)
{
	if ((nextcoor.x < 1) || (nextcoor.x >= game->width*2)
		|| (nextcoor.y < 1) || (nextcoor.y >= game->height))
	{
		return TRUE;
	}
	return FALSE;
}

//�ж��Ƿ�ҧ���Լ�
BOOL Iseatenself(coor nextcoor, Game *game)
{
	Node *cur = game->Snake.shead->next;
	for (; cur != NULL; cur = cur->next)
	{
		if (nextcoor.x == cur->pos.x && nextcoor.y == cur->pos.y)
		{
			return TRUE;
		}
	}
	return FALSE;
}

//��ӡ��
void SnakePrint(Game *game)
{
	COORD pos;
	Node *cur = game->Snake.shead;
	for (; cur != NULL; cur = cur->next)
	{
		pos.X = cur->pos.x;
		pos.Y = cur->pos.y;
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(handle, pos);
		if (cur == game->Snake.shead)
		{
			printf("͹");
		}
		else{
			printf("��");
		}
	}
}

//��ӡʳ��
void FoodPrint(coor food)
{
	COORD pos;
	pos.X = food.x;
	pos.Y = food.y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
	printf("��");
}

//���ѡ����
void playerchose(Game *game)
{
	if (GetAsyncKeyState(VK_DOWN)&&(game->Snake.direc != UP)){
		game->Snake.direc = DOWN;
	}
	else if (GetAsyncKeyState(VK_UP) && (game->Snake.direc != DOWN)){
		game->Snake.direc = UP;
	}
	else if (GetAsyncKeyState(VK_LEFT) && (game->Snake.direc != RIGHT)){
		game->Snake.direc = LEFT;
	}
	else if (GetAsyncKeyState(VK_RIGHT) && (game->Snake.direc != LEFT)){
		game->Snake.direc = RIGHT;
	}
}

//��ӡ����
void ScorePrint(Game *game)
{
	COORD pos;
	pos.X = 49;
	pos.Y = 1;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
	printf("SCORE:%4d",game->score);
}

//����ΪSetConsoleCursorPosition()�����������Ĺ��β�����ص�
void HideCursorForSetConsoleCursorPosition()
{
	HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);  //��þ��
	CONSOLE_CURSOR_INFO info;  //�ն˹����Ϣ�Ľṹ��
	/*
		typedef struct CONSOLE_CURSOR_INFO{
			DWORD dwSize;  //���İٷֱȺ�ȡ�
			BOOL bVisible;  //����Ƿ�ɼ� 
		}CONSOLE_CURSOR_INFO,PCONSOLE_CURSOR_INFO;
	*/
	GetConsoleCursorInfo(hStdOutput, &info); //��ȡ�ն˹����Ϣ
	info.bVisible = 0; //���ع��
	//info.dwSize = 0; //���ù��İٷֱȺ�ȣ�ʵ��Ϊ����ȣ�
	SetConsoleCursorInfo(hStdOutput, &info); //�����ն˹����Ϣ
}