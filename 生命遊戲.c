#include<stdio.h>
#include<stdlib.h>
#include<windows.h> 
#define margin 10
#define num 50

				/**********�ܼ�,�}�C,���c***********/ 

struct creature //�ͪ� 
{
	int x;//��m 
	int y;
	int alive;//�O�_�s�� 
}ET[50];

int map[margin+2][margin+2]={};//�����a��,0���L�ͪ�,1�����ͪ� 
int change;//�����a�ϬO�_���ܤ� 
double speed;//����e����s�t�� 



				/**********�禡***********/ 

void gotoxy(int x,int y)//��Ц첾(windows.h) 
{
 HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

 COORD pos;

 pos.X = x;

 pos.Y = y;

 SetConsoleCursorPosition(handle,pos);	
}


int exist(int x,int y)//�P�_�O�_���ͪ��s�b,�Y���^�Ǩ�index,�D�h-1 
{
	for(int i=0;i<num;i++)
	{
		if(ET[i].alive)
		{
			if(ET[i].x==x && ET[i].y==y)
			{
				return i;
			}
		}
	}
	return -1;
	
}


void printMap()//�L�X�ثe�ͺA���p 
{
	for(int i=1;i<=margin;i++)//�y��y 
	{
		for(int j=1;j<=margin;j++)//�y��x 
		{
			if(exist(j,i)>=0)//�s�b 
			{
				printf("��");
				map[i][j]=1;//������a�� -->�Ω�P�_�U�@�@�N���p
			}
			else//���s�b 
			{
				printf("��");
				map[i][j]=0;//������a��
			}
		}
		puts("");
	}
	
}


int nb(int x,int y) //�^�ǤE�c�椺�ͪ��ƶq 
{
	int n = 0;
	for(int i=y-1;i<=y+1;i++)
	{
		for(int j=x-1;j<=x+1;j++)
		{
			if(map[i][j]>0)//���ͪ��s�b 
			{
				n++;
			}
		}	
	}
	if(map[y][x]>0)
	{
		return n-1;//�|���ۤv�G-1 
	}
	else
	{
		return n;
	}
	
}

int born(int x,int y) //�c�޷s�ͪ� 
{
	for(int i=0;i<num;i++)
	{
		if(ET[i].alive==0)
		{
			ET[i].alive = 1;
			ET[i].x = x;
			ET[i].y = y;
			break;
		}
	}
}

void Evolution() // �i��t�� 
{
	for(int i=1;i<=margin;i++)//�y��y 
	{
		for(int j=1;j<=margin;j++)//�y��x 
		{
			if(map[i][j]>0)//�Ӯy�Хثe���ͪ� 
			{
				if(nb(j,i)<2||nb(j,i)>3)//�P��ͪ��p��2�Τj��3 
				{
					int index = exist(j,i);//���oindex 
					ET[index].alive = 0;// ���` 
					change++;//�a�Ϧ����� 
				}
			}
			else//�Ӯy�Хثe�L�ͪ� 
			{
				if(nb(j,i)==3)//�P��ͪ��꦳3�� 
				{
					born(j,i); //�b�Ӯy�ФW�c�޷s�ͪ� 
					change++; //�a�Ϧ����� 
				}
			}
		}
	}
} 

				/*****�D�禡*****/ 
				
int main()
{	
	puts("**�п�J10�ծy�� (1,1) ~ (10,10)**\n");
	for(int i=0;i<10;i++)//��J10�ծy��,������y�в��ͥͪ� 
	{
		printf("�y�� %d (x,y):",i+1);
		scanf("%d%d",&ET[i].x,&ET[i].y);
		ET[i].alive = 1;
	}
	puts("\n**�ͺA�t**");
	while(1)
	{
		if(speed==0)//speed��0�ɤ~���� 
		{
			gotoxy(0,15);
			printMap();
			Evolution();
	
			if(!change)//�a�ϨS����--> �ͺA�F�쥭�� or �ͺA�t�˸�  
			{
				system("pause");//���� 
			}
			else
			{
				change = 0;//�k�s 
			}
	
			speed =200000000;//���s�t�� 
		}
		speed--;//�C����1 
	}
	
}
