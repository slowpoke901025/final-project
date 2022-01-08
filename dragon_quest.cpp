#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <math.h>

#define SCREEN_HEIGHT 500 //設定遊戲視窗高度 
#define SCREEN_WIDTH 500 //設定遊戲視窗寬度
#define GRID_SIDE 40 //設定遊戲方陣每邊格子數量 
#define LEFT_MARGINE 30 //設定左邊界 
#define TOP_MARGINE 40 //設定上邊界 
#define FOOD_AMOUT 1 //設定每次產生食物數量 
#define INIT_SPEED  800 //設定初始惡龍移動速度 
#define MAX_QUEUE_SIZE 1600 //設定柱列大小 
#define DRAGON_SPEED 1500
#define BULLET_SPEED 800
//宣告前進方向列舉函數 
enum Direction {
	RIGHT, 
	LEFT, 
	UP, 
	DOWN,
};

//宣告遊戲場出現物體列舉函數 
enum Object {
	EMPTY, //空白 
	WALL, //牆或障礙物 
	FOOD, //食物
	DEVIL 
};

enum Mode
{
	NORMAL,
	ANGRY,
	HUNGRY
};

//宣告惡龍身體節點結構 
struct Node {
	int row; //節點位在第幾行 
	int col; //節點位在第幾列 
	Direction direct; //該節點的前進方向 
	struct Node *next;	//指向下一個節點 
	struct Node *pre;
}; 

//定義指向節點結構的指標變數 
typedef struct Node *NodePointer;

//定義座標結構 
struct Location {
	int row;
	int col;
};

typedef struct PathNode *PathPointer;

//定義路徑節點結構，用來建立移動路徑 
struct PathNode {
	int cost; //距離原點的步數 
	int steps; //距離目標的步數 
	Location loc;
	PathPointer parent;
	PathPointer next;
};

#define DECK_NUM  3
enum Bmode {NONE,READY,ING};
enum Btype {BREAK,FREEZE,TRAP};
int front_B = 0, rear_B = 0;


typedef struct Bullet
{
	int row;
	int col;
	Btype type;
	Direction dir;
	struct Bullet *next,*pre;
}Bullet;

typedef struct
{
	Bullet *first;
	Bullet *last;	
}Flying;

Flying Fly={};

void addFly(Bullet *B)
{
	if(!Fly.first)
	{
		Fly.first = Fly.last = B;
		B->next = B->pre = NULL;
	}
	else
	{
		Fly.last->next = B;
		B->pre = Fly.last;
		Fly.last = B;
	}
}

void removeFly(Bullet *B)
{
	if(B->pre)
	B->pre->next = B->next;
	else
	Fly.first = B->next;
	
	if(B->next)
	B->next->pre = B->pre;
	else
	Fly.last = B->pre;
	
	free(B);
}


Btype Deck[DECK_NUM+1];

Btype drawBullet()
{
	srand(time(NULL));
	Deck[rear_B] = (Btype)(rand()%DECK_NUM);
	rear_B = (rear_B+1)%(DECK_NUM+1);
}


Btype useBullet()
{
	Btype type = Deck[front_B];
	front_B = (front_B+1)%(DECK_NUM+1);
	return type;
}
bool isFilled()
{
	return (rear_B+1)%(DECK_NUM+1) == front_B;
}
bool isEmpty()
{
	return front_B == rear_B;
}
void openWindow(); //開啟游戲視窗 
void closeGame(); //處理遊戲結束邏輯 
int playGame(int field[][GRID_SIDE], NodePointer dragon, NodePointer player); //遊戲進行邏輯 
bool IsGameOver(NodePointer dragon, NodePointer player, int field[][GRID_SIDE]); //惡龍是否死亡(死亡條件：撞牆和撞到自己身體) 
int showGameOverMsg(); //遊戲結束訊息
void showInfo(); //顯示遊戲相關資訊 
void drawGameField(int field[][GRID_SIDE]); //繪製遊戲區域 
void drawSquare(int row, int col, int color); //繪製方塊 
void drawCircle(int row, int col, int color);//
void controlDragonDirection(int field[][GRID_SIDE], NodePointer dragon, NodePointer player); //讀取AI輸入，並設定到所有惡龍節點 
void controlPlayerDirection(int field[][GRID_SIDE], NodePointer player, NodePointer dragon); //讀取鍵盤方向輸入，或者AI輸入
void controlBulletDirection(int field[][GRID_SIDE], NodePointer player, NodePointer dragon); 
void moveNext(NodePointer dragon, NodePointer player); //繪製惡龍每前進一步的身體改變  
void createFood(int field[][GRID_SIDE],Object obj ,NodePointer dragon,NodePointer player); //產生食物 
bool IsAtWall(int field[][GRID_SIDE], int row, int col); //判斷是否撞到牆  
NodePointer IsAtDragon(NodePointer dragon, int row, int col); //判斷是否撞到惡龍自己的身體
bool IsAtPlayer(NodePointer player, int row, int col);
bool IsAtObject(int field[][GRID_SIDE], int row, int col);
bool IsCloseDragon(NodePointer dragon, int row, int col);
void dragonEatFood(int field[][GRID_SIDE], NodePointer dragon,NodePointer player); //處理惡龍吃到食物邏輯 
void playerEatFood(int field[][GRID_SIDE], NodePointer player,NodePointer dragon); //處理玩家吃到食物邏輯 
void addNode(NodePointer dragon); //增加惡龍身體節點
Location nextStepLoc(NodePointer node, Direction direct);
Location findNearestFood(int field[][GRID_SIDE], NodePointer dragon); //尋找最接近食物的座標 
Direction safeDirection(int field[][GRID_SIDE], NodePointer player, NodePointer dragon);
Direction safeDirectionD(int field[][GRID_SIDE], NodePointer dragon);

