#include<stdio.h>
#include<stdlib.h>
#include<windows.h> 
#define margin_r 50
#define margin_c 90 
#define num 50

				/**********�ܼ�,�}�C,���c***********/ 

int Map[margin_r+2][margin_c+2]={};//�D�a��,0���L�ͪ�,1�����ͪ�--->�ΨӦs���G 
int map[margin_r+2][margin_c+2]={};//�Ʀa��,�����D�a��,0���L�ͪ�,1�����ͪ� --->�ΨӤ�� 
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
void HideCursor() // �Ω����å���
{

CONSOLE_CURSOR_INFO cursor_info = {1, 0};

SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

}


void printMap()//�L�X�ثe�ͺA���p 
{
	HideCursor();
	for(int i=1;i<=margin_r;i++)//�y��row 
	{
		for(int j=1;j<=margin_c;j++)//�y��col 
		{
			if(Map[i][j]>0)//�s�b 
			{
				printf("��");
				map[i][j]=1;//������Ʀa�� -->�Ω�P�_�U�@�@�N���p
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


int nb(int r,int c) //�^�ǤE�c�椺�ͪ��ƶq 
{
	int n = 0;
	for(int i=r-1;i<=r+1;i++)
	{
		for(int j=c-1;j<=c+1;j++)
		{
			if(map[i][j]>0)//���ͪ��s�b 
			{
				n++;
			}
		}	
	}
	if(map[r][c]>0)
	{
		return n-1;//�|���ۤv�G-1 
	}
	else
	{
		return n;
	}
	
}

int born(int r,int c) //�c�޷s�ͪ� 
{
	Map[r][c]=1;
}

void Evolution() // �i��t�� 
{
	for(int i=1;i<=margin_r;i++)//�y��row 
	{
		for(int j=1;j<=margin_c;j++)//�y��col 
		{
			if(map[i][j]>0)//�Ӯy�Хثe���ͪ� 
			{
				if(nb(i,j)<2||nb(i,j)>3)//�P��ͪ��p��2�Τj��3 
				{
					Map[i][j]=0; 
					change++;//�a�Ϧ����� 
				}
			}
			else//�Ӯy�Хثe�L�ͪ� 
			{
				if(nb(i,j)==3)//�P��ͪ��꦳3�� 
				{
					born(i,j); //�b�Ӯy�ФW�c�޷s�ͪ� 
					change++; //�a�Ϧ����� 
				}
			}
		}
	}
} 

				/*****�D�禡*****/ 
				
int main()
{	

	int row,col,i=0;
	puts("**�п�J�y�� (1,1) ~ (50,90),�t�ư���**\n");
	while(1) 
	{
		printf("�y�� %d (row,col):",i+1);
		scanf("%d%d",&row,&col);     
		
		if(row>0 && col>0)
		{
			Map[row][col]=1;
			i++;
		}
		else
		{
			break;
		}
		
	}
	
	puts("\n**�ͺA�t**");
	while(1)
	{	
		if(speed==0)//speed��0�ɤ~���� 
		{
			gotoxy(0,0);
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
	
			speed =20000000;//���s�t�� 
		}
		speed--;//�C����1 
	}
	
}
