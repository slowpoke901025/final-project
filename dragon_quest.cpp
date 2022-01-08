#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <math.h>

#define SCREEN_HEIGHT 500 //�]�w�C���������� 
#define SCREEN_WIDTH 500 //�]�w�C�������e��
#define GRID_SIDE 40 //�]�w�C����}�C���l�ƶq 
#define LEFT_MARGINE 30 //�]�w����� 
#define TOP_MARGINE 40 //�]�w�W��� 
#define FOOD_AMOUT 1 //�]�w�C�����ͭ����ƶq 
#define INIT_SPEED  800 //�]�w��l�c�s���ʳt�� 
#define MAX_QUEUE_SIZE 1600 //�]�w�W�C�j�p 
#define DRAGON_SPEED 1500
#define BULLET_SPEED 800
//�ŧi�e�i��V�C�|��� 
enum Direction {
	RIGHT, 
	LEFT, 
	UP, 
	DOWN,
};

//�ŧi�C�����X�{����C�|��� 
enum Object {
	EMPTY, //�ť� 
	WALL, //��λ�ê�� 
	FOOD, //����
	DEVIL 
};

enum Mode
{
	NORMAL,
	ANGRY,
	HUNGRY
};

//�ŧi�c�s����`�I���c 
struct Node {
	int row; //�`�I��b�ĴX�� 
	int col; //�`�I��b�ĴX�C 
	Direction direct; //�Ӹ`�I���e�i��V 
	struct Node *next;	//���V�U�@�Ӹ`�I 
	struct Node *pre;
}; 

//�w�q���V�`�I���c�������ܼ� 
typedef struct Node *NodePointer;

//�w�q�y�е��c 
struct Location {
	int row;
	int col;
};

typedef struct PathNode *PathPointer;

