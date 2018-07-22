/********************************************************************************
程序名:    Snake World v4.0.0 
开发者:    张峻硕 
开发时间:  20180720-20180722 
联系方式:  zhangjunshuo_sdu@outlook.com 
开发目的:  ... 
附注:      如有建议或意见或发现BUG,欢迎指正或是交流! 
********************************************************************************/
//我的贪吃蛇小游戏
/*
在任意位置输出字符
随机生成食物
游戏结束条件判断
键盘方向键或WASD控制移动
蟒蛇长度达到场地格子数的四分之一左右就判定胜利
*/
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>//time()
#include <conio.h>//getch()

#define GROUND_WIDTH 40 //X
#define GROUND_HEIGHT 20 //Y 
#define WINDOW_WIDTH (GROUND_WIDTH+40) //窗体宽度为场地宽度加上40,以便输出得分和评语信息. 
#define WINDOW_HEIGHT (GROUND_HEIGHT+3) //设置窗体高度与场地高度加3,以便输出程序性能信息. 

int foodx = 0;//设置全局的食物生成点,用于判断蛇是否吃到食物.
int foody = 0;
int score = 0;//设置全局的计分变量.

struct snake
{
	public:
		int snakelen = 0;//蛇的长度.
		int u = 0;		//定义蛇的运动的上下左右方向的数值,0为非,1为是.
		int d = 0;
		int l = 0;
		int r = 0;
		int body[((GROUND_WIDTH-1)*(GROUND_HEIGHT-1))/2+1][2] = {};//实现建立一个最大长度的坐标数组来表示蛇身每一节的坐标.
		//[0]为x [1]为y
		//这样事先建好数组的做法,对于较大的场地和较小的内存显然不太友好.
		//在下一个版本中可以考虑使用C链表来节省内存.
};
struct snake s;//创建蛇对象

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
	foodx = rand()%(GROUND_WIDTH-2)+1;//设置foodx为1到38之间的一个随机数
	foody = rand()%(GROUND_HEIGHT-2)+1;
	_SetHandlePosition(foodx,foody);
	printf("@");
}

void _Welcome()//欢迎界面
{
	char shield[1];
	system("title SNAKE WORLD v4.0.0");//这里改变title 
	system("mode con cols=80 lines=23");//直接以字符串形式发送的,不能用%来转译.
	_SetHandlePosition(0,WINDOW_HEIGHT/2);//在屏幕中央输出欢迎信息
	printf("WELCOME TO THE SNAKE WORLD!");
	_SetHandlePosition(0,WINDOW_HEIGHT/2+1);
	printf("...PRESS ENTER TO START...");
	gets(shield);
	system("cls");
	_SetHandlePosition(0,0);
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
	//绘制计分板信息
	_SetHandlePosition(WINDOW_WIDTH/2+5,1);
	printf("WELCOME TO MY SNAKE WORLD");
	_SetHandlePosition(WINDOW_WIDTH/2+2,3);
	printf("HERE ARE SOME RULES FOR YOUR SNAKE:");
	_SetHandlePosition(WINDOW_WIDTH/2+2,5);
	printf("1.Don't touch the edge of the world.");
	_SetHandlePosition(WINDOW_WIDTH/2+2,7);
	printf("2.Be careful to avoid biting yourself.");
	_SetHandlePosition(WINDOW_WIDTH/2+2,9);
	printf("3.Grow up to a quarter of the world.");
	_SetHandlePosition(WINDOW_WIDTH/2+2,11);
	printf("4.Have fun! THIS IS FOR YOU (:");
	_SetHandlePosition(WINDOW_WIDTH/2+2,15);
	printf("YOUR SCORE:");//10
	printf(" %d",score);
	_SetHandlePosition(WINDOW_WIDTH/2+2,17);
	printf("SCORE TO WIN:");//12
	printf(" %d",((GROUND_WIDTH-1)*(GROUND_HEIGHT-1))/4-2-score);
}

void _InitializeSnake()
{
	_SetHandlePosition(GROUND_WIDTH/2,GROUND_HEIGHT/2);//在屏幕中央生成长度为2的蛇.
	printf("*");
	_SetHandlePosition(GROUND_WIDTH/2,GROUND_HEIGHT/2+1);
	printf("*");
	s.snakelen = 2; //设置蛇长为2.//如果设置蛇长为1会造成很多问题,因为那样的话就造成蛇头蛇尾重叠,与我的移动算法冲突.
	s.body[0][0] = GROUND_WIDTH/2;//设置蛇头坐标.
	s.body[0][1] = GROUND_HEIGHT/2;
	s.body[1][0] = GROUND_WIDTH/2;//设置蛇尾坐标.
	s.body[1][1] = GROUND_HEIGHT/2+1;
}

