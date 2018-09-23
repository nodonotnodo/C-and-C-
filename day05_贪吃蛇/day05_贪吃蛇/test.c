#include "Snakeeat.h"

void game()
{
	
	//创建一条蛇，对蛇进行初始化。
	Game game;
	SnakeInit(&game);

	//打印游戏菜单
	PrintMenu(&game);
	
	//初始化完成，正式开始游戏。
	/*
		进入游戏： 首先创建一个食物；
				   打印蛇与食物；
				   休眠，让玩家进行方向选择，若玩家未操作或操作不规范，则按原方向移动；
				   得到贪吃蛇的下一步坐标；
				   考虑是否撞到墙或者吃到自己；
				   考虑是否吃到食物：1.未能吃到食物：头插，尾删
								2.吃到食物：头插
	*/
	//创建一个食物
	coor food;
	GetFood(&food, &game);
	do{
		//打印蛇与食物；
		SnakePrint(&game);
		FoodPrint(food);

		//打印分数
		ScorePrint(&game);

		//休眠，让玩家进行方向选择，若玩家未操作或操作不规范，则按原方向移动；
		Sleep(game.speed);
		playerchose(&game);

		//得到贪吃蛇的下一步坐标；
		coor nextcoor = Gtenextcoor(&game);

		//考虑是否撞到墙或者吃到自己；
		if (Ishitwall(nextcoor,&game)){
			COORD pos;
			pos.X = 0;
			pos.Y = game.height + 2;
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(handle, pos); printf("你死了，游戏结束\n");
			SnakeDeatory(&game);
			return;
		}
		if (Iseatenself(nextcoor,&game)){
			COORD pos;
			pos.X = 0;
			pos.Y = game.height + 2;
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(handle, pos); printf("你死了，游戏结束\n");
			SnakeDeatory(&game);
			return;
		}

		//考虑是否吃到食物：//	1.吃到食物：头插
		if (nextcoor.x == food.x && nextcoor.y == food.y)
		{
			SnakePushfront(&game.Snake.shead, nextcoor.x, nextcoor.y);
			//食物被吃掉，加分并重新产生一个食物
			game.score += 10;
			GetFood(&food, &game);

			//每当达到50分的倍数，速度增加。
			if ((0 == game.score % 50)&&(game.speed >= 100)){
				game.speed -= 50;
			}
		}
		//2.未能吃到食物：头插，尾删
		else{
			SnakePushfront(&game.Snake.shead, nextcoor.x, nextcoor.y);
			SnakePopback(&game.Snake.shead);
		}

		//将因为SetConsoleCursorPosition()函数而产生的光标尾巴隐藏掉
		HideCursorForSetConsoleCursorPosition();
	} while (1);
}

int main()
{
	game();
	return 0;
}