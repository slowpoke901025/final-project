#include<stdio.h>
#include<conio.h>
#include"Conway.h"
#include"Level.h"
#include"Map.h"
#include"Windows.h"


int nb(int r, int c) //回傳九宮格內生物數量 
{
	int n = 0;
	for (int row = r - 1; row <= r + 1; row++)
	{
		for (int col = c - 1; col <= c + 1; col++)
		{
			if (Map.vice[row][col] > 0)//有生物存在 
			{
				n++;
			}
		}
	}
	if (Map.vice[r][c] > 0)
	{
		return n - 1;//會算到自己故-1 
	}
	else
	{
		return n;
	}

}


void Evolution() // 進行演化 
{
	for (int row = 1; row <= Margin.row; row++)//座標row 
	{
		for (int col = 1; col <= Margin.col; col++)//座標col 
		{
			if (Map.vice[row][col] > 0)//該座標目前有生物 
			{
				if (nb(row,col) < 2 || nb(row,col) > 3)//周圍生物小於2或大於3 
				{
					Map.main[row][col] = 0;
				}
			}
			else//該座標目前無生物 
			{
				if (nb(row,col) == 3)//周圍生物恰有3隻 
				{
					Map.main[row][col] = 1;//在該座標上繁殖新生物 
				}
			}
		}
	}
}

void printBug()
{
	gotoxy(Bug.x,Bug.y);
	color(10);
	printf("蟲");
	color(15);
				
	if(Map.treasure[Bug.y][Bug.x])//有寶物 
	{
		getTreasure();	
	}
	if(Level.treasure==0&&Bug.x==Level.exit_X&&Bug.y==Level.exit_Y)
	{
		Level.pass++;
	}
}

void printMap()//印出目前生態情況 
{
	int hit=0;
	HideCursor();
	gotoxy(1, 1);
	for (int row = 1; row <= Margin.row; row++)//座標row 
	{
		gotoxy(1,row);
		for (int col = 1; col <= Margin.col; col++)//座標col 
		{
			int BugIsHere=0;
				
			if(Bug.x==col && Bug.y==row)
			{
				color(10);
				printf("蟲");
				color(15);
				BugIsHere++;
			}
				
			if (Map.main[row][col] > 0)//存在 
			{	
				if(!BugIsHere)
				{
					printf("■");
				}
				else
				{
					crash(Bug.x,Bug.y);
					hit++;
				}
				Map.vice[row][col] = 1;//紀錄到副地圖 -->用於判斷下一世代情況
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
					
					printf("●");
					color(15);
				}
				else if(Level.treasure==0&&row==Level.exit_Y&&col==Level.exit_X)
				{
					color(6);
					printf("★");
					color(15);
				}
				else if(!BugIsHere)
				{
					printf("  ");
				}
				Map.vice[row][col] = 0;//紀錄到地圖
			}
		}
	}
	if(hit)//播放音效會暫停程序，故先跑完地圖再播放 
	{
		sound();
	}
		
}
void crash(int x,int y)//撞擊生物 
{	
	pBlood('-');
	color(4);//紅色警示 
	gotoxy(x,y);
	printf("■");
	
	color(15);
	gotoxy(x+1,y);//游標移至撞擊位置後一位(上次停在生命條)	
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
			printf("★");
		}
	}
	else
	{
		pBlood('+');
	}
	Map.treasure[Bug.y][Bug.x]=0;

}
void bugMove()//鍵盤函式 
{
	if (kbhit()) //判斷鍵盤是否有輸入 
	{
		char input = getch();//從緩衝區讀一個字 

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