int main()//目前还是测试区
{
	_Welcome();//绘制Welcome界面
	_DrawGround();//绘制场地
	_InitializeSnake();//初始化蟒蛇
	_RandomSetFood();//生成第一个食物

	int ch1 = 0;//和getch函数配合使用.
	int ch2 = 0;
	int x = GROUND_WIDTH/2;//用于存储当前位置的光标坐标.
	int y = GROUND_HEIGHT/2;

	while(s.snakelen <= ((GROUND_WIDTH-1)*(GROUND_HEIGHT-1))/4)
	{
		if(s.body[0][0] == GROUND_WIDTH-1 || s.body[0][0] == 0 || s.body[0][1] == GROUND_HEIGHT-1 || s.body[0][1] == 0)
		{
			_SetHandlePosition(GROUND_WIDTH/2-5,GROUND_HEIGHT/2);
			printf("GAME OVER");
			_SetHandlePosition(0,GROUND_HEIGHT-1);//这样防止pause信息输出在我的游戏场地里造成不美观.
			return -1;//失败则返回-1.胜利返回1
		}
		for(int i=1; i<s.snakelen; i++) //从第二节开始检查,如果有与蛇头坐标重叠的蛇身,则游戏结束.
		{
			if(s.body[0][0] == s.body[i][0] && s.body[0][1] == s.body[i][1])
			{
				_SetHandlePosition(GROUND_WIDTH/2-5,GROUND_HEIGHT/2);
				printf("GAME OVER");
				_SetHandlePosition(0,GROUND_HEIGHT-1);
				return -1;
			}
		}
		//游戏结束处理阵列.
		///////////////////////////////////////////////////////////////////////////////////////////////////
		if(s.body[0][0] == foodx && s.body[0][1] == foody)//蛇头吃到食物的处理器
		{
			_RandomSetFood();//立即生成第二个食物.
			s.snakelen++;//增加蛇身长度.
			score++;//得分增加.
			_SetHandlePosition(x,y);//先定位到移动前蛇尾的坐标,此时该点已经打印空格.
			printf("*");//将该点重新打印成蛇尾;
			//下面更新蛇身的坐标
			s.body[s.snakelen-1][0] = x;
			s.body[s.snakelen-1][1] = y;
			//最后更新计分板
			_SetHandlePosition(WINDOW_WIDTH/2+2+11,15);
			printf(" %d",score);
			_SetHandlePosition(WINDOW_WIDTH/2+2+13,17);
			printf(" %d",((GROUND_WIDTH-1)*(GROUND_HEIGHT-1))/4-2-score);
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////
		if (ch1=getch())//第一次调用getch(),返回值224.//蛇身移动处理器.
		{
			ch2=getch();//第二次调用getch()
			if(ch2 == 72)//The key you Pressed is : ↑
			{
				if(s.body[1][1] == s.body[0][1]-1);//不允许蛇回头
				else
				{
					_SetHandlePosition(s.body[s.snakelen-1][0],s.body[s.snakelen-1][1]);//定位到蛇尾的坐标
					printf(" ");//删除蛇尾
					_SetHandlePosition(s.body[0][0],s.body[0][1]-1);//定位到蛇头的移动方向的下一格
					printf("*");//绘制新蛇头,原蛇头不动,变成蛇身.
					//先把蛇尾的坐标存起来以便吃到食物的时候使用.
					x = s.body[s.snakelen-1][0];
					y = s.body[s.snakelen-1][1];
					//然后要更新蛇头和蛇尾的坐标
					for(int i=1; i<s.snakelen; i++) //用循环方式从蛇尾开始更新所有蛇身坐标
					{
						s.body[s.snakelen-i][0] = s.body[s.snakelen-(i+1)][0];
						s.body[s.snakelen-i][1] = s.body[s.snakelen-(i+1)][1];
					}
					//考虑到蛇的长度为2的情况,所以必须先更新蛇尾坐标,再更新蛇头坐标.
					s.body[0][0] = s.body[0][0];
					s.body[0][1] = s.body[0][1]-1;//更新蛇头的坐标.
				}
			}
			else if(ch2 == 80)//The key you Pressed is : ↓
			{
				if(s.body[1][1] == s.body[0][1]+1);//不允许蛇回头
				else
				{
					_SetHandlePosition(s.body[s.snakelen-1][0],s.body[s.snakelen-1][1]);//定位到蛇尾的坐标
					printf(" ");//删除蛇尾
					_SetHandlePosition(s.body[0][0],s.body[0][1]+1);//定位到蛇头的移动方向的下一格
					printf("*");//绘制新蛇头,原蛇头不动,变成蛇身.
					//先把蛇尾的坐标存起来以便吃到食物的时候使用.
					x = s.body[s.snakelen-1][0];
					y = s.body[s.snakelen-1][1];
					//然后要更新蛇头和蛇尾的坐标
					for(int i=1; i<s.snakelen; i++) //用循环方式从蛇尾开始更新所有蛇身坐标
					{
						s.body[s.snakelen-i][0] = s.body[s.snakelen-(i+1)][0];
						s.body[s.snakelen-i][1] = s.body[s.snakelen-(i+1)][1];
					}
					//考虑到蛇的长度为2的情况,所以必须先更新蛇尾坐标,再更新蛇头坐标.
					s.body[0][0] = s.body[0][0];
					s.body[0][1] = s.body[0][1]+1;//更新蛇头的坐标.
				}
			}
			else if(ch2 == 75)//The key you Pressed is : ←
			{
				if(s.body[1][0] == s.body[0][0]-1);//不允许蛇回头
				else
				{
					_SetHandlePosition(s.body[s.snakelen-1][0],s.body[s.snakelen-1][1]);//定位到蛇尾的坐标
					printf(" ");//删除蛇尾
					_SetHandlePosition(s.body[0][0]-1,s.body[0][1]);//定位到蛇头的移动方向的下一格
					printf("*");//绘制新蛇头,原蛇头不动,变成蛇身.
					//先把蛇尾的坐标存起来以便吃到食物的时候使用.
					x = s.body[s.snakelen-1][0];
					y = s.body[s.snakelen-1][1];
					//然后要更新蛇头和蛇尾的坐标
					for(int i=1; i<s.snakelen; i++) //用循环方式从蛇尾开始更新所有蛇身坐标
					{
						s.body[s.snakelen-i][0] = s.body[s.snakelen-(i+1)][0];
						s.body[s.snakelen-i][1] = s.body[s.snakelen-(i+1)][1];
					}
					//考虑到蛇的长度为2的情况,所以必须先更新蛇尾坐标,再更新蛇头坐标.
					s.body[0][0] = s.body[0][0]-1;
					s.body[0][1] = s.body[0][1];//更新蛇头的坐标.
				}
			}
			else if(ch2 == 77)//The key you Pressed is : →
			{
				if(s.body[1][0] == s.body[0][0]+1);//不允许蛇回头
				else
				{
					_SetHandlePosition(s.body[s.snakelen-1][0],s.body[s.snakelen-1][1]);//定位到蛇尾的坐标
					printf(" ");//删除蛇尾
					_SetHandlePosition(s.body[0][0]+1,s.body[0][1]);//定位到蛇头的移动方向的下一格
					printf("*");//绘制新蛇头,原蛇头不动,变成蛇身.
					//先把蛇尾的坐标存起来以便吃到食物的时候使用.
					x = s.body[s.snakelen-1][0];
					y = s.body[s.snakelen-1][1];
					//然后要更新蛇头和蛇尾的坐标
					for(int i=1; i<s.snakelen; i++) //用循环方式从蛇尾开始更新所有蛇身坐标
					{
						s.body[s.snakelen-i][0] = s.body[s.snakelen-(i+1)][0];
						s.body[s.snakelen-i][1] = s.body[s.snakelen-(i+1)][1];
					}
					//考虑到蛇的长度为2的情况,所以必须先更新蛇尾坐标,再更新蛇头坐标.
					s.body[0][0] = s.body[0][0]+1;
					s.body[0][1] = s.body[0][1];//更新蛇头的坐标.
				}
			}
		}
	}
	_SetHandlePosition(GROUND_WIDTH/2-4,GROUND_HEIGHT/2);
	printf("YOU WIN!!!");
	_SetHandlePosition(0,GROUND_HEIGHT-1);//这样防止pause信息输出在我的游戏场地里造成不美观.
	return 1;//失败则返回-1.胜利返回1
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
