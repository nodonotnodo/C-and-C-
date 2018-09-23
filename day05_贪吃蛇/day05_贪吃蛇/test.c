#include "Snakeeat.h"

void game()
{
	
	//����һ���ߣ����߽��г�ʼ����
	Game game;
	SnakeInit(&game);

	//��ӡ��Ϸ�˵�
	PrintMenu(&game);
	
	//��ʼ����ɣ���ʽ��ʼ��Ϸ��
	/*
		������Ϸ�� ���ȴ���һ��ʳ�
				   ��ӡ����ʳ�
				   ���ߣ�����ҽ��з���ѡ�������δ������������淶����ԭ�����ƶ���
				   �õ�̰���ߵ���һ�����ꣻ
				   �����Ƿ�ײ��ǽ���߳Ե��Լ���
				   �����Ƿ�Ե�ʳ�1.δ�ܳԵ�ʳ�ͷ�壬βɾ
								2.�Ե�ʳ�ͷ��
	*/
	//����һ��ʳ��
	coor food;
	GetFood(&food, &game);
	do{
		//��ӡ����ʳ�
		SnakePrint(&game);
		FoodPrint(food);

		//��ӡ����
		ScorePrint(&game);

		//���ߣ�����ҽ��з���ѡ�������δ������������淶����ԭ�����ƶ���
		Sleep(game.speed);
		playerchose(&game);

		//�õ�̰���ߵ���һ�����ꣻ
		coor nextcoor = Gtenextcoor(&game);

		//�����Ƿ�ײ��ǽ���߳Ե��Լ���
		if (Ishitwall(nextcoor,&game)){
			COORD pos;
			pos.X = 0;
			pos.Y = game.height + 2;
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(handle, pos); printf("�����ˣ���Ϸ����\n");
			SnakeDeatory(&game);
			return;
		}
		if (Iseatenself(nextcoor,&game)){
			COORD pos;
			pos.X = 0;
			pos.Y = game.height + 2;
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(handle, pos); printf("�����ˣ���Ϸ����\n");
			SnakeDeatory(&game);
			return;
		}

		//�����Ƿ�Ե�ʳ�//	1.�Ե�ʳ�ͷ��
		if (nextcoor.x == food.x && nextcoor.y == food.y)
		{
			SnakePushfront(&game.Snake.shead, nextcoor.x, nextcoor.y);
			//ʳ�ﱻ�Ե����ӷֲ����²���һ��ʳ��
			game.score += 10;
			GetFood(&food, &game);

			//ÿ���ﵽ50�ֵı������ٶ����ӡ�
			if ((0 == game.score % 50)&&(game.speed >= 100)){
				game.speed -= 50;
			}
		}
		//2.δ�ܳԵ�ʳ�ͷ�壬βɾ
		else{
			SnakePushfront(&game.Snake.shead, nextcoor.x, nextcoor.y);
			SnakePopback(&game.Snake.shead);
		}

		//����ΪSetConsoleCursorPosition()�����������Ĺ��β�����ص�
		HideCursorForSetConsoleCursorPosition();
	} while (1);
}

int main()
{
	game();
	return 0;
}