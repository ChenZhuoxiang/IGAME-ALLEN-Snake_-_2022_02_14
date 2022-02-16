#include "stdio.h"
#include "graphics.h"
#include "conio.h"
#include "stdlib.h"


#define SNAKE_NUM 500
#define HEIGHT 640
#define WIDE 480

enum DIR//枚举定义方向
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
// DWORD 是32位整形数据类型
// 食物结构
struct Food
{
	int x;
	int y;
	int r;//食物大小
	bool flag;//食物是否被吃了
	DWORD color;//食物颜色
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
	//GetTickCount()  是获取系统开机到现在的所经过时间的毫秒数
	srand(GetTickCount());
	//init 初始化 graph 图形窗口
	//initgraph(640,480,SHOWCONSOLE)   SHOWCONSOLE  显示控制台
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
	// 初始化食物
	food.x = rand() % 640;//rand()是随机函数,随机产生一个整数,如果没有设置随机数种子，每次都会生成一个固定的整数
	food.y = rand() % 480;//设置随机数种子需要的头文件 stdlib.h
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;

}
//初始化食物
void InitFood()
{
	//如果食物消失则重新生成食物
	if(food.flag ==false)
	{
		food.x = rand() % 640;//rand()是随机函数,随机产生一个整数,如果没有设置随机数种子，每次都会生成一个固定的整数
		food.y = rand() % 480;//设置随机数种子需要的头文件 stdlib.h
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = rand() % 10 + 5;
		food.flag =true;
	}
}


// 通过按键改变方向

void keycontrol()
{
#if 0
	//判断是否有按键
	if (_kbhit()) 
	{
		switch (_getch())
		{
			//72 80 75 77 上下左右键值
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
	//双缓冲绘图
	BeginBatchDraw();
	//设置背景颜色
	setbkcolor(RGB(0, 161, 214));
	cleardevice();
	setfillcolor(RGB(16, 124, 16));
	// Drawing the snake
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	//绘制食物
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();

}	

//程序暂停
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