PathPointer findPath(int field[][GRID_SIDE], Location startLoc, Location goalLoc); //尋找兩點之間可到達的路徑
PathPointer heroFindPath(int field[][GRID_SIDE], Location startLoc, Location goalLoc, NodePointer dragon);
void addPathQueue(PathNode pathNode); //將之後要拜訪的節點放入佇列裡 
PathPointer popPathQueue(); //傳回柱列中的元素，並將它從柱列中刪除 
bool isPathQueueEmpty(); //判斷柱列是否為空 
void resetPathQueue(); //重設柱列 
void sortPathQueue(); //對柱列中的元素進行排序 
bool IsInPathQueue(PathNode pathNode); //判斷該元素是否在柱列之中 
PathPointer buildPath(PathPointer goal); //回傳到目標位置的路徑串列 
int calcSteps(Location start, Location goal); //計算兩點之間需要移動的步數 
bool visited(Location loc); //判斷是否該節點已經拜訪過 
Direction getDirectionByPath(NodePointer dragon); //從路徑資料判斷下一步方向 

Direction dragonAI(int field[][GRID_SIDE], NodePointer dragon, NodePointer player); //惡龍AI 
Direction playerAI(int field[][GRID_SIDE], NodePointer player, NodePointer dragon); //勇者AI 

struct PathNode pathQueue[MAX_QUEUE_SIZE]; //宣告將要拜訪的節點柱列 
int front; //queue 第一個元素的前一個位置 
int rear; //queue 最後一個元素的位置

int speed_D = DRAGON_SPEED, speed_B = BULLET_SPEED; //遊戲移動速度 
int scoreSum = 0; //紀錄分數 
int totalTime = 0; //紀錄遊戲時間 
int const scorePerFood = 1; //每一份食物可得分數 
bool meetSelfWillDie = false; //決定惡龍撞到自己身體是否會死掉 
bool IFPlayAI = false; //是否開啟AI模式 
bool stupid = 1;
Mode modeD = NORMAL;
int colorD = RED;

void moveNext_Player(NodePointer player);
void moveNext_Dragon(NodePointer dragon);


