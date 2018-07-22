/********************************************************************************
������:    Snake World v4.0.0 
������:    �ž�˶ 
����ʱ��:  20180720-20180722 
��ϵ��ʽ:  zhangjunshuo_sdu@outlook.com 
����Ŀ��:  ... 
��ע:      ���н�����������BUG,��ӭָ�����ǽ���! 
********************************************************************************/
//�ҵ�̰����С��Ϸ
/*
������λ������ַ�
�������ʳ��
��Ϸ���������ж�
���̷������WASD�����ƶ�
���߳��ȴﵽ���ظ��������ķ�֮һ���Ҿ��ж�ʤ��
*/
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>//time()
#include <conio.h>//getch()

#define GROUND_WIDTH 40 //X
#define GROUND_HEIGHT 20 //Y 
#define WINDOW_WIDTH (GROUND_WIDTH+40) //������Ϊ���ؿ�ȼ���40,�Ա�����÷ֺ�������Ϣ. 
#define WINDOW_HEIGHT (GROUND_HEIGHT+3) //���ô���߶��볡�ظ߶ȼ�3,�Ա��������������Ϣ. 

int foodx = 0;//����ȫ�ֵ�ʳ�����ɵ�,�����ж����Ƿ�Ե�ʳ��.
int foody = 0;
int score = 0;//����ȫ�ֵļƷֱ���.

struct snake
{
	public:
		int snakelen = 0;//�ߵĳ���.
		int u = 0;		//�����ߵ��˶����������ҷ������ֵ,0Ϊ��,1Ϊ��.
		int d = 0;
		int l = 0;
		int r = 0;
		int body[((GROUND_WIDTH-1)*(GROUND_HEIGHT-1))/2+1][2] = {};//ʵ�ֽ���һ����󳤶ȵ�������������ʾ����ÿһ�ڵ�����.
		//[0]Ϊx [1]Ϊy
		//�������Ƚ������������,���ڽϴ�ĳ��غͽ�С���ڴ���Ȼ��̫�Ѻ�.
		//����һ���汾�п��Կ���ʹ��C��������ʡ�ڴ�.
};
struct snake s;//�����߶���

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
	foodx = rand()%(GROUND_WIDTH-2)+1;//����foodxΪ1��38֮���һ�������
	foody = rand()%(GROUND_HEIGHT-2)+1;
	_SetHandlePosition(foodx,foody);
	printf("@");
}

void _Welcome()//��ӭ����
{
	char shield[1];
	system("title SNAKE WORLD v4.0.0");//����ı�title 
	system("mode con cols=80 lines=23");//ֱ�����ַ�����ʽ���͵�,������%��ת��.
	_SetHandlePosition(0,WINDOW_HEIGHT/2);//����Ļ���������ӭ��Ϣ
	printf("WELCOME TO THE SNAKE WORLD!");
	_SetHandlePosition(0,WINDOW_HEIGHT/2+1);
	printf("...PRESS ENTER TO START...");
	gets(shield);
	system("cls");
	_SetHandlePosition(0,0);
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
	//���ƼƷְ���Ϣ
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
	_SetHandlePosition(GROUND_WIDTH/2,GROUND_HEIGHT/2);//����Ļ�������ɳ���Ϊ2����.
	printf("*");
	_SetHandlePosition(GROUND_WIDTH/2,GROUND_HEIGHT/2+1);
	printf("*");
	s.snakelen = 2; //�����߳�Ϊ2.//��������߳�Ϊ1����ɺܶ�����,��Ϊ�����Ļ��������ͷ��β�ص�,���ҵ��ƶ��㷨��ͻ.
	s.body[0][0] = GROUND_WIDTH/2;//������ͷ����.
	s.body[0][1] = GROUND_HEIGHT/2;
	s.body[1][0] = GROUND_WIDTH/2;//������β����.
	s.body[1][1] = GROUND_HEIGHT/2+1;
}

