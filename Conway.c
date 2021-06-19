#include<stdio.h>
#include<conio.h>
#include"Conway.h"
#include"Level.h"
#include"Map.h"
#include"Windows.h"


int nb(int r, int c) //�^�ǤE�c�椺�ͪ��ƶq 
{
	int n = 0;
	for (int row = r - 1; row <= r + 1; row++)
	{
		for (int col = c - 1; col <= c + 1; col++)
		{
			if (Map.vice[row][col] > 0)//���ͪ��s�b 
			{
				n++;
			}
		}
	}
	if (Map.vice[r][c] > 0)
	{
		return n - 1;//�|���ۤv�G-1 
	}
	else
	{
		return n;
	}

}


void Evolution() // �i��t�� 
{
	for (int row = 1; row <= Margin.row; row++)//�y��row 
	{
		for (int col = 1; col <= Margin.col; col++)//�y��col 
		{
			if (Map.vice[row][col] > 0)//�Ӯy�Хثe���ͪ� 
			{
				if (nb(row,col) < 2 || nb(row,col) > 3)//�P��ͪ��p��2�Τj��3 
				{
					Map.main[row][col] = 0;
				}
			}
			else//�Ӯy�Хثe�L�ͪ� 
			{
				if (nb(row,col) == 3)//�P��ͪ��꦳3�� 
				{
					Map.main[row][col] = 1;//�b�Ӯy�ФW�c�޷s�ͪ� 
				}
			}
		}
	}
}

void printBug()
{
	gotoxy(Bug.x,Bug.y);
	color(10);
	printf("��");
	color(15);
				
	if(Map.treasure[Bug.y][Bug.x])//���_�� 
	{
		getTreasure();	
	}
	if(Level.treasure==0&&Bug.x==Level.exit_X&&Bug.y==Level.exit_Y)
	{
		Level.pass++;
	}
}

void printMap()//�L�X�ثe�ͺA���p 
{
	int hit=0;
	HideCursor();
	gotoxy(1, 1);
	for (int row = 1; row <= Margin.row; row++)//�y��row 
	{
		gotoxy(1,row);
		for (int col = 1; col <= Margin.col; col++)//�y��col 
		{
			int BugIsHere=0;
				
			if(Bug.x==col && Bug.y==row)
			{
				color(10);
				printf("��");
				color(15);
				BugIsHere++;
			}
				
			if (Map.main[row][col] > 0)//�s�b 
			{	
				if(!BugIsHere)
				{
					printf("��");
				}
				else
				{
					crash(Bug.x,Bug.y);
					hit++;
				}
				Map.vice[row][col] = 1;//������Ʀa�� -->�Ω�P�_�U�@�@�N���p
			}
			else //Map.main[row][col] == 0
			{
				if(Map.treasure[row][col]>0)
				{
					if(Map.treasure[row][col]==1)
					{
						color(1);
					}
					else
					{
						color(4);	
					}
					
					printf("��");
					color(15);
				}
				else if(Level.treasure==0&&row==Level.exit_Y&&col==Level.exit_X)
				{
					color(6);
					printf("��");
					color(15);
				}
				else if(!BugIsHere)
				{
					printf("  ");
				}
				Map.vice[row][col] = 0;//������a��
			}
		}
	}
	if(hit)//���񭵮ķ|�Ȱ��{�ǡA�G���]���a�ϦA���� 
	{
		sound();
	}
		
}
void crash(int x,int y)//�����ͪ� 
{	
	pBlood('-');
	color(4);//����ĵ�� 
	gotoxy(x,y);
	printf("��");
	
	color(15);
	gotoxy(x+1,y);//��в��ܼ�����m��@��(�W�����b�ͩR��)	
	Time.start++;
}
void getTreasure()
{
	if(Map.treasure[Bug.y][Bug.x]==1)
	{
		Level.treasure--;
		gotoxy(Margin.col+7,4);
		printf("%d",Level.treasure);
		
		if(Level.treasure==0)
		{
			gotoxy(Level.exit_X,Level.exit_Y);
			color(6);
			printf("��");
		}
	}
	else
	{
		pBlood('+');
	}
	Map.treasure[Bug.y][Bug.x]=0;

}
void bugMove()//��L�禡 
{
	if (kbhit()) //�P�_��L�O�_����J 
	{
		char input = getch();//�q�w�İ�Ū�@�Ӧr 

		if (input == 'a')
		{
			if(Bug.x!=1)
			{
				if(!Map.vice[Bug.y][Bug.x-1])
				{
					gotoxy(Bug.x,Bug.y);
					printf("  ");
					Bug.x--;
					
				}
				else
				{
					crash(Bug.x-1,Bug.y);
					sound();
				}	
			}
		}
	
		else if (input == 'd')
		{
			if(Bug.x!=Margin.col)
			{
				if(!Map.vice[Bug.y][Bug.x+1])
				{
					gotoxy(Bug.x,Bug.y);
					printf("  ");
					Bug.x++;
				}
				else
				{
					crash(Bug.x+1,Bug.y);
					sound();
				}	
			}	
		}

		else if (input == 'w')
		{
			if(Bug.y!=1)
			{
				if(!Map.vice[Bug.y-1][Bug.x])
				{
					gotoxy(Bug.x,Bug.y);
					printf("  ");
					Bug.y--;
				}
				else
				{
					crash(Bug.x,Bug.y-1);
					sound();	
				}	
			}
		}
		
		else if (input == 's')
		{
			if(Bug.y!=Margin.row)
			{
				if(!Map.vice[Bug.y+1][Bug.x])
				{
					gotoxy(Bug.x,Bug.y);
					printf("  ");
					Bug.y++;
				}
				else
				{
					crash(Bug.x,Bug.y+1);
					sound();
				}
			}
		}

	}

}


