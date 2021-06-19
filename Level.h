struct BUG
{
	char name[10];
	int blood;
	int x;
	int y;	
};

struct MARGIN
{
	int row;
	int col;	
};

struct LEVEL
{
	int treasure;
	int speed;
	int pass;
	int exit_X;
	int exit_Y;
};

struct TIME
{
	int start;
	int left;
	int now;
	int limit;
	int total;
};

extern struct BUG Bug;
extern struct MARGIN Margin;
extern struct TIME Time;
extern struct LEVEL Level;

void getName(char[]);
void pBlood(char);
void pSit();
int pTime();
void Bound();
void InfoBox();
void setLevel(int);
