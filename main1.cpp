//�ҵ�̰����С��Ϸ
/*
������λ������ַ�
�������ʳ��
��Ϸ���������ж�
���̷������WASD�����ƶ�
*/
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>//time()
#include <conio.h>//getch()

#define GROUND_WIDTH 40 //X
#define GROUND_HEIGHT 20 //Y 

void _SetHandlePosition(int x, int y)//��д�������඼������ǰ��һ���»���,��������windows���ṩ��.���ǹ��λ�����ú���.
{
	HANDLE handle;//��windows������ഴ��һ��handle����,���ڲ������.
	handle = GetStdHandle(STD_OUTPUT_HANDLE);//��handle��ֵ�ɵ�ǰ����̨�µ�һ����׼���.
	COORD pos = {0,0};//����һ��pos����,���ڱ�ʾָ�������,ָ�����겢���Ǽ򵥵Ķ�ά����,����windows�涨��.
	CONSOLE_CURSOR_INFO controler;//��windows������ഴ��һ��������controler����,�����޸Ŀ���̨��Ĺ������ֵ.
	controler.dwSize = 1;    //���ù���С
	controler.bVisible =  0; //���ù�겻�ɼ� FALSE
	SetConsoleCursorInfo(handle, &controler);    //Ӧ�ù������.
	//����������ȫ����д��main����,��Ϊ�ú�����Ҫ����ظ�ִ��.//����д��ȫ��,Ϊʲô?

	pos.X = x;
	pos.Y = y; //���ù��xyֵ.
	SetConsoleCursorPosition(handle,pos);//���ù��λ��.
}

void _RandomSetFood()//�������ʳ�ﺯ��
{
	srand((unsigned)(time(NULL)));//��ϵͳ��ǰʱ������rand()�����������,��֤ÿ������������в�һ��.//srand��������Ҫѧϰ.
	int x = rand()%(GROUND_WIDTH-2)+1;//����xΪ1��38֮���һ�������
	int y = rand()%(GROUND_HEIGHT-2)+1;
	_SetHandlePosition(x,y);
	printf("@");
}

void _DrawGround()//���Ƴ��غ���
{
	//����40 X 20�ĳ���
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

int main()//Ŀǰ���ǲ�����
{
	_DrawGround();//���Ƴ���
	_InitializeSnake();//��ʼ������
	int ch1 = 0;//��getch�������ʹ��.
	int ch2 = 0;
	int x = GROUND_WIDTH/2;//���ڴ洢��ǰλ�õĹ������.
	int y = GROUND_HEIGHT/2;
	while(1)
	{
		if(x == GROUND_WIDTH-1 || x == 0 || y == GROUND_HEIGHT-1 || y == 0)
		{
			_SetHandlePosition(GROUND_WIDTH/2-5,GROUND_HEIGHT/2);
			printf("GAME OVER");
			_SetHandlePosition(0,GROUND_HEIGHT+2);//������ֹpause��Ϣ������ҵ���Ϸ��������ɲ�����. 
			break;
		}
		if (ch1=getch())//��һ�ε���getch(),����ֵ224
		{
			ch2=getch();//�ڶ��ε���getch()
			if(ch2 == 72)//The key you Pressed is : ��
			{
				_SetHandlePosition(x,y);//��ʼ��λ,��дҲ��,�������.
				printf(" ");
				y = y-1; //���������ƶ�һ��.
				_SetHandlePosition(x,y);//���¶�λ.
				printf("*");
			}

			else if(ch2 == 80)//The key you Pressed is : ��
			{
				_SetHandlePosition(x,y);//��ʼ��λ,��дҲ��,�������.
				printf(" ");
				y = y+1; //���������ƶ�һ��.
				_SetHandlePosition(x,y);//���¶�λ.
				printf("*");
			}
			else if(ch2 == 75)//The key you Pressed is : ��
			{
				_SetHandlePosition(x,y);//��ʼ��λ,��дҲ��,�������.
				printf(" ");
				x = x-1; //���������ƶ�һ��.
				_SetHandlePosition(x,y);//���¶�λ.
				printf("*");
			}
			else if(ch2 == 77)//The key you Pressed is : ��
			{
				_SetHandlePosition(x,y);//��ʼ��λ,��дҲ��,�������.
				printf(" ");
				x = x+1; //���������ƶ�һ��.
				_SetHandlePosition(x,y);//���¶�λ.
				printf("*");
			}
		}
	}
}
/*//̰���߶Խ����ƶ�����С���� //�����������ϵ�����Ӿ��� 2X = Y!
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
//����ʳ�����С����
for(int i=0; i<GROUND_HEIGHT*GROUND_WIDTH; i++)
{
	Sleep(100);
	_RandomSetFood();
}*/
