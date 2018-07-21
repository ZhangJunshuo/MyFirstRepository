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

void _RandomSetFood()
{
	srand((unsigned)(time(NULL)));//用系统当前时间设置rand()随机序列种子,保证每次运行随机序列不一样.//srand函数还需要学习.
	int x = rand()%(38)+1;//设置x为1到38之间的一个随机数
	int y = rand()%(18)+1;
	_SetHandlePosition(x,y);
	printf("@");
}

int main()//目前还是测试区
{
	//int i = 0, j = 0;//先定义两个操作变量,以免多次在for里面重复定义浪费时间.要注意每次用完后初始化.每次都初始化太危险.
	int x = 0, y = 0;//定义好光标位置.同样每次是用完之后要初始化.
	//绘制40 X 20的场地
	for(int i=0; i<40; i++)
	{
		printf("#");
	}
	_SetHandlePosition(0,19);
	for(int i=0; i<40; i++)
	{
		printf("#");
	}
	for(int i=0; i<19; i++)
	{
		_SetHandlePosition(0,i+1);
		printf("#");
	}
	for(int i=0; i<19; i++)
	{
		_SetHandlePosition(39,i+1);
		printf("#");
	}
	//贪吃蛇对角线移动测试小程序 //发现这个坐标系里面视觉上 2X = Y!
	for(int i=0; i<20; i++)
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
	for(int i=0; i<800; i++)
	{
		Sleep(100);
		_RandomSetFood();
	}
}
