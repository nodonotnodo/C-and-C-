#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

/*
Ҫʵ��һ��̰���ߣ���������Ҫ����������еĸ�����Ϣ�ýṹ����������
��ô���ǵ�̰�����ж�Ӧ������Щ��Ϣ�أ�
1.̰���������ߡ�
����������ѡ��ʹ��˳����������������أ�
������˳�����������������Ѱ��Ԫ��ʱ�临�Ӷ�ΪO(1),����������
���ǲ�����Ҫ����Ԫ�أ�����̰���߻���߳����ڿ��ǵ��������⣬
���������������������ʾ̰���ߡ�
�������ݣ�̰���ߵ�ͷ����̰������һ���ķ���
2.̰�����е�ʳ�
���ʳ��Ӧ����һ����ά�����꣬�����ýṹ������ʾ��ͬʱ̰���ߵ�ͷ��
Ҳ����һ����ά��������ʾ���������Ƕ���һ���ṹ�壬��������ݾ���x��y
*/

typedef struct coordinate{
	int x;
	int y;
}coor;  //��ά���̰꣬���ߵ�ͷ�������ʳ������ʹ��

typedef enum drection{
	UP,
	DOWN,
	LEFT,
	RIGHT
}dir;  //����������������ʾ̰������һ���ķ���

typedef struct Node{
	coor pos;
	struct Node *next;
}Node;  //��ʾ̰���ߵ�����

typedef struct Snake{
	Node *shead;
	dir direc;
}Snake;  //̰����

typedef struct Game{
	Snake Snake;
	int score;
	int speed;
	int width;
	int height;
}Game;

//��ӡ��Ϸ�˵�
void PrintMenu(Game *game);

//�������ͷ��
void SnakePushfront(Node **shead, int x, int y);

//�������βɾ
void SnakePopback(Node **shead);


//���߽��г�ʼ��
void SnakeInit(Game *game);

//��������
void SnakeDeatory(Game *game);

//���һ��ʳ��
void GetFood(coor *food, Game *game);

//�õ�̰���ߵ���һ�����ꣻ
coor Gtenextcoor(Game *game);

//�ж��Ƿ�����
BOOL Ishitwall(coor nextcoor, Game *game);

//�ж��Ƿ�ҧ���Լ�
BOOL Iseatenself(coor nextcoor, Game *game);

//��ӡ��
void SnakePrint(Game *game);

//��ӡʳ��
void FoodPrint(coor food);

//���ѡ����
void playerchose(Game *game);

//��ӡ����
void ScorePrint(Game *game);

//����ΪSetConsoleCursorPosition()�����������Ĺ��β�����ص�
void HideCursorForSetConsoleCursorPosition();