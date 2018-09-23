#include "Snakeeat.h"

////打印游戏菜单
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
//				printf("▉");
//			}
//			else{
//				if ((0 == j) || (game->width + 1 == j))
//				{
//					pos.X = j;
//					pos.Y = i;
//					HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//					SetConsoleCursorPosition(handle, pos);
//					printf("▉");
//				}
//			}
//		}
//	}
//}

//打印游戏菜单
void PrintMenu(Game *game)
{
	printf("▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉     ▉▉▉▉▉▉▉▉\n");
	printf("▉                                      ▉     ▉            ▉\n");
	printf("▉                                      ▉     ▉▉▉▉▉▉▉▉\n");
	printf("▉                                      ▉\n");
	printf("▉                                      ▉\n");
	printf("▉                                      ▉\n");
	printf("▉                                      ▉\n");
	printf("▉                                      ▉\n");
	printf("▉                                      ▉\n");
	printf("▉                                      ▉\n");
	printf("▉                                      ▉\n");
	printf("▉                                      ▉\n");
	printf("▉                                      ▉\n");
	printf("▉                                      ▉\n");
	printf("▉                                      ▉\n");
	printf("▉                                      ▉\n");
	printf("▉                                      ▉\n");
	printf("▉                                      ▉\n");
	printf("▉                                      ▉\n");
	printf("▉                                      ▉\n");
	printf("▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉▉\n");
}

//蛇链表的头插
void SnakePushfront(Node **shead, int x, int y)
{
	//获得一个新节点
	Node *node = (Node *)malloc(sizeof(Node));
	node->pos.x = x;
	node->pos.y = y;
	node->next = *shead;
	*shead = node;
}

//蛇链表的尾删
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

//对蛇进行初始化
/*
	考虑到我们的蛇的移动实际上就是一个链表头插，尾删的动态表示。
	所以我们会将链表的头插，尾删封装为两个函数，所以此处的初始化使用头插初始化。
*/
void SnakeInit(Game *game)
{
	//这里初始化贪吃蛇的初始坐标为：（2,3）,(4,3),(6,3)
	game->Snake.shead = NULL;
	SnakePushfront(&game->Snake.shead, 2, 3);
	SnakePushfront(&game->Snake.shead, 4, 3);
	SnakePushfront(&game->Snake.shead, 6, 3);
	game->Snake.direc = RIGHT;

	//分数初始化为0，宽初始化为20，高初始化为20,速度初始化为一秒两步。
	game->score = 0;
	game->width = 20;
	game->height = 20;
	game->speed = 500;
}

//销毁链表
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

//获得一个食物
void GetFood(coor *food, Game *game)
{
	srand((unsigned int)time(NULL));
	do{
		food->x = rand() % (2 * game->width);
		food->y = rand() % (game->height);
	}while (!((0 == food->x % 2)&&(food->x >= 2)&&(food->y >= 2)));
}

//得到贪吃蛇的下一步坐标；
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

//判断是否碰壁
BOOL Ishitwall(coor nextcoor, Game *game)
{
	if ((nextcoor.x < 1) || (nextcoor.x >= game->width*2)
		|| (nextcoor.y < 1) || (nextcoor.y >= game->height))
	{
		return TRUE;
	}
	return FALSE;
}

//判断是否咬到自己
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

//打印蛇
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
			printf("凸");
		}
		else{
			printf("⊙");
		}
	}
}

//打印食物
void FoodPrint(coor food)
{
	COORD pos;
	pos.X = food.x;
	pos.Y = food.y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
	printf("◆");
}

//玩家选择方向
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

//打印分数
void ScorePrint(Game *game)
{
	COORD pos;
	pos.X = 49;
	pos.Y = 1;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos);
	printf("SCORE:%4d",game->score);
}

//将因为SetConsoleCursorPosition()函数而产生的光标尾巴隐藏掉
void HideCursorForSetConsoleCursorPosition()
{
	HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);  //获得句柄
	CONSOLE_CURSOR_INFO info;  //终端光标信息的结构体
	/*
		typedef struct CONSOLE_CURSOR_INFO{
			DWORD dwSize;  //光标的百分比厚度。
			BOOL bVisible;  //光标是否可见 
		}CONSOLE_CURSOR_INFO,PCONSOLE_CURSOR_INFO;
	*/
	GetConsoleCursorInfo(hStdOutput, &info); //获取终端光标信息
	info.bVisible = 0; //隐藏光标
	//info.dwSize = 0; //设置光标的百分比厚度（实际为光标厚度）
	SetConsoleCursorInfo(hStdOutput, &info); //设置终端光标信息
}