void shot(NodePointer player,int field[][GRID_SIDE] )
{
	
	if(isEmpty())return;
	
	int row = player->row;
	int col = player->col;
	Direction dir;
	

	
	switch(player->direct)
	{
		case UP:
			--row;
			dir = UP;
			break;
				
		case DOWN:
			++row;
			dir = DOWN;
			break;
				
		case LEFT:
			--col;
			dir = LEFT;
			break;
					
		case RIGHT:
			++col;
			dir = RIGHT;
			break; 
					
	}
	
	if(!IsAtWall(field,row,col))
	{
		Bullet *bullet = (Bullet*)malloc(sizeof(Bullet));
		bullet->type = useBullet();
		bullet->row = row;
		bullet->col = col;
		bullet->dir = dir;
		addFly(bullet);
		drawCircle(row,col,BLUE);
	}
	
}
void controlBulletDirection(int field[][GRID_SIDE], NodePointer player, NodePointer dragon)
{
	
	Bullet *B = Fly.first; 
	while(B)
	{
			
		int row = B->row;
		int col = B->col;
		drawCircle(row,col,BLACK);
			
			switch(B->dir)
			{
				case UP:
					--row;
					break;
						
				case DOWN:
					++row;
					break;
						
				case LEFT:
					--col;
					break;
							
				case RIGHT:
					++col;
					break; 				
			}
			
			NodePointer pos;
			if(IsAtWall(field,row,col))
			{
				removeFly(B);
			}
			else if((pos=IsAtDragon(dragon,row,col)))
			{
				drawCircle(row,col,YELLOW);
				delay(100);
				
				NodePointer temp;
				if(pos->pre)
				{
					pos->pre->next = NULL;
				}
				else
				{
					temp = pos->next;
					pos->next = NULL;
					pos = temp;
				}
				
				while(pos)
				{
					temp = pos;
					drawSquare(pos->row,pos->col,BLACK);
					pos = pos->next;
					free(temp);
				}
				removeFly(B);
				
			}
			else
			{
				B->row = row;
				B->col = col;
				
				switch(B->type)
				{
					case BREAK:
						drawCircle(row,col,BROWN);
						break;
					
					case FREEZE:
						drawCircle(row,col,CYAN);
						break;
						
					case TRAP:
						drawCircle(row,col,LIGHTMAGENTA);
						break;
					
					
				}
				
			}
			
			B = B->next;
			
		}
	
		
}
// 主程式      
int main( ){  	
	openWindow();
	
	while(TRUE){
	
		Node headPlayer = {2, 4, RIGHT, NULL,NULL}; //設定勇者初始位置和方向 
		Node headDragon = {15, 15, RIGHT, NULL,NULL}; //設定龍頭初始位置和方向 
		NodePointer dragon = &headDragon;
		NodePointer player = &headPlayer;
		
		//設定遊戲場和障礙物 
	   	int field[GRID_SIDE][GRID_SIDE] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		   								   {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
										   {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
										   {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
										   {1,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
										   {1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,2,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,1,1,1,1,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,1,1,1,1,0,0,1},
										   {1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1},
										   {1,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,1},
										   {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
										   {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
										   {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
										   {1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
										   {1,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1},
										   {1,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,2,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
										   {1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
										   {1,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1},
										   {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}; 
	   	
		
		totalTime = time(NULL);
		playGame(field, dragon, player); //進行遊戲
			    
	}
}

//開啟游戲視窗
void openWindow(){
	initwindow(SCREEN_WIDTH*1.5 + LEFT_MARGINE * 3, SCREEN_HEIGHT + TOP_MARGINE * 3, "Hungry dragon Game");
	
}

//處理遊戲結束邏輯 
void closeGame(){
	//free(dragon);
	exit(0);
}

void randomFood(int field[][GRID_SIDE], NodePointer dragon, NodePointer player)
{
	srand((unsigned)time(NULL));
	if (rand() % 30 == 0)
		createFood(field,DEVIL, dragon,player);
}
void drawInfo()
{
	int row = 0,col = GRID_SIDE;
	
	for(int row=0; row<10;row++)
	{
		for(int col=GRID_SIDE+2;col<GRID_SIDE+15;col++)
		{
			if((row!=0 && row != 9) && col!= GRID_SIDE+2 && col != GRID_SIDE+14)
			continue;
			
			drawSquare(row,col,YELLOW);
		}
	}
		
}
//遊戲進行邏輯
int playGame(int field[][GRID_SIDE], NodePointer dragon, NodePointer player) {
	
	drawGameField(field); //繪製遊戲區域 
	drawInfo();
	moveNext_Player(player);
	createFood(field, FOOD,dragon,player); //產生第一份食物 
	
	while(1){
				
		controlPlayerDirection(field, player, dragon);//讀取玩家輸入方向鍵，並將新方向設定到各惡龍節點 
	
		playerEatFood(field, player,dragon); //判斷玩家是否有吃到食物，如果有增加分數 
		
		
		if(--speed_B == 0)
		{
			controlBulletDirection(field, player, dragon);
			speed_B = BULLET_SPEED;
		}
		if(--speed_D == 0)
		{
			controlDragonDirection(field, dragon, player); 
			moveNext_Dragon(dragon);
			dragonEatFood(field, dragon,player); //判斷惡龍是否有吃到食物，如果有新增節點到尾巴
			speed_D = DRAGON_SPEED;
		}
		
		randomFood(field, dragon,player);
		
		 
		showInfo(); //顯示時間和分數資訊 
		
		if(IsGameOver(dragon, player, field)) //判斷是否符合遊戲結束條件， 
			return showGameOverMsg(); //顯示遊戲結束訊息，並等待玩家輸入選項 
	 
		
	}
}

//繪製遊戲區域，依據遊戲場矩陣設定繪製物件 
void drawGameField(int field[][GRID_SIDE]){
   	int row = 0, col = 0;
   	cleardevice(); //清理螢幕畫面 
	for(row = 0; row < GRID_SIDE; row ++){
   		for(col = 0; col <  GRID_SIDE; col++){
				switch(field[row][col])	{
					case WALL: //牆在矩陣中的值是1 
						drawSquare(row, col, YELLOW);
						break;
					case FOOD: //食物在矩陣中的值是2
						drawSquare(row, col, GREEN);
						break;	
				}	
		   }
	}
}


//繪製方塊
void drawSquare(int row, int col, int color){
	
	int squareHeight = SCREEN_HEIGHT / GRID_SIDE;
   	int SquareWidth = SCREEN_WIDTH / GRID_SIDE;
	int left = 0, right = 0, bottom = 0, top = 0;
	left = LEFT_MARGINE + col * SquareWidth + col;
   	top =  TOP_MARGINE + row * squareHeight + row;
	right = left + SquareWidth;
   	bottom = top + squareHeight;
   	 
	setfillstyle(SOLID_FILL,color); //設定繪製物件的為實心和顏色 
   	bar(left , top, right, bottom);	//設定繪製方塊的位置 
}

void drawCircle(int row, int col, int color){
	
	int squareHeight = SCREEN_HEIGHT / GRID_SIDE;
   	int SquareWidth = SCREEN_WIDTH / GRID_SIDE;
   	int left = 0, right = 0, bottom = 0, top = 0;
   	left = LEFT_MARGINE + col * SquareWidth + col;
   	top =  TOP_MARGINE + row * squareHeight + row;
	right = left + SquareWidth;
   	bottom = top + squareHeight;
   	
   	
   	setcolor(color);
   	setfillstyle(SOLID_FILL,color);
   	fillellipse(left+SquareWidth/2,top+squareHeight/2,SquareWidth/2,squareHeight/2);
	
}

//繪製惡龍每前進一步的身體改變 
void moveNext(NodePointer dragon, NodePointer player) {

	moveNext_Player(player);
	moveNext_Dragon(dragon);
}

void moveNext_Dragon(NodePointer dragon)
{
	int currRow, currCol;
	NodePointer head = dragon;
	while (dragon != NULL){
		currRow = dragon->row;
		currCol = dragon->col;
		
		//依據節點的方向屬性，設定移動下一步的位置	
		switch(dragon->direct){
			case RIGHT:
				dragon->col++;
				break;			
			case LEFT:
				dragon->col--;
				break;
			case UP:
				dragon->row--;
				break;			
			case DOWN:
				dragon->row++;
				break;
		}

		drawSquare(dragon->row, dragon->col, colorD);
		
		if (!dragon -> next && !IsAtDragon(dragon, currRow, currCol))
			drawSquare(currRow, currCol, BLACK);
			
		dragon = dragon -> next;	
	}	
	
}

void moveNext_Player(NodePointer player)
{
	if (player){
		
		int currRow = player->row;
		int currCol = player->col;
		Direction dir = player->direct;
		//player->direct = STOP;
		
		switch(dir){
			case RIGHT:
				
				player->col++;
				break;			
			case LEFT:
				player->col--;
				break;		
			case UP:
				player->row--;
				break;
								
			case DOWN:
				player->row++;
				break;				
		}
			drawSquare(currRow, currCol, BLACK);
			drawSquare(player->row, player->col, BLUE);
	} 
	
}

//惡龍是否死亡(死亡條件：撞牆和撞到自己身體) 
bool IsGameOver(NodePointer dragon, NodePointer player, int field[][GRID_SIDE]){
	NodePointer head = dragon;
	
	if(!head)return true;
	//判斷是否撞到牆 
	if (IsAtWall(field, head->row, head->col))
		return true;
	if (IsAtWall(field, player->row, player->col))
		return true;
	
	
	//判斷是否撞到惡龍自己 
	if(meetSelfWillDie)
		return IsAtDragon(dragon->next, head->row, head->col);
	
	//檢查是否AI撞到龍 
	if(player != NULL) {
		if(IsAtDragon(dragon, player->row, player->col))
			return true;
	}
	
	return false;
}

//判斷是否撞到牆
bool IsAtWall(int field[][GRID_SIDE], int row, int col){
		if (field[row][col] == WALL)
			return true;
		return false;
}
bool IsAtObject(int field[][GRID_SIDE], int row, int col)
{
	if (field[row][col] == FOOD)
	{
		return true;		
	}
		return false;
}
//判斷是否撞到惡龍自己的身體
NodePointer IsAtDragon(NodePointer dragon, int row, int col){

	while(dragon != NULL){
		if (row == dragon->row && col == dragon->col)
			return dragon;
		dragon = dragon -> next;
	}
	return NULL;
}

bool IsAtPlayer(NodePointer player, int row, int col)
{
	return player->row == row && player->col == col;	
} 

void exception(int key)
{
	
	if (key == 'q' || key == 'Q'){
	
			closeGame();
	}
		else if(key == 's' || key == 'S')
		{
			
		}

		else if (key == 'a') //決定是否改變模式 ，主要有玩家模式和電腦操控的AI模式 
		{
			IFPlayAI = !IFPlayAI;
			if(modeD == ANGRY)
			{
				modeD = NORMAL;
			}else
			{
				modeD = ANGRY;
			}
			
		}
			
		
}

//讀取鍵盤方向輸入，並設定到所有惡龍節點 
void controlPlayerDirection(int field[][GRID_SIDE], NodePointer player, NodePointer dragon) {
	
	
	//get key code by pressing keybord
	
	
	
	if(kbhit()) {
		
		bool flag = true;
		int key = getch();
		switch(key){
			case KEY_RIGHT:
				player -> direct = RIGHT;
				break;
							
			case KEY_LEFT:
				player -> direct = LEFT;
				break;	
					
			case KEY_UP:
				player -> direct = UP;
				break;	
							
			case KEY_DOWN:
				player -> direct = DOWN;
				break;
			
			case ' ':
				shot(player,field);
			default:
				flag = false;
							
		}
		
		if(flag)
		{
			moveNext_Player(player);
			char ch;
			while (kbhit()) 
			{
				ch=getch();
			}
		}
		
		else
		exception(key);
		
	
	}
	
	if (IFPlayAI)
	{
		player->direct = playerAI(field, player, dragon);
		moveNext_Player(player);
	}
		
		
	
	
			
}


//讀取鍵盤方向輸入，並設定到所有惡龍節點 
void controlDragonDirection(int field[][GRID_SIDE], NodePointer dragon, NodePointer player) {
		
	Direction dragonDirect = dragonAI(field, dragon, player);
	//為了達到像龍一樣移動方式，當龍改變方向時，並不是整個身體一起改變，
	//而是延遲性地，各個節點逐一改變，當一個節點收到新的前進方向時，
	//會將自己目前的方向傳給下一個。 
	Direction temp;
	while(dragon != NULL){
		temp = dragon -> direct;
		dragon -> direct = dragonDirect;
		dragonDirect = temp;
		dragon = dragon -> next;
	}
}

//產生食物
void createFood(int field[][GRID_SIDE],Object obj, NodePointer dragon,NodePointer player){
	int row, col, i, foodAmount = FOOD_AMOUT;
	srand((unsigned)time(NULL)); //取目前系統時間作為亂數種子 

	for(i=0; i< foodAmount; i++){
		//如果亂數產生的位置是在牆和龍身體重疊，則重新產生，直到符合條件為止 
		do{
			row = rand() % GRID_SIDE;
			col = rand() % GRID_SIDE;	
		}while(IsAtWall(field, row, col) || IsAtDragon(dragon, row, col) || IsAtPlayer(player,row,col)||IsAtObject(field,row,col));
	
		field[row][col] = obj;
		if(obj == FOOD)
		drawSquare(row,col, GREEN);
		else if(obj == DEVIL)
		drawCircle(row,col, WHITE);
	}
}

//處理惡龍吃到食物邏輯
void dragonEatFood(int field[][GRID_SIDE], NodePointer dragon,NodePointer player){
	//如果龍頭與食物位置重疊，就是吃到食物 
	if(field[dragon->row][dragon->col] == FOOD){
		field[dragon->row][dragon->col] = EMPTY; //將該食物清空 
		printf("The dragon has eaten food at row: %d, col: %d\n", dragon->row, dragon->col);
		addNode(dragon); //增加節點  
		createFood(field, FOOD,dragon,player); //產生新的食物 
	}
	else if(field[dragon->row][dragon->col] == DEVIL)
	{
		modeD = ANGRY;
		colorD = LIGHTRED;
	} 
}

//處理玩家吃到食物邏輯
void playerEatFood(int field[][GRID_SIDE], NodePointer player, NodePointer dragon){
	//如果龍頭與食物位置重疊，就是吃到食物 
	if(field[player->row][player->col] >= FOOD){
		field[player->row][player->col] = EMPTY; //將該食物清空 
		printf("The player has eaten food at row: %d, col: %d\n", player->row, player->col);
		scoreSum = scoreSum + scorePerFood; //紀錄分數 
		createFood(field,FOOD,player,dragon); //產生新的食物
		
		if(!isFilled())
		{
			drawBullet();
		}
		 
	}
}

//增加惡龍身體節點
void addNode(NodePointer dragon){
	NodePointer tail = NULL;
	NodePointer newNode = (NodePointer) malloc(sizeof(Node)); //初始化一個新節點 
	//尋找龍的尾巴 
	while(dragon != NULL){
		tail = dragon;
		dragon = dragon -> next;
	}
	//將龍尾巴的方向屬性給新節點 
	newNode -> direct = tail -> direct;
	
	//決定新節點的位置，依據尾巴的移動方向來掛上新節點 
	switch(tail->direct){
		case RIGHT:
			newNode -> row = tail -> row;
			newNode -> col = tail -> col - 1;
			break;			
		case LEFT:
			newNode -> row = tail -> row;
			newNode -> col = tail -> col + 1;			
			break;
		case UP:
			newNode -> row = tail -> row + 1;
			newNode -> col = tail -> col;			
			break;
		case DOWN:
			newNode -> row = tail -> row - 1;
			newNode -> col = tail -> col;			
			break;
	}
	
	tail -> next = newNode; //將尾巴節點連接到新節點
	newNode->pre = tail; 
	newNode -> next = NULL;		
}

//龍的AI控制 
PathPointer pathDtoF = NULL;
Location oldFood;

Direction dragonAI(int field[][GRID_SIDE], NodePointer dragon, NodePointer player) {
	
	
	Direction dragonDirect = dragon -> direct;
	Location start = {dragon -> row, dragon -> col};
	
	if(modeD == NORMAL)
	{
		Location newFood = findNearestFood(field, dragon);
	
		if(oldFood.col != newFood.col || oldFood.row != newFood.row)
		{
			oldFood = newFood;
			pathDtoF = findPath(field, start, newFood);
		}
		
	}
	else if(modeD == ANGRY)
	{
		Location target = {player->row, player->col};
		pathDtoF = heroFindPath(field,start,target,dragon);
	}
	
	
	
	if(pathDtoF)
	{
		dragonDirect = getDirectionByPath(dragon);
	}	
	else
	{
		dragonDirect = safeDirectionD(field, dragon);
	}
	
	return dragonDirect;
}

//從路徑資料判斷下一步方向 
Direction getDirectionByPath(NodePointer dragon){
	
	PathPointer nextPath = pathDtoF->next;
	pathDtoF = pathDtoF->next;
	
	int horizontal = nextPath->loc.col - dragon->col;
	int vertical = nextPath->loc.row - dragon->row;
	if(horizontal == 1)
		return RIGHT;
	else if(horizontal == -1)
		return LEFT;
	
	if(vertical == 1)
		return DOWN;
	else if(vertical == -1)
		return UP;
	return 	dragon -> direct;		
}


Direction Loc;
Direction safeDirectionD(int field[][GRID_SIDE], NodePointer dragon){
	int i;
	int dirSize = 4;
	Location loc;
	
		
	loc = nextStepLoc(dragon, UP);Loc = UP;
	if(!IsAtWall(field, loc.row, loc.col))
		return UP;

	loc = nextStepLoc(dragon, DOWN);Loc = DOWN;
	if(!IsAtWall(field, loc.row, loc.col))
		return DOWN;
	loc = nextStepLoc(dragon, RIGHT);Loc = RIGHT;
	if(!IsAtWall(field, loc.row, loc.col))
		return RIGHT;
	loc = nextStepLoc(dragon, LEFT);Loc = LEFT;
	if(!IsAtWall(field, loc.row, loc.col))
		return LEFT;						
	return dragon->direct;
}

//尋找兩點之間可到達的路徑
PathPointer findPath(int field[][GRID_SIDE], Location startLoc, Location goalLoc){
	resetPathQueue();
	int steps = calcSteps(startLoc, goalLoc);
	PathNode start = {0, steps, startLoc, NULL, NULL};
	addPathQueue(start);//first pathNode
	while(!isPathQueueEmpty()){
		sortPathQueue();
		PathPointer current = popPathQueue();
		if(current->loc.row == goalLoc.row && current->loc.col == goalLoc.col)
			return buildPath(current);
		int dirSize = 4;
		int iDir[] = {1, 0, -1, 0};
		int jDir[] = {0, 1, 0, -1};
		int i,j;
		for(i=0, j=0; i<dirSize; i++, j++){
			Location neighborLoc = {current->loc.row + iDir[i], current->loc.col + jDir[j]};
			if(!visited(neighborLoc) && !IsAtWall(field, neighborLoc.row, neighborLoc.col)){
				int steps = calcSteps(neighborLoc, goalLoc);
				int cost = 	current->cost + 1;
				PathNode neighbor = {cost, steps, neighborLoc, current, NULL};
				if(!IsInPathQueue(neighbor)){
					addPathQueue(neighbor);
				}				
			}
		}
		
	}
	return NULL;
}

//將之後要拜訪的節點放入佇列裡
void addPathQueue(PathNode pathNode){
//	printf("addPathQueue\n");
	if(rear == MAX_QUEUE_SIZE - 1){
		printf("the queue is full");
		return;
	}
	rear += 1;
	pathQueue[rear]	= pathNode;
}

//傳回柱列中的元素，並將它從柱列中刪除
PathPointer popPathQueue(){
//	printf("popPathQueue\n");
	if(front == rear){
		printf("the queue is empty");
		return NULL;
	}
	front ++;
	PathPointer node = (PathPointer)malloc(sizeof(PathNode));
	node->cost = pathQueue[front].cost;
	node->steps = pathQueue[front].steps;
	node->loc = pathQueue[front].loc;
	node->parent = pathQueue[front].parent;
	node->next = pathQueue[front].next;
	return node;
}

//判斷柱列是否為空
bool isPathQueueEmpty(){
//	printf("isPathQueueEmpty\n");
	return front == rear;
}

//重設柱列 
void resetPathQueue(){
//	printf("resetPathQueue\n");
	front = -1;
	rear = -1;	
}

//對柱列中的元素進行排序 
void sortPathQueue(){
//	printf("sortPathQueue\n");
	if(front == rear)
		return;
	int i, j;
	int nowTotal, nextTotal;	
	for(i=front + 1; i<rear; i++){
		
		nowTotal = pathQueue[i].cost + pathQueue[i].steps;
		
		for(j=i+1; j<=rear; j++){

			
			nextTotal = pathQueue[j].cost + pathQueue[j].steps;

			if(nowTotal > nextTotal){
				PathNode temp =  pathQueue[i];
				pathQueue[i] = pathQueue[j];
				pathQueue[j] = temp;
				nowTotal = nextTotal;
			}
		}
	}		
}

//判斷該元素是否在柱列之中
bool IsInPathQueue(PathNode pathNode){
//	printf("IsInPathQueue\n");
	int i;
	if(front == rear)
		return false;
	for(i=front;i<=rear;i++){
		if(pathQueue[i].loc.row == pathNode.loc.row && pathQueue[i].loc.col == pathNode.loc.col)
			return true;
	}
	return false;
}

//回傳到目標位置的路徑串列 
PathPointer buildPath(PathPointer goal){
//	printf("buildPath ");
//	printf("(%d, %d)\n", goal->loc.row, goal->loc.col);
	if(goal == NULL || goal->parent == NULL)
		return NULL;
	PathPointer head = goal;
	head->next = NULL;
	PathPointer temp = head;
	
	while(head->parent){
		
//		printf("node (%d, %d)->", head->loc.row, head->loc.col);	
		head = head->parent; 
		head->next = temp;
		temp = head;
	}
//	printf("NULL\n");
	return head;
}

//計算兩點之間需要移動的步數 
int calcSteps(Location start, Location goal){
	//printf("calcSteps\n");
	int steps = abs(start.row - goal.row) + abs(start.col - goal.col);
	return steps;
}

//判斷是否該節點已經拜訪過 
bool visited(Location loc){
	//printf("visited\n");
	int i;
	for(i=0;i<=front;i++){
		if(pathQueue[i].loc.row == loc.row && pathQueue[i].loc.col == loc.col)
			return true;
	}
	return false;
}

//尋找最接近食物的座標 
Location findNearestFood(int field[][GRID_SIDE], NodePointer me){
	int rowDis, colDis, row, col, nearest = 100000;
	Object target = FOOD;
	
	Location nearestFood = {-1, -1};
	for(row = 0; row < GRID_SIDE; row++){
		for(col = 0; col < GRID_SIDE; col++){
			if(field[row][col] == target){
				rowDis = abs(row - me -> row);
				colDis = abs(col - me -> col);
				if(nearest > (rowDis + colDis)){
					nearest = (rowDis + colDis);
					nearestFood.row = row;
					nearestFood.col = col;
				}
			}
			else if(field[row][col] == DEVIL)
			{
				rowDis = abs(row - me -> row);
				colDis = abs(col - me -> col);
				nearest = (rowDis + colDis);
				nearestFood.row = row;
				nearestFood.col = col;
				target = DEVIL;
			}
		}
	}
	return nearestFood;
}

//實作勇者AI 
Direction playerAI(int field[][GRID_SIDE], NodePointer player, NodePointer dragon){
//	printf("playerAI\n");
	Direction playerDirect = safeDirection(field,player,dragon);
		
	return playerDirect;
}

Direction safeDirection(int field[][GRID_SIDE], NodePointer player, NodePointer dragon){
//	printf("safeDirection\n");
	int i;
	int dirSize = 4;
	Location loc;
	
	loc = nextStepLoc(player, UP);
	if(!IsAtWall(field, loc.row, loc.col) && !IsCloseDragon(dragon, loc.row, loc.col))
		return UP;
	loc = nextStepLoc(player, DOWN);
	if(!IsAtWall(field, loc.row, loc.col) && !IsCloseDragon(dragon, loc.row, loc.col))
		return DOWN;
	loc = nextStepLoc(player, RIGHT);
	if(!IsAtWall(field, loc.row, loc.col) && !IsCloseDragon(dragon, loc.row, loc.col))
		return RIGHT;
	loc = nextStepLoc(player, LEFT);
	if(!IsAtWall(field, loc.row, loc.col) && !IsCloseDragon(dragon, loc.row, loc.col))
		return LEFT;						
	return player->direct;
}

Location nextStepLoc(NodePointer node, Direction direct){
//	printf("nextStepLoc\n");
	int currRow =  node -> row;
	int currCol = node -> col;
	int nextRow, nextCol;
	Location loc;
	switch(direct){
		case RIGHT:
			nextRow = currRow;
			nextCol = currCol + 1;
			break;	
		case LEFT:
			nextRow = currRow;
			nextCol = currCol - 1;
			break;
		case UP:
			nextRow = currRow - 1;
			nextCol = currCol;
			break;				
		case DOWN:
			nextRow = currRow + 1;
			nextCol = currCol;		
			break;	
	}
	loc.row = nextRow;
	loc.col = nextCol;
	return loc;
}


PathPointer heroFindPath(int field[][GRID_SIDE], Location startLoc, Location goalLoc, NodePointer dragon){
//	printf("heroFindPath\n");
	resetPathQueue();
	int steps = calcSteps(startLoc, goalLoc);
	PathNode start = {0, steps, startLoc, NULL, NULL};
	addPathQueue(start);//first pathNode
	while(!isPathQueueEmpty()){
		sortPathQueue();
		PathPointer current = popPathQueue();
		if(current->loc.row == goalLoc.row && current->loc.col == goalLoc.col)
			return buildPath(current);
		int dirSize = 4;
		int iDir[] = {1, 0, -1, 0};
		int jDir[] = {0, 1, 0, -1};
		int i,j;
		for(i=0, j=0; i<dirSize; i++, j++){
			Location neighborLoc = {current->loc.row + iDir[i], current->loc.col + jDir[j]};
			if(!visited(neighborLoc) && !IsAtWall(field, neighborLoc.row, neighborLoc.col)){
				int steps = calcSteps(neighborLoc, goalLoc);
				int cost = 	current->cost + 1;
				PathNode neighbor = {cost, steps, neighborLoc, current, NULL};
				if(!IsInPathQueue(neighbor)){
					addPathQueue(neighbor);
				
				}				
			}
		}
		
	}
	return NULL;
}

//判斷是否撞到惡龍自己的身體
bool IsCloseDragon(NodePointer dragon, int row, int col){
//	printf("IsCloseDragon\n");
	if(dragon == NULL)
		return NULL;
	NodePointer head = dragon;
	while(dragon != NULL){
		if (row == dragon->row && col == dragon->col)
			return true;
		dragon = dragon -> next;
	}
	int dirSize = 4;
	int iDir[] = {1, 0, -1, 0};
	int jDir[] = {0, 1, 0, -1};
	int i,j;
	for(i=0, j=0; i<dirSize; i++, j++){
		if (row == (head->row + iDir[i]) && (col == head->col  + jDir[j]))
			return true;
	}
	return false;
}
//遊戲結束訊息
int showGameOverMsg(){
   	//cleardevice(); //清理所有螢幕資料，如果希望只顯示訊息時，取消註解 
	int i = 0;
	char msg1[15] = "Game Over!!";
	char msg2[40] = "press [q] to quit or [s] to restart!!";
   	for(; ; i++){
	   	setcolor(i%14);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 7);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg1);
	   	
	   	setcolor(WHITE);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 2);
	   	outtextxy(20, SCREEN_HEIGHT / 2 + 70, msg2);
	   	
	   	delay(200);
	   	
	   	setcolor(BLACK);
	   	settextstyle(TRIPLEX_FONT, HORIZ_DIR , 7);
	   	outtextxy(0, SCREEN_HEIGHT / 2, msg1);	   
		   	
	   	if(kbhit()) {
	   		char key;
			key = getch();	
			if (key == 'q' || key == 'Q' || key == 's' || key == 'S') {
				return key; 				
			}
		}
	}	
}

//顯示遊戲相關資訊
void showInfo(){
	
	int timeNow = time(NULL);
	char timeMsg[45] = " Time:";
	char scoreMsg[45] = "Score:";
	char modeMsg[20] = "";
	char optMsg1[50] = "press [q] to quit, [s] to restart or";
	char optMsg2[50] = "press [a] to change mode.";
	
	char time[10];
	char score[10];
	
	sprintf(time, "%5d", timeNow - totalTime);
	strcat(timeMsg, time);
	strcat(timeMsg, " sec.");
	
	setcolor(WHITE); //設定文字顏色 
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1); //設定字型，水平或垂直和字型大小 
   	outtextxy(0, 0, timeMsg); //依據坐標輸出文字到螢幕	
	
	sprintf(score, "%5d", scoreSum);
	strcat(scoreMsg, score);
	strcat(scoreMsg, " point.");

	setcolor(WHITE);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(0, 19, scoreMsg);
   	
   	if(IFPlayAI){
   		strcat(modeMsg, "AI Mode    ");
	}else{
   		strcat(modeMsg, "Player Mode");
	}
			
   	setcolor(LIGHTMAGENTA);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(SCREEN_HEIGHT - LEFT_MARGINE * 2, 0, modeMsg);
   	
   	setcolor(LIGHTGREEN);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(0, TOP_MARGINE + (GRID_SIDE + 2) * SCREEN_HEIGHT / GRID_SIDE, optMsg1);
	outtextxy(0, TOP_MARGINE + (GRID_SIDE + 2) * SCREEN_HEIGHT / GRID_SIDE + 20, optMsg2);	      	
}