int main()//Ŀǰ���ǲ�����
{
	_Welcome();//����Welcome����
	_DrawGround();//���Ƴ���
	_InitializeSnake();//��ʼ������
	_RandomSetFood();//���ɵ�һ��ʳ��

	int ch1 = 0;//��getch�������ʹ��.
	int ch2 = 0;
	int x = GROUND_WIDTH/2;//���ڴ洢��ǰλ�õĹ������.
	int y = GROUND_HEIGHT/2;

	while(s.snakelen <= ((GROUND_WIDTH-1)*(GROUND_HEIGHT-1))/4)
	{
		if(s.body[0][0] == GROUND_WIDTH-1 || s.body[0][0] == 0 || s.body[0][1] == GROUND_HEIGHT-1 || s.body[0][1] == 0)
		{
			_SetHandlePosition(GROUND_WIDTH/2-5,GROUND_HEIGHT/2);
			printf("GAME OVER");
			_SetHandlePosition(0,GROUND_HEIGHT-1);//������ֹpause��Ϣ������ҵ���Ϸ��������ɲ�����.
			return -1;//ʧ���򷵻�-1.ʤ������1
		}
		for(int i=1; i<s.snakelen; i++) //�ӵڶ��ڿ�ʼ���,���������ͷ�����ص�������,����Ϸ����.
		{
			if(s.body[0][0] == s.body[i][0] && s.body[0][1] == s.body[i][1])
			{
				_SetHandlePosition(GROUND_WIDTH/2-5,GROUND_HEIGHT/2);
				printf("GAME OVER");
				_SetHandlePosition(0,GROUND_HEIGHT-1);
				return -1;
			}
		}
		//��Ϸ������������.
		///////////////////////////////////////////////////////////////////////////////////////////////////
		if(s.body[0][0] == foodx && s.body[0][1] == foody)//��ͷ�Ե�ʳ��Ĵ�����
		{
			_RandomSetFood();//�������ɵڶ���ʳ��.
			s.snakelen++;//����������.
			score++;//�÷�����.
			_SetHandlePosition(x,y);//�ȶ�λ���ƶ�ǰ��β������,��ʱ�õ��Ѿ���ӡ�ո�.
			printf("*");//���õ����´�ӡ����β;
			//����������������
			s.body[s.snakelen-1][0] = x;
			s.body[s.snakelen-1][1] = y;
			//�����¼Ʒְ�
			_SetHandlePosition(WINDOW_WIDTH/2+2+11,15);
			printf(" %d",score);
			_SetHandlePosition(WINDOW_WIDTH/2+2+13,17);
			printf(" %d",((GROUND_WIDTH-1)*(GROUND_HEIGHT-1))/4-2-score);
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////
		if (ch1=getch())//��һ�ε���getch(),����ֵ224.//�����ƶ�������.
		{
			ch2=getch();//�ڶ��ε���getch()
			if(ch2 == 72)//The key you Pressed is : ��
			{
				if(s.body[1][1] == s.body[0][1]-1);//�������߻�ͷ
				else
				{
					_SetHandlePosition(s.body[s.snakelen-1][0],s.body[s.snakelen-1][1]);//��λ����β������
					printf(" ");//ɾ����β
					_SetHandlePosition(s.body[0][0],s.body[0][1]-1);//��λ����ͷ���ƶ��������һ��
					printf("*");//��������ͷ,ԭ��ͷ����,�������.
					//�Ȱ���β������������Ա�Ե�ʳ���ʱ��ʹ��.
					x = s.body[s.snakelen-1][0];
					y = s.body[s.snakelen-1][1];
					//Ȼ��Ҫ������ͷ����β������
					for(int i=1; i<s.snakelen; i++) //��ѭ����ʽ����β��ʼ����������������
					{
						s.body[s.snakelen-i][0] = s.body[s.snakelen-(i+1)][0];
						s.body[s.snakelen-i][1] = s.body[s.snakelen-(i+1)][1];
					}
					//���ǵ��ߵĳ���Ϊ2�����,���Ա����ȸ�����β����,�ٸ�����ͷ����.
					s.body[0][0] = s.body[0][0];
					s.body[0][1] = s.body[0][1]-1;//������ͷ������.
				}
			}
			else if(ch2 == 80)//The key you Pressed is : ��
			{
				if(s.body[1][1] == s.body[0][1]+1);//�������߻�ͷ
				else
				{
					_SetHandlePosition(s.body[s.snakelen-1][0],s.body[s.snakelen-1][1]);//��λ����β������
					printf(" ");//ɾ����β
					_SetHandlePosition(s.body[0][0],s.body[0][1]+1);//��λ����ͷ���ƶ��������һ��
					printf("*");//��������ͷ,ԭ��ͷ����,�������.
					//�Ȱ���β������������Ա�Ե�ʳ���ʱ��ʹ��.
					x = s.body[s.snakelen-1][0];
					y = s.body[s.snakelen-1][1];
					//Ȼ��Ҫ������ͷ����β������
					for(int i=1; i<s.snakelen; i++) //��ѭ����ʽ����β��ʼ����������������
					{
						s.body[s.snakelen-i][0] = s.body[s.snakelen-(i+1)][0];
						s.body[s.snakelen-i][1] = s.body[s.snakelen-(i+1)][1];
					}
					//���ǵ��ߵĳ���Ϊ2�����,���Ա����ȸ�����β����,�ٸ�����ͷ����.
					s.body[0][0] = s.body[0][0];
					s.body[0][1] = s.body[0][1]+1;//������ͷ������.
				}
			}
			else if(ch2 == 75)//The key you Pressed is : ��
			{
				if(s.body[1][0] == s.body[0][0]-1);//�������߻�ͷ
				else
				{
					_SetHandlePosition(s.body[s.snakelen-1][0],s.body[s.snakelen-1][1]);//��λ����β������
					printf(" ");//ɾ����β
					_SetHandlePosition(s.body[0][0]-1,s.body[0][1]);//��λ����ͷ���ƶ��������һ��
					printf("*");//��������ͷ,ԭ��ͷ����,�������.
					//�Ȱ���β������������Ա�Ե�ʳ���ʱ��ʹ��.
					x = s.body[s.snakelen-1][0];
					y = s.body[s.snakelen-1][1];
					//Ȼ��Ҫ������ͷ����β������
					for(int i=1; i<s.snakelen; i++) //��ѭ����ʽ����β��ʼ����������������
					{
						s.body[s.snakelen-i][0] = s.body[s.snakelen-(i+1)][0];
						s.body[s.snakelen-i][1] = s.body[s.snakelen-(i+1)][1];
					}
					//���ǵ��ߵĳ���Ϊ2�����,���Ա����ȸ�����β����,�ٸ�����ͷ����.
					s.body[0][0] = s.body[0][0]-1;
					s.body[0][1] = s.body[0][1];//������ͷ������.
				}
			}
			else if(ch2 == 77)//The key you Pressed is : ��
			{
				if(s.body[1][0] == s.body[0][0]+1);//�������߻�ͷ
				else
				{
					_SetHandlePosition(s.body[s.snakelen-1][0],s.body[s.snakelen-1][1]);//��λ����β������
					printf(" ");//ɾ����β
					_SetHandlePosition(s.body[0][0]+1,s.body[0][1]);//��λ����ͷ���ƶ��������һ��
					printf("*");//��������ͷ,ԭ��ͷ����,�������.
					//�Ȱ���β������������Ա�Ե�ʳ���ʱ��ʹ��.
					x = s.body[s.snakelen-1][0];
					y = s.body[s.snakelen-1][1];
					//Ȼ��Ҫ������ͷ����β������
					for(int i=1; i<s.snakelen; i++) //��ѭ����ʽ����β��ʼ����������������
					{
						s.body[s.snakelen-i][0] = s.body[s.snakelen-(i+1)][0];
						s.body[s.snakelen-i][1] = s.body[s.snakelen-(i+1)][1];
					}
					//���ǵ��ߵĳ���Ϊ2�����,���Ա����ȸ�����β����,�ٸ�����ͷ����.
					s.body[0][0] = s.body[0][0]+1;
					s.body[0][1] = s.body[0][1];//������ͷ������.
				}
			}
		}
	}
	_SetHandlePosition(GROUND_WIDTH/2-4,GROUND_HEIGHT/2);
	printf("YOU WIN!!!");
	_SetHandlePosition(0,GROUND_HEIGHT-1);//������ֹpause��Ϣ������ҵ���Ϸ��������ɲ�����.
	return 1;//ʧ���򷵻�-1.ʤ������1
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