//�w�q���|�`�I���c�A�Ψӫإ߲��ʸ��| 
struct PathNode {
	int cost; //�Z�����I���B�� 
	int steps; //�Z���ؼЪ��B�� 
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
void openWindow(); //�}�Ҵ������� 
void closeGame(); //�B�z�C�������޿� 
int playGame(int field[][GRID_SIDE], NodePointer dragon, NodePointer player); //�C���i���޿� 
bool IsGameOver(NodePointer dragon, NodePointer player, int field[][GRID_SIDE]); //�c�s�O�_���`(���`����G����M����ۤv����) 
int showGameOverMsg(); //�C�������T��
void showInfo(); //��ܹC��������T 
void drawGameField(int field[][GRID_SIDE]); //ø�s�C���ϰ� 
void drawSquare(int row, int col, int color); //ø�s��� 
void drawCircle(int row, int col, int color);//
void controlDragonDirection(int field[][GRID_SIDE], NodePointer dragon, NodePointer player); //Ū��AI��J�A�ó]�w��Ҧ��c�s�`�I 
void controlPlayerDirection(int field[][GRID_SIDE], NodePointer player, NodePointer dragon); //Ū����L��V��J�A�Ϊ�AI��J
void controlBulletDirection(int field[][GRID_SIDE], NodePointer player, NodePointer dragon); 
void moveNext(NodePointer dragon, NodePointer player); //ø�s�c�s�C�e�i�@�B���������  
void createFood(int field[][GRID_SIDE],Object obj ,NodePointer dragon,NodePointer player); //���ͭ��� 
bool IsAtWall(int field[][GRID_SIDE], int row, int col); //�P�_�O�_������  
NodePointer IsAtDragon(NodePointer dragon, int row, int col); //�P�_�O�_����c�s�ۤv������
bool IsAtPlayer(NodePointer player, int row, int col);
bool IsAtObject(int field[][GRID_SIDE], int row, int col);
bool IsCloseDragon(NodePointer dragon, int row, int col);
void dragonEatFood(int field[][GRID_SIDE], NodePointer dragon,NodePointer player); //�B�z�c�s�Y�쭹���޿� 
void playerEatFood(int field[][GRID_SIDE], NodePointer player,NodePointer dragon); //�B�z���a�Y�쭹���޿� 
void addNode(NodePointer dragon); //�W�[�c�s����`�I
Location nextStepLoc(NodePointer node, Direction direct);
Location findNearestFood(int field[][GRID_SIDE], NodePointer dragon); //�M��̱��񭹪����y�� 
Direction safeDirection(int field[][GRID_SIDE], NodePointer player, NodePointer dragon);
Direction safeDirectionD(int field[][GRID_SIDE], NodePointer dragon);

PathPointer findPath(int field[][GRID_SIDE], Location startLoc, Location goalLoc); //�M����I�����i��F�����|
PathPointer heroFindPath(int field[][GRID_SIDE], Location startLoc, Location goalLoc, NodePointer dragon);
void addPathQueue(PathNode pathNode); //�N����n���X���`�I��J��C�� 
PathPointer popPathQueue(); //�Ǧ^�W�C���������A�ñN���q�W�C���R�� 
bool isPathQueueEmpty(); //�P�_�W�C�O�_���� 
void resetPathQueue(); //���]�W�C 
void sortPathQueue(); //��W�C���������i��Ƨ� 
bool IsInPathQueue(PathNode pathNode); //�P�_�Ӥ����O�_�b�W�C���� 
PathPointer buildPath(PathPointer goal); //�^�Ǩ�ؼЦ�m�����|��C 
int calcSteps(Location start, Location goal); //�p����I�����ݭn���ʪ��B�� 
bool visited(Location loc); //�P�_�O�_�Ӹ`�I�w�g���X�L 
Direction getDirectionByPath(NodePointer dragon); //�q���|��ƧP�_�U�@�B��V 

Direction dragonAI(int field[][GRID_SIDE], NodePointer dragon, NodePointer player); //�c�sAI 
Direction playerAI(int field[][GRID_SIDE], NodePointer player, NodePointer dragon); //�i��AI 

struct PathNode pathQueue[MAX_QUEUE_SIZE]; //�ŧi�N�n���X���`�I�W�C 
int front; //queue �Ĥ@�Ӥ������e�@�Ӧ�m 
int rear; //queue �̫�@�Ӥ�������m

int speed_D = DRAGON_SPEED, speed_B = BULLET_SPEED; //�C�����ʳt�� 
int scoreSum = 0; //�������� 
int totalTime = 0; //�����C���ɶ� 
int const scorePerFood = 1; //�C�@�������i�o���� 
bool meetSelfWillDie = false; //�M�w�c�s����ۤv����O�_�|���� 
bool IFPlayAI = false; //�O�_�}��AI�Ҧ� 
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
// �D�{��      
int main( ){  	
	openWindow();
	
	while(TRUE){
	
		Node headPlayer = {2, 4, RIGHT, NULL,NULL}; //�]�w�i�̪�l��m�M��V 
		Node headDragon = {15, 15, RIGHT, NULL,NULL}; //�]�w�s�Y��l��m�M��V 
		NodePointer dragon = &headDragon;
		NodePointer player = &headPlayer;
		
		//�]�w�C�����M��ê�� 
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
		playGame(field, dragon, player); //�i��C��
			    
	}
}

//�}�Ҵ�������
void openWindow(){
	initwindow(SCREEN_WIDTH*1.5 + LEFT_MARGINE * 3, SCREEN_HEIGHT + TOP_MARGINE * 3, "Hungry dragon Game");
	
}

//�B�z�C�������޿� 
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
//�C���i���޿�
int playGame(int field[][GRID_SIDE], NodePointer dragon, NodePointer player) {
	
	drawGameField(field); //ø�s�C���ϰ� 
	drawInfo();
	moveNext_Player(player);
	createFood(field, FOOD,dragon,player); //���ͲĤ@������ 
	
	while(1){
				
		controlPlayerDirection(field, player, dragon);//Ū�����a��J��V��A�ñN�s��V�]�w��U�c�s�`�I 
	
		playerEatFood(field, player,dragon); //�P�_���a�O�_���Y�쭹���A�p�G���W�[���� 
		
		
		if(--speed_B == 0)
		{
			controlBulletDirection(field, player, dragon);
			speed_B = BULLET_SPEED;
		}
		if(--speed_D == 0)
		{
			controlDragonDirection(field, dragon, player); 
			moveNext_Dragon(dragon);
			dragonEatFood(field, dragon,player); //�P�_�c�s�O�_���Y�쭹���A�p�G���s�W�`�I�����
			speed_D = DRAGON_SPEED;
		}
		
		randomFood(field, dragon,player);
		
		 
		showInfo(); //��ܮɶ��M���Ƹ�T 
		
		if(IsGameOver(dragon, player, field)) //�P�_�O�_�ŦX�C����������A 
			return showGameOverMsg(); //��ܹC�������T���A�õ��ݪ��a��J�ﶵ 
	 
		
	}
}

//ø�s�C���ϰ�A�̾ڹC�����x�}�]�wø�s���� 
void drawGameField(int field[][GRID_SIDE]){
   	int row = 0, col = 0;
   	cleardevice(); //�M�z�ù��e�� 
	for(row = 0; row < GRID_SIDE; row ++){
   		for(col = 0; col <  GRID_SIDE; col++){
				switch(field[row][col])	{
					case WALL: //��b�x�}�����ȬO1 
						drawSquare(row, col, YELLOW);
						break;
					case FOOD: //�����b�x�}�����ȬO2
						drawSquare(row, col, GREEN);
						break;	
				}	
		   }
	}
}


//ø�s���
void drawSquare(int row, int col, int color){
	
	int squareHeight = SCREEN_HEIGHT / GRID_SIDE;
   	int SquareWidth = SCREEN_WIDTH / GRID_SIDE;
	int left = 0, right = 0, bottom = 0, top = 0;
	left = LEFT_MARGINE + col * SquareWidth + col;
   	top =  TOP_MARGINE + row * squareHeight + row;
	right = left + SquareWidth;
   	bottom = top + squareHeight;
   	 
	setfillstyle(SOLID_FILL,color); //�]�wø�s���󪺬���ߩM�C�� 
   	bar(left , top, right, bottom);	//�]�wø�s�������m 
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

//ø�s�c�s�C�e�i�@�B��������� 
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
		
		//�̾ڸ`�I����V�ݩʡA�]�w���ʤU�@�B����m	
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

//�c�s�O�_���`(���`����G����M����ۤv����) 
bool IsGameOver(NodePointer dragon, NodePointer player, int field[][GRID_SIDE]){
	NodePointer head = dragon;
	
	if(!head)return true;
	//�P�_�O�_������ 
	if (IsAtWall(field, head->row, head->col))
		return true;
	if (IsAtWall(field, player->row, player->col))
		return true;
	
	
	//�P�_�O�_����c�s�ۤv 
	if(meetSelfWillDie)
		return IsAtDragon(dragon->next, head->row, head->col);
	
	//�ˬd�O�_AI�����s 
	if(player != NULL) {
		if(IsAtDragon(dragon, player->row, player->col))
			return true;
	}
	
	return false;
}

//�P�_�O�_������
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
//�P�_�O�_����c�s�ۤv������
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

		else if (key == 'a') //�M�w�O�_���ܼҦ� �A�D�n�����a�Ҧ��M�q���ޱ���AI�Ҧ� 
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

//Ū����L��V��J�A�ó]�w��Ҧ��c�s�`�I 
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


//Ū����L��V��J�A�ó]�w��Ҧ��c�s�`�I 
void controlDragonDirection(int field[][GRID_SIDE], NodePointer dragon, NodePointer player) {
		
	Direction dragonDirect = dragonAI(field, dragon, player);
	//���F�F�칳�s�@�˲��ʤ覡�A���s���ܤ�V�ɡA�ä��O��Ө���@�_���ܡA
	//�ӬO����ʦa�A�U�Ӹ`�I�v�@���ܡA��@�Ӹ`�I����s���e�i��V�ɡA
	//�|�N�ۤv�ثe����V�ǵ��U�@�ӡC 
	Direction temp;
	while(dragon != NULL){
		temp = dragon -> direct;
		dragon -> direct = dragonDirect;
		dragonDirect = temp;
		dragon = dragon -> next;
	}
}

//���ͭ���
void createFood(int field[][GRID_SIDE],Object obj, NodePointer dragon,NodePointer player){
	int row, col, i, foodAmount = FOOD_AMOUT;
	srand((unsigned)time(NULL)); //���ثe�t�ήɶ��@���üƺؤl 

	for(i=0; i< foodAmount; i++){
		//�p�G�üƲ��ͪ���m�O�b��M�s���魫�|�A�h���s���͡A����ŦX���󬰤� 
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

//�B�z�c�s�Y�쭹���޿�
void dragonEatFood(int field[][GRID_SIDE], NodePointer dragon,NodePointer player){
	//�p�G�s�Y�P������m���|�A�N�O�Y�쭹�� 
	if(field[dragon->row][dragon->col] == FOOD){
		field[dragon->row][dragon->col] = EMPTY; //�N�ӭ����M�� 
		printf("The dragon has eaten food at row: %d, col: %d\n", dragon->row, dragon->col);
		addNode(dragon); //�W�[�`�I  
		createFood(field, FOOD,dragon,player); //���ͷs������ 
	}
	else if(field[dragon->row][dragon->col] == DEVIL)
	{
		modeD = ANGRY;
		colorD = LIGHTRED;
	} 
}

//�B�z���a�Y�쭹���޿�
void playerEatFood(int field[][GRID_SIDE], NodePointer player, NodePointer dragon){
	//�p�G�s�Y�P������m���|�A�N�O�Y�쭹�� 
	if(field[player->row][player->col] >= FOOD){
		field[player->row][player->col] = EMPTY; //�N�ӭ����M�� 
		printf("The player has eaten food at row: %d, col: %d\n", player->row, player->col);
		scoreSum = scoreSum + scorePerFood; //�������� 
		createFood(field,FOOD,player,dragon); //���ͷs������
		
		if(!isFilled())
		{
			drawBullet();
		}
		 
	}
}

//�W�[�c�s����`�I
void addNode(NodePointer dragon){
	NodePointer tail = NULL;
	NodePointer newNode = (NodePointer) malloc(sizeof(Node)); //��l�Ƥ@�ӷs�`�I 
	//�M���s������ 
	while(dragon != NULL){
		tail = dragon;
		dragon = dragon -> next;
	}
	//�N�s���ڪ���V�ݩʵ��s�`�I 
	newNode -> direct = tail -> direct;
	
	//�M�w�s�`�I����m�A�̾ڧ��ڪ����ʤ�V�ӱ��W�s�`�I 
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
	
	tail -> next = newNode; //�N���ڸ`�I�s����s�`�I
	newNode->pre = tail; 
	newNode -> next = NULL;		
}

//�s��AI���� 
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

//�q���|��ƧP�_�U�@�B��V 
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

//�M����I�����i��F�����|
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

//�N����n���X���`�I��J��C��
void addPathQueue(PathNode pathNode){
//	printf("addPathQueue\n");
	if(rear == MAX_QUEUE_SIZE - 1){
		printf("the queue is full");
		return;
	}
	rear += 1;
	pathQueue[rear]	= pathNode;
}

//�Ǧ^�W�C���������A�ñN���q�W�C���R��
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

//�P�_�W�C�O�_����
bool isPathQueueEmpty(){
//	printf("isPathQueueEmpty\n");
	return front == rear;
}

//���]�W�C 
void resetPathQueue(){
//	printf("resetPathQueue\n");
	front = -1;
	rear = -1;	
}

//��W�C���������i��Ƨ� 
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

//�P�_�Ӥ����O�_�b�W�C����
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

//�^�Ǩ�ؼЦ�m�����|��C 
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

//�p����I�����ݭn���ʪ��B�� 
int calcSteps(Location start, Location goal){
	//printf("calcSteps\n");
	int steps = abs(start.row - goal.row) + abs(start.col - goal.col);
	return steps;
}

//�P�_�O�_�Ӹ`�I�w�g���X�L 
bool visited(Location loc){
	//printf("visited\n");
	int i;
	for(i=0;i<=front;i++){
		if(pathQueue[i].loc.row == loc.row && pathQueue[i].loc.col == loc.col)
			return true;
	}
	return false;
}

//�M��̱��񭹪����y�� 
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

//��@�i��AI 
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

//�P�_�O�_����c�s�ۤv������
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
//�C�������T��
int showGameOverMsg(){
   	//cleardevice(); //�M�z�Ҧ��ù���ơA�p�G�Ʊ�u��ܰT���ɡA�������� 
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

//��ܹC��������T
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
	
	setcolor(WHITE); //�]�w��r�C�� 
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1); //�]�w�r���A�����Ϋ����M�r���j�p 
   	outtextxy(0, 0, timeMsg); //�̾ڧ��п�X��r��ù�	
	
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

