#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"Level.h"
#include"Windows.h"


struct BUG Bug;
struct MARGIN Margin;
struct TIME Time;
struct LEVEL Level;


void pBlood(char c)
{
	if(c=='+')
	{
		Bug.blood++;
	}
	else if(c=='-')
	{
		Bug.blood--;
	}
	
	color(4);
	gotoxy(Margin.col+5,6);//游標移至生命條 
	
	for(int i=1;i<=8;i++)//更新血條 至多8條 
	{
		if(i<=Bug.blood)
		{
			printf("■");
		}
		else
		{
		 	printf("  ");
		}
	}	
}
int pTime()
{
	Time.now=time(NULL);
	Time.left = Time.limit-(Time.now-Time.start);
	gotoxy(Margin.col+5,2);
	
	if(Time.left>=100)
	{
		printf("%d",Time.left);
	}
	else if(Time.left>=10)
	{
		printf(" %d",Time.left);
	}
	else
	{
		printf("  %d",Time.left);
	}
	
	return Time.left>0 ? 1:0;
}

void pSit()
{
	gotoxy(Margin.col+5,8);
	printf("%d %d ",Bug.x,Bug.y);
}

void Bound()//印出邊界 
{
	system("cls");
	color(15);
	for(int i=0;i<=Margin.row+1;i++)
	{
		for(int j=0;j<=Margin.col+1;j++)
		{
			if(i==0||i==Margin.row+1)
			{
				printf("□");
			}
			else if(j==0||j==Margin.col+1)
			{
				printf("□");
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}
}


void InfoBox()//印出資訊欄 
{
	color(15);
	gotoxy(Margin.col+2,0);
	
	for(int i=0;i<11;i++)
	{
		for(int j=0;j<13;j++)
		{
			gotoxy(Margin.col+2+j,i);
			if(i==0||i==10)
			{
				printf("□");
			}
			else if(j==12)
			{
				printf("□");
			}
			else
			{
				printf("  ");
			}
		} 
	}
	
	
	gotoxy(Margin.col+2,2);
	printf("*時間:%d",Time.limit);
	
	gotoxy(Margin.col+2,4);
	printf("*剩餘寶物:%d",Level.treasure);
	
	gotoxy(Margin.col+2,6);
	printf("*生命:");
	color(4);
	printf("■■■■■");
	 
	
	color(15);
	gotoxy(Margin.col+2,8);
	printf("*座標:");
	
}
void setLevel(int level)
{
	switch(level){
		
		case 0:
			Margin.row=31;
			Margin.col=87;
			Time.limit=200;
			Bug.x=1;
			Bug.y=15;
			Level.exit_X=87;
			Level.exit_Y=16;
			Level.treasure=7;
			break;
		case 1:
			Margin.row=51;
			Margin.col=91;
			Time.limit=200;
			Bug.x=4;
			Bug.y=1;
			Level.exit_X=87;
			Level.exit_Y=51;
			Level.treasure=8;
			break;
		case 2:
			Margin.row=43;
			Margin.col=91;
			Time.limit=100;
			Bug.x=46;
			Bug.y=22;
			Level.exit_X=46;
			Level.exit_Y=14;
			Level.treasure=6;
			break;
		case 3:
			Margin.row=51;
			Margin.col=97;
			Time.limit=300;
			Bug.x=2;
			Bug.y=25;
			Level.exit_X=39;
			Level.exit_Y=26;
			Level.treasure=7;
			break;
		case 4:
			Margin.row=16;
			Margin.col=68;
			Time.limit=100;//
			Bug.x=24;//
			Bug.y=3;//
			Level.exit_X=62;//
			Level.exit_Y=9;//
			Level.treasure=12;
			break;
	}
	Bug.blood=5;
	Level.speed=0;
	Level.pass=0;
}
void getName(char name[])
{
	for(int i=0;i<5;i++)
	{
		gotoxy(39,23+i);
		for(int j=0;j<35;j++)
		{
			if(i==0||i==4)
			{
				printf("-");
			}
			else
			{
				printf(" ");
			}
		}
	}
	gotoxy(40,25);
	printf("Please enter your name: ");
	scanf("%[^\n]s",name);	
	system("cls");
}

