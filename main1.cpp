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

void _RandomSetFood()
{
	srand((unsigned)(time(NULL)));//��ϵͳ��ǰʱ������rand()�����������,��֤ÿ������������в�һ��.//srand��������Ҫѧϰ.
	int x = rand()%(38)+1;//����xΪ1��38֮���һ�������
	int y = rand()%(18)+1;
	_SetHandlePosition(x,y);
	printf("@");
}

int main()//Ŀǰ���ǲ�����
{
	//int i = 0, j = 0;//�ȶ���������������,��������for�����ظ������˷�ʱ��.Ҫע��ÿ��������ʼ��.ÿ�ζ���ʼ��̫Σ��.
	int x = 0, y = 0;//����ù��λ��.ͬ��ÿ��������֮��Ҫ��ʼ��.
	//����40 X 20�ĳ���
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
	//̰���߶Խ����ƶ�����С���� //�����������ϵ�����Ӿ��� 2X = Y!
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
	//����ʳ�����С����
	for(int i=0; i<800; i++)
	{
		Sleep(100);
		_RandomSetFood();
	}
}
