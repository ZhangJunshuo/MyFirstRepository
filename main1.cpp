//我的贪吃蛇小游戏
/*
在任意位置输出字符
随机生成食物
游戏结束条件判断
键盘方向键或WASD控制移动
*/
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>//time()
#include <conio.h>//getch()

#define GROUND_WIDTH 40 //X
#define GROUND_HEIGHT 20 //Y 

void _SetHandlePosition(int x, int y)//自写函数和类都在名字前加一个下划线,以区别于windows库提供的.这是光标位置设置函数.
{
	HANDLE handle;//用windows库里的类创建一个handle对象,用于操作光标.
	handle = GetStdHandle(STD_OUTPUT_HANDLE);//将handle赋值成当前控制台下的一个标准光标.
	COORD pos = {0,0};//创建一个pos对象,用于表示指针的坐标,指针坐标并不是简单的二维数组,这是windows规定的.
	CONSOLE_CURSOR_INFO controler;//用windows库里的类创建一个控制者controler对象,用于修改控制台里的光标属性值.
	controler.dwSize = 1;    //设置光标大小
	controler.bVisible =  0; //设置光标不可见 FALSE
	SetConsoleCursorInfo(handle, &controler);    //应用光标属性.
	//上述代码完全可以写在main里面,因为该函数需要多次重复执行.//不能写成全局,为什么?

	pos.X = x;
	pos.Y = y; //设置光标xy值.
	SetConsoleCursorPosition(handle,pos);//设置光标位置.
}

void _RandomSetFood()//随机生成食物函数
{
	srand((unsigned)(time(NULL)));//用系统当前时间设置rand()随机序列种子,保证每次运行随机序列不一样.//srand函数还需要学习.
	int x = rand()%(GROUND_WIDTH-2)+1;//设置x为1到38之间的一个随机数
	int y = rand()%(GROUND_HEIGHT-2)+1;
	_SetHandlePosition(x,y);
	printf("@");
}

void _DrawGround()//绘制场地函数
{
	//绘制40 X 20的场地
	_SetHandlePosition(0,0);
	for(int i=0; i<GROUND_WIDTH-1+1; i++)
	{
		printf("#");
	}
	_SetHandlePosition(0,GROUND_HEIGHT-1);
	for(int i=0; i<GROUND_WIDTH-1; i++)
	{
		printf("#");
	}
	for(int i=0; i<GROUND_HEIGHT-1; i++)
	{
		_SetHandlePosition(0,i+1);
		printf("#");
	}
	for(int i=0; i<GROUND_HEIGHT-1; i++)
	{
		_SetHandlePosition(GROUND_WIDTH-1,i+1);
		printf("#");
	}
}

void _InitializeSnake()
{
	_SetHandlePosition(GROUND_WIDTH/2,GROUND_HEIGHT/2);
	printf("*");
}

int main()//目前还是测试区
{
	_DrawGround();//绘制场地
	_InitializeSnake();//初始化蟒蛇
	int ch1 = 0;//和getch函数配合使用.
	int ch2 = 0;
	int x = GROUND_WIDTH/2;//用于存储当前位置的光标坐标.
	int y = GROUND_HEIGHT/2;
	while(1)
	{
		if(x == GROUND_WIDTH-1 || x == 0 || y == GROUND_HEIGHT-1 || y == 0)
		{
			_SetHandlePosition(GROUND_WIDTH/2-5,GROUND_HEIGHT/2);
			printf("GAME OVER");
			_SetHandlePosition(0,GROUND_HEIGHT+2);//这样防止pause信息输出在我的游戏场地里造成不美观. 
			break;
		}
		if (ch1=getch())//第一次调用getch(),返回值224
		{
			ch2=getch();//第二次调用getch()
			if(ch2 == 72)//The key you Pressed is : ↑
			{
				_SetHandlePosition(x,y);//初始定位,不写也行,保险起见.
				printf(" ");
				y = y-1; //坐标向上移动一格.
				_SetHandlePosition(x,y);//重新定位.
				printf("*");
			}

			else if(ch2 == 80)//The key you Pressed is : ↓
			{
				_SetHandlePosition(x,y);//初始定位,不写也行,保险起见.
				printf(" ");
				y = y+1; //坐标向下移动一格.
				_SetHandlePosition(x,y);//重新定位.
				printf("*");
			}
			else if(ch2 == 75)//The key you Pressed is : ←
			{
				_SetHandlePosition(x,y);//初始定位,不写也行,保险起见.
				printf(" ");
				x = x-1; //坐标向左移动一格.
				_SetHandlePosition(x,y);//重新定位.
				printf("*");
			}
			else if(ch2 == 77)//The key you Pressed is : →
			{
				_SetHandlePosition(x,y);//初始定位,不写也行,保险起见.
				printf(" ");
				x = x+1; //坐标向右移动一格.
				_SetHandlePosition(x,y);//重新定位.
				printf("*");
			}
		}
	}
}
/*//贪吃蛇对角线移动测试小程序 //发现这个坐标系里面视觉上 2X = Y!
for(int i=0; i<GROUND_HEIGHT; i++)
{
	_SetHandlePosition(x,y);
	printf("*");
	x++;
	x++;
	y++;
	_SetHandlePosition(x-8,y-4);
	printf(" ");
	Sleep(300);
}
_SetHandlePosition(0,y);
printf("\n*********Game Over!**********");
//生成食物测试小程序
for(int i=0; i<GROUND_HEIGHT*GROUND_WIDTH; i++)
{
	Sleep(100);
	_RandomSetFood();
}*/
