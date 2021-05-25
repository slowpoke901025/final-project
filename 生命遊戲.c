//規則
//生物的周圍有2或3隻生物 繼續存在
// 生物的周圍無生物,僅有1隻,或超過3隻  死亡
//無生物地區被恰好3隻包圍  繁殖一隻新生物

#include<stdio.h>
#include<stdlib.h>
#include<windows.h> 
#define margin 10
#define num 50

				/**********變數,陣列,結構***********/ 

struct creature //生物 
{
	int x;//位置 
	int y;
	int alive;//是否存活 
}ET[50];

int map[margin+2][margin+2]={};//紀錄地圖,0為無生物,1為有生物 
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


int exist(int x,int y)//判斷是否有生物存在,若有回傳其index,非則-1 
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


void printMap()//印出目前生態情況 
{
	for(int i=1;i<=margin;i++)//座標y 
	{
		for(int j=1;j<=margin;j++)//座標x 
		{
			if(exist(j,i)>=0)//存在 
			{
				printf("●");
				map[i][j]=1;//紀錄到地圖 -->用於判斷下一世代情況
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


int nb(int x,int y) //回傳九宮格內生物數量 
{
	int n = 0;
	for(int i=y-1;i<=y+1;i++)
	{
		for(int j=x-1;j<=x+1;j++)
		{
			if(map[i][j]>0)//有生物存在 
			{
				n++;
			}
		}	
	}
	if(map[y][x]>0)
	{
		return n-1;//會算到自己故-1 
	}
	else
	{
		return n;
	}
	
}

int born(int x,int y) //繁殖新生物 
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

void Evolution() // 進行演化 
{
	for(int i=1;i<=margin;i++)//座標y 
	{
		for(int j=1;j<=margin;j++)//座標x 
		{
			if(map[i][j]>0)//該座標目前有生物 
			{
				if(nb(j,i)<2||nb(j,i)>3)//周圍生物小於2或大於3 
				{
					int index = exist(j,i);//取得index 
					ET[index].alive = 0;// 死亡 
					change++;//地圖有改變 
				}
			}
			else//該座標目前無生物 
			{
				if(nb(j,i)==3)//周圍生物恰有3隻 
				{
					born(j,i); //在該座標上繁殖新生物 
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
		printf("座標 %d (x,y):",i+1);
		scanf("%d%d",&ET[i].x,&ET[i].y);
		ET[i].alive = 1;
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
