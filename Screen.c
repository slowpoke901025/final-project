#include<stdio.h>
#include"Screen.h"
#include"ScreenElement.h"
#include"Windows.h"

void printScreen(int map[][100])
{
	HideCursor();
	for(int i=1;i<=50;i++)
	{
		for(int j=1;j<=100;j++)
		{
		
			if(map[i][j])
			{
				printf("■");
			}
			else
			{
				printf("  ");
			}
		}
			sleep(30); 
		puts("");	
	}
	pressToContinue();
}




void story()
{
	int speed=0;
	char *str[10]={"「啊…頭好暈…」","「我怎麼在這裡？這裡是哪裡？」"," 從前從前，有一隻小跳蚤。\n"," 在路上跳著跳著 就不小心被路人吃下肚了！\n\n"," 你願意幫助它躲過障礙、逃出人體，最後重見光明嗎？"};
	int i=0,j=0;
	gotoxy(40,20);
	while(str[i]!=NULL)
	{
		if(str[i][j]!='\0')
		{
			printf("%c",str[i][j++]);
			sleep(50);
		}
		else
		{
			i++;
			j=0;
			gotoxy(40,20+i);
			if(i>=2)
			{
				gotoxy(40,20+i+1);
			}
			if(i==4)
			{
				gotoxy(40,20+i+2);
			}
			sleep(500);
		}
	}
	
	pressToContinue();
	
}

void showBeforeRun(int level)
{
	int mapTitle[55][100]={0};
	
	switch(level)
	{
		case 0:
			throat(30,30,mapTitle);
			break;
		case 1:
			stomach(32,22,mapTitle);
			break;		
		case 2:
			small(50,25,mapTitle);
			break;
			
		case 3:
			large(20,20,mapTitle);
			break;
		case 4:
			gonmen(35,10,mapTitle);
			break;
	}
	
	printScreen(mapTitle);
	
}
void printResult(int timeTotal)
{
	color(15);
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
	
	gotoxy(45,24);
	color(4);
	printf("*恭喜過關*");
	gotoxy(44,26);
	color(1);
	printf("你總共花了 %d 秒",timeTotal);
	pressToContinue();
	
}
void startUp()
{
	int map[55][100]={};
	adventure(50,25,map);
	printScreen(map);		
}
void fail()
{
	int map[55][100]={};
	gameover(25,20,map);
	color(4);
	printScreen(map);
}
void showBoard()
{
	int map[55][100]={};
    
    rankBoard(20,5,map);
    
    for(int i=1;i<=50;i++)
	{
		for(int j=1;j<=100;j++)
		{
			color(9);
		
			if(map[i][j])
			{
				printf("■");
			}
			else
			{
				printf("  ");//□
			}
		}
		puts("");
	}
	
} 
void animationStart()
{
	int map[55][100]={};
	int d_lip=10;
	HideCursor();
	
	for(int k=0;k<10;k++)
	{
		int q;
		if(k>3&&k<7)
		{
			q=36;
		}
		else
		{
			q=27;
		}
		
		for(int i=q;i<55;i++)//reset
		{
			gotoxy(19,i);
			for(int j=19;j<100;j++)
			{
				printf("  ");
				map[i][j]=0;
			}
			puts("");
		}
		
		
		left_eye(20,10,map);
		right_eye(20,10,map);
		up_lip(20,10,map);
		down_lip(20,d_lip,map);
		switch(k)
		{
			case 4:
				bug1(20,10,map);
				break;
			case 5:
				bug2(20,10,map);
				break;
			case 6:
				bug3(20,10,map);
				map[35][45]=0;
				gotoxy(45,35);
				printf("  ");
				break;
			case 7:
				bug4(20,10,map);
				break;
			case 8:
				bug5(20,10,map);
				break;
		}
		
		gotoxy(0,0);
		for(int i=0;i<55;i++)
		{
			for(int j=0;j<100;j++)
			{
				color(0);
				if(map[i][j])
				{
					if(map[i][j]==2)
					{
						color(4);
					}
					else if(map[i][j]==1)
					{
						color(15);
					}
					else if(map[i][j]==4)
					{
						color(10);
					}
					else
					{
						color(0);
					}
					printf("■");	
				}
				else
				{
					color(15);
					printf("  ");
				}	
			}
			puts("");
		}
		if(k<3)
		{
			d_lip++;
		}
		else if(k>5)
		{
			d_lip--;
		}
		sleep(400);
		
	} 
	pressToContinue();
}

void animationEnd()
{
	int map[55][100]={};
	pipi(1,1,map);
	HideCursor() ;
	for(int i=0;i<5;i++)
	{
		for(int i=1;i<=17;i++)
		{
			gotoxy(17,i);
			for(int j=17;j<30;j++)
			{
				map[i][j]=0;
				printf("  ");
			}
		}
		
		switch(i)
		{
			case 1:
				bug22(1,1,map);
				break;
			case 2:
				bug33(1,1,map);
				bug2die(1,1,map);
				break;
			case 3:
				bug44(1,1,map);
				break;
		}
		gotoxy(0,0);
		for(int i=1;i<40;i++)
		{
			for(int j=1;j<50;j++)
			{
				color(10);
				if(map[i][j])
				{
					if(map[i][j]==1)
					{
					  color(14);	
					}
					printf("■");
				}
				else
				{
					printf("  ");
				}
			}
			puts("");
		}
		sleep(500);
	}
}

