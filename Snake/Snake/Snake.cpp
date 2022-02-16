#include "stdio.h"
#include "graphics.h"
#include "conio.h"
#include "stdlib.h"


#define SNAKE_NUM 500
#define HEIGHT 640
#define WIDE 480

enum DIR//ö�ٶ��巽��
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
// DWORD ��32λ������������
// ʳ��ṹ
struct Food
{
	int x;
	int y;
	int r;//ʳ���С
	bool flag;//ʳ���Ƿ񱻳���
	DWORD color;//ʳ����ɫ
}food;


struct Snake
{
	int size;// THE SIZE OF SNAKE 
	int dir;// THE DIRECTION OF SNAKE 
	int speed;// THE SPEED OF SNAKE 
	POINT coor[SNAKE_NUM]; //THE MOST LENGTH OF SNAKE 
}snake;
// INITING THE DATA OF GAME !
void GameInit()
{
	//GetTickCount()  �ǻ�ȡϵͳ���������ڵ�������ʱ��ĺ�����
	srand(GetTickCount());
	//init ��ʼ�� graph ͼ�δ���
	//initgraph(640,480,SHOWCONSOLE)   SHOWCONSOLE  ��ʾ����̨
	initgraph(HEIGHT, WIDE);
	// Initing the data of snake and the length of the snake is 3
	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT;
	for (int i = 0; i < snake.size ; i++)
	{
		snake.coor[i].x = 40-10*i;
		snake.coor[i].y = 10;
	}
	// ��ʼ��ʳ��
	food.x = rand() % 640;//rand()���������,�������һ������,���û��������������ӣ�ÿ�ζ�������һ���̶�������
	food.y = rand() % 480;//���������������Ҫ��ͷ�ļ� stdlib.h
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;

}
//��ʼ��ʳ��
void InitFood()
{
	//���ʳ����ʧ����������ʳ��
	if(food.flag ==false)
	{
		food.x = rand() % 640;//rand()���������,�������һ������,���û��������������ӣ�ÿ�ζ�������һ���̶�������
		food.y = rand() % 480;//���������������Ҫ��ͷ�ļ� stdlib.h
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = rand() % 10 + 5;
		food.flag =true;
	}
}


// ͨ�������ı䷽��

void keycontrol()
{
#if 0
	//�ж��Ƿ��а���
	if (_kbhit()) 
	{
		switch (_getch())
		{
			//72 80 75 77 �������Ҽ�ֵ
		case 'W':
		case 'w':
		case 72:
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
			}
			break;
		case 's':
		case 'S':
		case 80:
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
			}
			break;
		case 'a':
		case 'A':
		case 75:
			if (snake.dir != RIGHT) 
			{
				snake.dir = LEFT;
			}
			break;
		case 'd':
		case 'D':
		case 77:
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}
			break;
		}
	}
#elif 1
{
		if (GetAsyncKeyState('W') && snake.dir != DOWN)
			snake.dir = UP;
		if (GetAsyncKeyState('S') && snake.dir != UP)
			snake.dir = DOWN;
		if (GetAsyncKeyState('A') && snake.dir != RIGHT)
			snake.dir = LEFT;
		if (GetAsyncKeyState('D') && snake.dir != LEFT)
			snake.dir = RIGHT;
}
#endif

}

void GameDraw()
{
	//˫�����ͼ
	BeginBatchDraw();
	//���ñ�����ɫ
	setbkcolor(RGB(0, 161, 214));
	cleardevice();
	setfillcolor(RGB(16, 124, 16));
	// Drawing the snake
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	//����ʳ��
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();

}	

//������ͣ
void Stop()
{
	if (_kbhit())
	{
		if (_getch() == ' ')
		{
			while (1)
			{
				if (_getch() != NULL)
					break;
			}
		}
		
		
	}
}



void SnakeMove()
{
	for (int i = snake.size - 1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	switch (snake.dir)
	{
		case UP:
			snake.coor[0].y-=snake.speed;
			if (snake.coor[0].y <= 0)
				snake.coor[0].y = WIDE;
			break;
		case DOWN:
			snake.coor[0].y+=snake.speed;
			if (snake.coor[0].y >= WIDE)
				snake.coor[0].y = 0;
			break;
		case LEFT:
			snake.coor[0].x-=snake.speed;
			if (snake.coor[0].x <= 0)
				snake.coor[0].x = HEIGHT;
			break;
		case RIGHT:
			snake.coor[0].x+=snake.speed;
			if (snake.coor[0].x >= HEIGHT)
				snake.coor[0].x = 0;
			break;
	}
}

void EatFood()
{
	if (snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r && snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r&&food.flag)
	{
		food.flag = false;
		snake.size = snake.size++;
	}
	
}

int main()

{
	GameInit();
	GameDraw();


	while (1)
	{
		GameDraw();
		SnakeMove();
		keycontrol();
		EatFood();
		InitFood();
		Sleep(50);
		Stop();
	
	}

	return 0;

}

