#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

/*
要实现一个贪吃蛇，我们首先要将这个程序中的各种信息用结构体描述出来
那么我们的贪吃蛇中都应该有哪些信息呢？
1.贪吃蛇这条蛇。
这条蛇我们选择使用顺序表还是链表来描述呢？
分析：顺序表对于链表的优势是寻找元素时间复杂度为O(1),但是在这里
我们并不需要查找元素，而且贪吃蛇还会边长。在考虑到扩容问题，
我们这里决定用链表来表示贪吃蛇。
链表内容：贪吃蛇的头部，贪吃蛇下一步的方向。
2.贪吃蛇中的食物。
这个食物应该是一个二维的坐标，我们用结构体来表示。同时贪吃蛇的头部
也是用一个二维坐标来表示，所以我们定义一个结构体，里面的内容就是x和y
*/

typedef struct coordinate{
	int x;
	int y;
}coor;  //二维坐标，贪吃蛇的头部坐标和食物坐标使用

typedef enum drection{
	UP,
	DOWN,
	LEFT,
	RIGHT
}dir;  //方向，这里用它来表示贪吃蛇下一步的方向

typedef struct Node{
	coor pos;
	struct Node *next;
}Node;  //表示贪吃蛇的链表

typedef struct Snake{
	Node *shead;
	dir direc;
}Snake;  //贪吃蛇

typedef struct Game{
	Snake Snake;
	int score;
	int speed;
	int width;
	int height;
}Game;

//打印游戏菜单
void PrintMenu(Game *game);

//蛇链表的头插
void SnakePushfront(Node **shead, int x, int y);

//蛇链表的尾删
void SnakePopback(Node **shead);


//对蛇进行初始化
void SnakeInit(Game *game);

//销毁链表
void SnakeDeatory(Game *game);

//获得一个食物
void GetFood(coor *food, Game *game);

//得到贪吃蛇的下一步坐标；
coor Gtenextcoor(Game *game);

//判断是否碰壁
BOOL Ishitwall(coor nextcoor, Game *game);

//判断是否咬到自己
BOOL Iseatenself(coor nextcoor, Game *game);

//打印蛇
void SnakePrint(Game *game);

//打印食物
void FoodPrint(coor food);

//玩家选择方向
void playerchose(Game *game);

//打印分数
void ScorePrint(Game *game);

//将因为SetConsoleCursorPosition()函数而产生的光标尾巴隐藏掉
void HideCursorForSetConsoleCursorPosition();