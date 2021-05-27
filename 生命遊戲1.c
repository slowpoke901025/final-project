#include<stdio.h>
#include<stdlib.h>
#include<windows.h> 
#define margin 10
#define num 50

				/**********變數,陣列,結構***********/ 

int Map[margin+2][margin+2]={};//主地圖,0為無生物,1為有生物--->用來存結果 
int map[margin+2][margin+2]={};//副地圖,紀錄主地圖,0為無生物,1為有生物 --->用來比較 
int change;//紀錄地圖是否有變化 
double speed;//控制畫面更新速度 



				/**********函式***********/ 

void gotoxy(int x,int y)//游標位移(windows.h) 
{
 HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

 COORD pos;

 pos.X = x;

 pos.Y = y;

 SetConsoleCursorPosition(handle,pos);	
}


void printMap()//印出目前生態情況 
{
	for(int i=1;i<=margin;i++)//座標row 
	{
		for(int j=1;j<=margin;j++)//座標col 
		{
			if(Map[i][j]>0)//存在 
			{
				printf("●");
				map[i][j]=1;//紀錄到副地圖 -->用於判斷下一世代情況
			}
			else//不存在 
			{
				printf("○");
				map[i][j]=0;//紀錄到地圖
			}
		}
		puts("");
	}
	
}


int nb(int r,int c) //回傳九宮格內生物數量 
{
	int n = 0;
	for(int i=r-1;i<=r+1;i++)
	{
		for(int j=c-1;j<=c+1;j++)
		{
			if(map[i][j]>0)//有生物存在 
			{
				n++;
			}
		}	
	}
	if(map[r][c]>0)
	{
		return n-1;//會算到自己故-1 
	}
	else
	{
		return n;
	}
	
}

int born(int r,int c) //繁殖新生物 
{
	Map[r][c]=1;
}

void Evolution() // 進行演化 
{
	for(int i=1;i<=margin;i++)//座標row 
	{
		for(int j=1;j<=margin;j++)//座標col 
		{
			if(map[i][j]>0)//該座標目前有生物 
			{
				if(nb(i,j)<2||nb(i,j)>3)//周圍生物小於2或大於3 
				{
					Map[i][j]=0; 
					change++;//地圖有改變 
				}
			}
			else//該座標目前無生物 
			{
				if(nb(i,j)==3)//周圍生物恰有3隻 
				{
					born(i,j); //在該座標上繁殖新生物 
					change++; //地圖有改變 
				}
			}
		}
	}
} 

				/*****主函式*****/ 
				
int main()
{	
	puts("**請輸入10組座標 (1,1) ~ (10,10)**\n");
	for(int i=0;i<10;i++)//輸入10組座標,於對應座標產生生物 
	{
		int row,col;
		printf("座標 %d (row,col):",i+1);
		scanf("%d%d",&row,&col);
		Map[row][col]=1;
	}
	puts("\n**生態系**");
	while(1)
	{
		if(speed==0)//speed為0時才執行 
		{
			gotoxy(0,15);
			printMap();
			Evolution();
	
			if(!change)//地圖沒改變--> 生態達到平衡 or 生態系瓦解  
			{
				system("pause");//停止 
			}
			else
			{
				change = 0;//歸零 
			}
	
			speed =200000000;//重製速度 
		}
		speed--;//每圈減少1 
	}
	
}
