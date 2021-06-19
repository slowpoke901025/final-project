#include "Creature.h"
/**************************slowpoke************************************/

void fur(int x,int y,int Map[][100])//5x7
{
	Map[y][x]=1;
	Map[y][x+1]=1;
	Map[y][x+5]=1;
	Map[y][x+6]=1;
	Map[y-1][x+1]=1;
	Map[y-1][x+5]=1;
	Map[y-2][x+1]=1;
	Map[y-2][x+3]=1;
	Map[y-2][x+5]=1;
	Map[y-3][x+2]=1;
	Map[y-3][x+4]=1;
	Map[y-4][x+3]=1;
}
void furU(int x,int y,int Map[][100])//5x7
{
	Map[y][x]=1;
	Map[y][x+1]=1;
	Map[y][x+5]=1;
	Map[y][x+6]=1;
	Map[y+1][x+1]=1;
	Map[y+1][x+5]=1;
	Map[y+2][x+1]=1;
	Map[y+2][x+3]=1;
	Map[y+2][x+5]=1;
	Map[y+3][x+2]=1;
	Map[y+3][x+4]=1;
	Map[y+4][x+3]=1;
}
void furL(int x,int y,int Map[][100])//5x7
{
	Map[y][x]=1;
	Map[y+1][x]=1;
	Map[y+1][x+1]=1;
	Map[y+1][x+2]=1;
	Map[y+2][x+3]=1;
	Map[y+3][x+2]=1;
	Map[y+3][x+4]=1;
	Map[y+4][x+3]=1;
	Map[y+5][x]=1;
	Map[y+5][x+1]=1;
	Map[y+5][x+2]=1;
	Map[y+6][x]=1;
}
void furR(int x,int y,int Map[][100])//5x7
{
	Map[y][x]=1;
	Map[y+1][x]=1;
	Map[y+1][x-1]=1;
	Map[y+1][x-2]=1;
	Map[y+2][x-3]=1;
	Map[y+3][x-2]=1;
	Map[y+3][x-4]=1;
	Map[y+4][x-3]=1;
	Map[y+5][x]=1;
	Map[y+5][x-1]=1;
	Map[y+5][x-2]=1;
	Map[y+6][x]=1;
}
void germ(int x,int y,int Map[][100])
{
	Map[y][x]=1;
	Map[y][x+1]=1;
	Map[y][x+6]=1;
	Map[y][x+7]=1;
	Map[y-1][x]=1;
	Map[y-1][x+2]=1;	
	Map[y-1][x+5]=1;
	Map[y-1][x+7]=1;
	Map[y-2][x+2]=1;
	Map[y-2][x+5]=1;
	Map[y-3][x+1]=1;
	Map[y-3][x+6]=1;
	Map[y-4][x+1]=1;
	Map[y-4][x+2]=1;
	Map[y-4][x+5]=1;
	Map[y-4][x+6]=1;
	Map[y-5][x+3]=1;
	Map[y-5][x+4]=1;
}
void germU(int x,int y,int Map[][100])
{
	Map[y][x]=1;
	Map[y][x+1]=1;
	Map[y][x+6]=1;
	Map[y][x+7]=1;
	Map[y+1][x]=1;
	Map[y+1][x+2]=1;	
	Map[y+1][x+5]=1;
	Map[y+1][x+7]=1;
	Map[y+2][x+2]=1;
	Map[y+2][x+5]=1;
	Map[y+3][x+1]=1;
	Map[y+3][x+6]=1;
	Map[y+4][x+1]=1;
	Map[y+4][x+2]=1;
	Map[y+4][x+5]=1;
	Map[y+4][x+6]=1;
	Map[y+5][x+3]=1;
	Map[y+5][x+4]=1;
}

void octapole(int x,int y,int Map[][100])
{
	Map[y][x]=1;
	Map[y][x+1]=1;
	Map[y-1][x]=1;
	Map[y-1][x+2]=1;
	Map[y-3][x+2]=1;
	Map[y-3][x+4]=1;
	Map[y-5][x+4]=1;
	Map[y-5][x+6]=1;
	Map[y-6][x+7]=1;
	Map[y-7][x+6]=1;
	Map[y-7][x+7]=1;
}
void octapoleR(int x,int y,int Map[][100])
{
	Map[y][x]=1;
	Map[y][x+1]=1;
	Map[y+1][x]=1;
	Map[y+1][x+2]=1;
	Map[y+3][x+2]=1;
	Map[y+3][x+4]=1;
	Map[y+5][x+4]=1;
	Map[y+5][x+6]=1;
	Map[y+6][x+7]=1;
	Map[y+7][x+6]=1;
	Map[y+7][x+7]=1;	
}
void circle(int x,int y,int Map[][100])
{
	Map[y][x]=1;    Map[y][x+16]=1;
	Map[y+1][x]=1;	Map[y+1][x+15]=1;
	Map[y+1][x+1]=1;Map[y+1][x+16]=1;
	Map[y+2][x]=1;	Map[y+2][x+15]=1;
	Map[y+2][x+1]=1;Map[y+2][x+16]=1;
	Map[y+3][x+1]=1;Map[y+3][x+15]=1;
	Map[y+8][x+3]=1;Map[y+8][x+12]=1;
	Map[y+8][x+4]=1;Map[y+8][x+13]=1;
	Map[y+9][x-9]=1;Map[y+9][x+23]=1;
	Map[y+9][x-8]=1;Map[y+9][x+24]=1;
	Map[y+9][x-7]=1;Map[y+9][x+25]=1;
	Map[y+9][x+4]=1;Map[y+9][x+11]=1;
	Map[y+9][x+5]=1;Map[y+9][x+12]=1;
	Map[y+10][x-8]=1;Map[y+10][x+22]=1;
	Map[y+10][x-7]=1;Map[y+10][x+23]=1;
	Map[y+10][x-6]=1;Map[y+10][x+24]=1;
	Map[y+10][x+5]=1;Map[y+10][x+10]=1;
	Map[y+10][x+6]=1;Map[y+10][x+11]=1;
	Map[y+12][x-1]=1;Map[y+12][x+17]=1;
	Map[y+13][x-1]=1;Map[y+13][x+16]=1;
	Map[y+13][x]=1;	 Map[y+13][x+17]=1;
	Map[y+14][x]=1;	 Map[y+14][x+15]=1;
	Map[y+14][x+1]=1;Map[y+14][x+16]=1;				
	Map[y+15][x+1]=1;Map[y+15][x+15]=1;
	Map[y+19][x+1]=1;Map[y+19][x+15]=1;
	Map[y+20][x]=1;	 Map[y+20][x+15]=1;
	Map[y+20][x+1]=1;Map[y+20][x+16]=1;	
	Map[y+21][x-1]=1;Map[y+21][x+16]=1;
	Map[y+21][x]=1;	 Map[y+21][x+17]=1;
	Map[y+22][x-1]=1;Map[y+22][x+17]=1;
	Map[y+24][x-8]=1;Map[y+24][x+22]=1;
	Map[y+24][x-7]=1;Map[y+24][x+23]=1;
	Map[y+24][x-6]=1;Map[y+24][x+24]=1;
	Map[y+24][x+5]=1;Map[y+24][x+10]=1;
	Map[y+24][x+6]=1;Map[y+24][x+11]=1;
	Map[y+25][x-9]=1;Map[y+25][x+23]=1;
	Map[y+25][x-8]=1;Map[y+25][x+24]=1;
	Map[y+25][x-7]=1;Map[y+25][x+25]=1;
	Map[y+25][x+4]=1;Map[y+25][x+11]=1;
	Map[y+25][x+5]=1;Map[y+25][x+12]=1;
	Map[y+26][x+3]=1;Map[y+26][x+12]=1;
	Map[y+26][x+4]=1;Map[y+26][x+13]=1;
	Map[y+31][x+1]=1;Map[y+31][x+15]=1;
	Map[y+32][x]=1;	 Map[y+32][x+15]=1;
	Map[y+32][x+1]=1;Map[y+32][x+16]=1;
	Map[y+33][x]=1;	 Map[y+33][x+15]=1;
	Map[y+33][x+1]=1;Map[y+33][x+16]=1;
	Map[y+34][x]=1;  Map[y+34][x+16]=1;                  	
}
void triangle(int x, int y,int Map[][100])
{
	Map[y][x]=1;
	Map[y][x+2]=1;
	Map[y-1][x+1]=1;
	Map[y+1][x+1]=1;
	Map[y-2][x+4]=1;
	Map[y-2][x+6]=1;
	Map[y-3][x+5]=1;
	Map[y-1][x+5]=1;
	Map[y+2][x+4]=1;
	Map[y+2][x+6]=1;
	Map[y+1][x+5]=1;
	Map[y+3][x+5]=1; 
	Map[y+4][x+8]=1;
	Map[y+4][x+10]=1;
	Map[y+3][x+9]=1;
	Map[y+5][x+9]=1;
	Map[y][x+8]=1;
	Map[y][x+10]=1;
	Map[y-1][x+9]=1;
	Map[y+1][x+9]=1;
	Map[y-4][x+8]=1;
	Map[y-4][x+10]=1;
	Map[y-5][x+9]=1;
	Map[y-3][x+9]=1;
}
void triangleR(int x, int y,int Map[][100])
{
	Map[y][x]=1;
	Map[y][x-2]=1;
	Map[y-1][x-1]=1;
	Map[y+1][x-1]=1;
	Map[y-2][x-4]=1;
	Map[y-2][x-6]=1;
	Map[y-3][x-5]=1;
	Map[y-1][x-5]=1;
	Map[y+2][x-4]=1;
	Map[y+2][x-6]=1;
	Map[y+1][x-5]=1;
	Map[y+3][x-5]=1;
	Map[y+4][x-8]=1;
	Map[y+4][x-10]=1;
	Map[y+3][x-9]=1;
	Map[y+5][x-9]=1;
	Map[y][x-8]=1;
	Map[y][x-10]=1;
	Map[y-1][x-9]=1;
	Map[y+1][x-9]=1;
	Map[y-4][x-8]=1;
	Map[y-4][x-10]=1;
	Map[y-5][x-9]=1;
	Map[y-3][x-9]=1;
}

/**************************ROY************************************/
//ª½½u
void line1(int x, int y, int map[][100]){
    map[y][x] = 1;
    map[y+1][x] = 1;
    map[y+2][x] = 1;
}

//¾î½u
void line2(int x, int y, int map[][100]){
    map[y][x] = 1;
    map[y][x+1] = 1;
    map[y][x+2] = 1;

}

//15¶g´Áªá
void flower(int x, int y, int map[][100]){
    map[y][x] = 1;
    map[y+1][x] = 1;
    map[y
+2][x] = 1;
    map[y+3][x] = 1;
    map[y+4][x] = 1;
    map[y+5][x] = 1;
    map[y+6][x] = 1;
    map[y+7][x] = 1;

    map[y][x+1] = 1;
     map[y+2][x+1] = 1;
    map[y+2][x+2] = 1;
    map[y+3][x+1] = 1;
    map[y+4][x+1] = 1;
    map[y+5][x+1] = 1;
    map[y+7][x+1] = 1;

    map[y][x+2] = 1;
    map[y+1][x+2] = 1;
    map[y+2][x+2] = 1;
    map[y+3][x+2] = 1;
    map[y+4][x+2] = 1;
    map[y+5][x+2] = 1;
    map[y+6][x+2] = 1;
    map[y+7][x+2] = 1;
}

//¤p©Z§J
void tank(int x, int y, int map[][100]){
    map[y][x] = 1;
    map[y+1][x] = 1;
    map[y+9][x] = 1;
    map[y+10][x] = 1;

    map[y][x+1] = 1;
    map[y+2][x+1] = 1;
    map[y+5][x+1] = 1;
    map[y+8][x+1] = 1;
    map[y+10][x+1] = 1;

    map[y+2][x+2] = 1;
    map[y+5][x+2] = 1;
    map[y+6][x+2] = 1;
    map[y+7][x+2] = 1;
    map[y+8][x+2] = 1;

    map[y][x+3] = 1;
    map[y+2][x+3] = 1;
    map[y+5][x+3] = 1;
    map[y+8][x+3] = 1;
    map[y+10][x+3] = 1;

    map[y][x+4] = 1;
    map[y+1][x+4] = 1;
    map[y+9][x+4] = 1;
    map[y+10][x+4] = 1;
}

//­ËµÛªº©Z§J

void reverse_tank(int x, int y, int map[][100]){
map[y][x] = 1;
map[y+1][x] = 1;
map[y+9][x] = 1;
map[y+10][x] = 1;

map[y][x+1] = 1;
map[y+2][x+1] = 1;
map[y+5][x+1] = 1;
map[y+8][x+1] = 1;
map[y+10][x+1] = 1;

map[y+2][x+2] = 1;
map[y+3][x+2] = 1;
map[y+4][x+2] = 1;
map[y+5][x+2] = 1;
map[y+8][x+2] = 1;

map[y][x+3] = 1;
map[y+2][x+3] = 1;
map[y+5][x+3] = 1;
map[y+8][x+3] = 1;
map[y+10][x+3] = 1;

map[y][x+4] = 1;
map[y+1][x+4] = 1;
map[y+9][x+4] = 1;
map[y+10][x+4] = 1;
}


//µu½bÀY 
void sa(int x, int y, int map[][100]){
    map[y][x] = 1;
    map[y][x+1] = 1;

    map[y-1][x] = 1;
    map[y-1][x+2] = 1;

    map[y-2][x+1] = 1;
    map[y-2][x+2] = 1;
}

/**************************Tu************************************/
//µu½bÀY¤Ï 
void saR(int x, int y, int map[][100]) {
    map[y][x] = 1;
    map[y][x + 1] = 1;

    map[y +1][x] = 1;
    map[y +1][x + 2] = 1;

    map[y +2][x + 1] = 1;
    map[y + 2][x + 2] = 1;
}

//­¸Ãð 
void d(int x, int y, int map[][100]){
    map[y][x] = 1;
    map[y][x+1] = 1;
    map[y][x+12] = 1;
    map[y][x+14] = 1;

    map[y+1][x+14] = 1;
    map[y+1][x+15] = 1;

    map[y+2][x+14] = 1;
    map[y+2][x+15] = 1;

    map[y-1][x] = 1;
    map[y-1][x+1] = 1;
    map[y-1][x+2] = 1;
    map[y-1][x+3] = 1;
    map[y-1][x+4] = 1;
    map[y-1][x+5] = 1;
    map[y-1][x+14] = 1;

    map[y-2][x+5] = 1;
    map[y-2][x+6] = 1;
    map[y-2][x+14] = 1;

    map[y-3][x+2] = 1;
    map[y-3][x+5] = 1;
    map[y-3][x+8] = 1;
    map[y-3][x+9] = 1;
    map[y-3][x+10] = 1;
    map[y-3][x+11] = 1;
    map[y-3][x+12] = 1;
    map[y-3][x+13] = 1;
    map[y-3][x+14] = 1;

    map[y-4][x+5] = 1;
    map[y-4][x+9] = 1;
    map[y-4][x+10] = 1;
    map[y-4][x+13] = 1;

    map[y-5][x+5] = 1;
    map[y-5][x+6] = 1;

    map[y-6][x+5] = 1;
    map[y-6][x+6] = 1;
    map[y-6][x+12] = 1;

    map[y-7][x+5] = 1;
    map[y-7][x+11] = 1;
    map[y-7][x+12] = 1;

    map[y-8][x+11] = 1;
    map[y-8][x+12] = 1;

    map[y-9][x+4] = 1;
    map[y-9][x+7] = 1;
    map[y-9][x+8] = 1;
    map[y-9][x+12] = 1;

    map[y-10][x+3] = 1;
    map[y-10][x+4] = 1;
    map[y-10][x+5] = 1;
    map[y-10][x+6] = 1;
    map[y-10][x+7] = 1;
    map[y-10][x+8] = 1;
    map[y-10][x+9] = 1;
    map[y-10][x+12] = 1;
    map[y-10][x+15] = 1;

    map[y-11][x+3] = 1;
    map[y-11][x+11] = 1;
    map[y-11][x+12] = 1;

    map[y-12][x+3] = 1;
    map[y-12][x+12] = 1;
    map[y-12][x+13] = 1;
    map[y-12][x+14] = 1;
    map[y-12][x+15] = 1;
    map[y-12][x+16] = 1;
    map[y-12][x+17] = 1;

    map[y-13][x+3] = 1;
    map[y-13][x+5] = 1;
    map[y-13][x+16] = 1;
    map[y-13][x+17] = 1;

    map[y-14][x+2] = 1;
    map[y-14][x+3] = 1;

    map[y-15][x+2] = 1;
    map[y-15][x+3] = 1;
}

//­¸Ãð¤Ï
void dR(int x, int y, int map[][100]) {
    map[y][x] = 1;
    map[y][x + 1] = 1;
    map[y][x + 12] = 1;
    map[y][x + 14] = 1;

    map[y - 1][x + 14] = 1;
    map[y - 1][x + 15] = 1;

    map[y - 2][x + 14] = 1;
    map[y - 2][x + 15] = 1;

    map[y + 1][x] = 1;
    map[y + 1][x + 1] = 1;
    map[y + 1][x + 2] = 1;
    map[y + 1][x + 3] = 1;
    map[y + 1][x + 4] = 1;
    map[y + 1][x + 5] = 1;
    map[y + 1][x + 14] = 1;

    map[y + 2][x + 5] = 1;
    map[y+ 2][x + 6] = 1;
    map[y + 2][x + 14] = 1;

    map[y +3][x + 2] = 1;
    map[y + 3][x + 5] = 1;
    map[y + 3][x + 8] = 1;
    map[y + 3][x + 9] = 1;
    map[y + 3][x + 10] = 1;
    map[y + 3][x + 11] = 1;
    map[y + 3][x + 12] = 1;
    map[y +3][x + 13] = 1;
    map[y + 3][x + 14] = 1;

    map[y + 4][x + 5] = 1;
    map[y + 4][x + 9] = 1;
    map[y + 4][x + 10] = 1;
    map[y + 4][x + 13] = 1;

    map[y + 5][x + 5] = 1;
    map[y + 5][x + 6] = 1;

    map[y + 6][x + 5] = 1;
    map[y + 6][x + 6] = 1;
    map[y + 6][x + 12] = 1;

    map[y +7][x + 5] = 1;
    map[y + 7][x + 11] = 1;
    map[y + 7][x + 12] = 1;

    map[y +8][x + 11] = 1;
    map[y+ 8][x + 12] = 1;

    map[y + 9][x + 4] = 1;
    map[y +9][x + 7] = 1;
    map[y +9][x + 8] = 1;
    map[y + 9][x + 12] = 1;

    map[y +10][x + 3] = 1;
    map[y + 10][x + 4] = 1;
    map[y + 10][x + 5] = 1;
    map[y + 10][x + 6] = 1;
    map[y + 10][x + 7] = 1;
    map[y + 10][x + 8] = 1;
    map[y + 10][x + 9] = 1;
    map[y + 10][x + 12] = 1;
    map[y + 10][x + 15] = 1;

    map[y + 11][x + 3] = 1;
    map[y + 11][x + 11] = 1;
    map[y + 11][x + 12] = 1;

    map[y + 12][x + 3] = 1;
    map[y + 12][x + 12] = 1;
    map[y + 12][x + 13] = 1;
    map[y + 12][x + 14] = 1;
    map[y + 12][x + 15] = 1;
    map[y + 12][x + 16] = 1;
    map[y + 12][x + 17] = 1;

    map[y + 13][x + 3] = 1;
    map[y + 13][x + 5] = 1;
    map[y + 13][x + 16] = 1;
    map[y + 13][x + 17] = 1;

    map[y + 14][x + 2] = 1;
    map[y + 14][x + 3] = 1;

    map[y + 15][x + 2] = 1;
    map[y + 15][x + 3] = 1;
}

//ªÅ¤ß¤Q¦r
void sc(int x, int y, int map[][100]){
    map[y][x] = 1;

    map[y-1][x-1] = 1;
    map[y-1][x+1] = 1;

    map[y-2][x] = 1;
}

//¤j¤Q¦r 
void bc(int x, int y, int map[][100]){
    map[y][x] = 1;

    map[y-1][x] = 1;

    map[y-2][x-1] = 1;
    map[y-2][x-2] = 1;
    map[y-2][x+1] = 1;
    map[y-2][x+2] = 1;

    map[y-4][x-2] = 1;
    map[y-4][x-4] = 1;
    map[y-4][x+2] = 1;
    map[y-4][x+4] = 1;

    map[y-5][x-4] = 1;
    map[y-5][x+4] = 1;

    map[y-6][x-5] = 1;
    map[y-6][x-6] = 1;
    map[y-6][x+5] = 1;
    map[y-6][x+6] = 1;

    map[y-7][x-4] = 1;
    map[y-7][x+4] = 1;

    map[y-8][x-2] = 1;
    map[y-8][x-4] = 1;
    map[y-8][x+2] = 1;
    map[y-8][x+4] = 1;

    map[y-10][x-1] = 1;
    map[y-10][x-2] = 1;
    map[y-10][x+1] = 1;
    map[y-10][x+2] = 1;

    map[y-11][x] = 1;

    map[y-12][x] = 1;
}

//¥ÛÀY
void st(int x, int y, int map[][100]){
    map[y][x] = 1;
    map[y][x+1] = 1;  

    map[y-1][x-1] = 1;
    map[y-1][x+2] = 1;

    map[y-2][x] = 1;
    map[y-2][x+1] = 1;
}

//¤è¶ô 
void sq(int x, int y, int map[][100]){
    map[y][x] = 1;
    map[y][x+1] = 1;

    map[y-1][x] = 1;
    map[y-1][x+1] = 1;
}



//´U¤l
void hat(int x, int y, int map[][100]){
    map[y][x] = 1;
    map[y][x+1] = 1;
    map[y][x+3] = 1;
    map[y][x+4] = 1;

    map[y-1][x+1] = 1;
    map[y-1][x+3] = 1;

    map[y-2][x+1] = 1;
    map[y-2][x+3] = 1;

    map[y-3][x+2] = 1;
    
    map[y+2][x] = 1;
    map[y+2][x + 1] = 1;
    map[y+2][x + 3] = 1;
    map[y+2][x + 4] = 1;

    map[y +3][x + 1] = 1;
    map[y + 3][x + 3] = 1;

    map[y + 4][x + 1] = 1;
    map[y + 4][x + 3] = 1;

    map[y +5][x + 2] = 1;
}
//¤Ï´U¤l 
void hr(int x, int y, int map[][100]) {
    map[y][x] = 1;
    map[y][x + 1] = 1;
    map[y][x + 3] = 1;
    map[y][x + 4] = 1;

    map[y +1][x + 1] = 1;
    map[y + 1][x + 3] = 1;

    map[y + 2][x + 1] = 1;
    map[y + 2][x + 3] = 1;

    map[y +3][x + 2] = 1;
}
//¤j¤è¶ô 
void bsq(int x, int y, int map[][100]){
    map[y][x] = 1;
    map[y][x+1] = 1;
    map[y][x+3] = 1;
    map[y][x+4] = 1;

    map[y-1][x-1] = 1;
    map[y-1][x+1] = 1;
    map[y-1][x+2] = 1;
    map[y-1][x+5] = 1;

    map[y-2][x] = 1;
    map[y-2][x-1] = 1;
    map[y-2][x+5] = 1;

    map[y-3][x] = 1;
    map[y-3][x+4] = 1;

    map[y-4][x-1] = 1;
    map[y-4][x+4] = 1;
    map[y-4][x+5] = 1;

    map[y-5][x-1] = 1;
    map[y-5][x+2] = 1;
    map[y-5][x+3] = 1;
    map[y-5][x+5] = 1;

    map[y-6][x] = 1;
    map[y-6][x+1] = 1;
    map[y-6][x+3] = 1;
    map[y-6][x+4] = 1;
}

//¶Ã¶] 
void run(int x, int y, int map[][100]){
    map[y][x] = 1;
    map[y][x+1] = 1;
    map[y][x+26] = 1;
    map[y][x+27] = 1;

    map[y-1][x] = 1;
    map[y-1][x+1] = 1;
    map[y-1][x+26] = 1;
    map[y-1][x+27] = 1;

    map[y-2][x+8] = 1;
    map[y-2][x+9] = 1;

    map[y-3][x+7] = 1;
    map[y-3][x+10] = 1;

    map[y-4][x+8] = 1;
    map[y-4][x+9] = 1;

    map[y-5][x+12] = 1;
    map[y-5][x+13] = 1;
    map[y-5][x+14] = 1;

    map[y-6][x+11] = 1;
    map[y-6][x+15] = 1;

    map[y-7][x+11] = 1;
    map[y-7][x+15] = 1;

    map[y-8][x+12] = 1;
    map[y-8][x+13] = 1;
    map[y-8][x+14] = 1;

    map[y-10][x+13] = 1;
    map[y-10][x+14] = 1;
    map[y-10][x+15] = 1;

    map[y-11][x+12] = 1;
    map[y-11][x+16] = 1;

    map[y-12][x+12] = 1;
    map[y-12][x+16] = 1;

    map[y-13][x+13] = 1;
    map[y-13][x+14] = 1;
    map[y-13][x+15] = 1;

    map[y-14][x+18] = 1;
    map[y-14][x+19] = 1;

    map[y-15][x+17] = 1;
    map[y-15][x+20] = 1;

    map[y-16][x+18] = 1;
    map[y-16][x+19] = 1;

    map[y-17][x] = 1;
    map[y-17][x+1] = 1;
    map[y-17][x+26] = 1;
    map[y-17][x+27] = 1;

    map[y-18][x] = 1;
    map[y-18][x+1] = 1;
    map[y-18][x+26] = 1;
    map[y-18][x+27] = 1;
}

//´cÅ]¤j¼M¼M 
void df(int x, int y, int map[][100]){
    map[y][x] = 1;
    map[y][x+2] = 1;
    map[y][x+5] = 1;
    map[y][x+15] = 1;
    map[y][x+18] = 1;
    map[y][x+20] = 1;

    map[y-1][x-1] = 1;
    map[y-1][x+2] = 1;
    map[y-1][x+4] = 1;
    map[y-1][x+5] = 1;
    map[y-1][x+15] = 1;
    map[y-1][x+16] = 1;
    map[y-1][x+18] = 1;
    map[y-1][x+21] = 1;

    map[y-2][x+6] = 1;
    map[y-2][x+7] = 1;
    map[y-2][x+9] = 1;
    map[y-2][x+11] = 1;
    map[y-2][x+13] = 1;
    map[y-2][x+14] = 1;

    map[y-3][x-1] = 1;
    map[y-3][x] = 1;
    map[y-3][x+4] = 1;
    map[y-3][x+5] = 1;
    map[y-3][x+6] = 1;
    map[y-3][x+7] = 1;
    map[y-3][x+9] = 1;
    map[y-3][x+11] = 1;
    map[y-3][x+13] = 1;
    map[y-3][x+14] = 1;
    map[y-3][x+15] = 1;
    map[y-3][x+16] = 1;
    map[y-3][x+20] = 1;
    map[y-3][x+21] = 1;

    map[y-4][x+6] = 1;
    map[y-4][x+7] = 1;
    map[y-4][x+9] = 1;
    map[y-4][x+11] = 1;
    map[y-4][x+13] = 1;
    map[y-4][x+14] = 1;

    map[y-5][x] = 1;
    map[y-5][x+2] = 1;
    map[y-5][x+9] = 1;
    map[y-5][x+11] = 1;
    map[y-5][x+18] = 1;
    map[y-5][x+20] = 1;

    map[y-6][x-1] = 1;
    map[y-6][x] = 1;
    map[y-6][x+2] = 1;
    map[y-6][x+9] = 1;
    map[y-6][x+11] = 1;
    map[y-6][x+18] = 1;
    map[y-6][x+20] = 1;
    map[y-6][x+21] = 1;

    map[y-7][x+1] = 1;
    map[y-7][x+2] = 1;
    map[y-7][x+3] = 1;
    map[y-7][x+7] = 1;
    map[y-7][x+9] = 1;
    map[y-7][x+11] = 1;
    map[y-7][x+13] = 1;
    map[y-7][x+17] = 1;
    map[y-7][x+18] = 1;
    map[y-7][x+19] = 1;

    map[y-8][x+1] = 1;
    map[y-8][x+2] = 1;
    map[y-8][x+3] = 1;
    map[y-8][x+6] = 1;
    map[y-8][x+8] = 1;
    map[y-8][x+12] = 1;
    map[y-8][x+14] = 1;
    map[y-8][x+17] = 1;
    map[y-8][x+18] = 1;
    map[y-8][x+19] = 1;
    
    map[y-9][x+7] = 1;
    map[y-9][x+13] = 1;

    map[y-10][x+1] = 1;
    map[y-10][x+2] = 1;
    map[y-10][x+3] = 1;
    map[y-10][x+4] = 1;
    map[y-10][x+5] = 1;
    map[y-10][x+6] = 1;
    map[y-10][x+14] = 1;
    map[y-10][x+15] = 1;
    map[y-10][x+16] = 1;
    map[y-10][x+17] = 1;
    map[y-10][x+18] = 1;
    map[y-10][x+19] = 1;

    map[y-12][x+1] = 1;
    map[y-12][x+2] = 1;
    map[y-12][x+3] = 1;
    map[y-12][x+4] = 1;
    map[y-12][x+5] = 1;
    map[y-12][x+6] = 1;
    map[y-12][x+14] = 1;
    map[y-12][x+15] = 1;
    map[y-12][x+16] = 1;
    map[y-12][x+17] = 1;
    map[y-12][x+18] = 1;
    map[y-12][x+19] = 1;

    map[y-13][x+7] = 1;
    map[y-13][x+13] = 1;

    map[y-14][x+1] = 1;
    map[y-14][x+2] = 1;
    map[y-14][x+3] = 1;
    map[y-14][x+6] = 1;
    map[y-14][x+8] = 1;
    map[y-14][x+12] = 1;
    map[y-14][x+14] = 1;
    map[y-14][x+17] = 1;
    map[y-14][x+18] = 1;
    map[y-14][x+19] = 1;

    map[y-15][x+1] = 1;
    map[y-15][x+2] = 1;
    map[y-15][x+3] = 1;
    map[y-15][x+7] = 1;
    map[y-15][x+9] = 1;
    map[y-15][x+11] = 1;
    map[y-15][x+13] = 1;
    map[y-15][x+17] = 1;
    map[y-15][x+18] = 1;
    map[y-15][x+19] = 1;

    map[y-16][x-1] = 1;
    map[y-16][x] = 1;
    map[y-16][x+2] = 1;
    map[y-16][x+9] = 1;
    map[y-16][x+11] = 1;
    map[y-16][x+18] = 1;
    map[y-16][x+20] = 1;
    map[y-16][x+21] = 1;

    map[y-17][x] = 1;
    map[y-17][x+2] = 1;
    map[y-17][x+9] = 1;
    map[y-17][x+11] = 1;
    map[y-17][x+18] = 1;
    map[y-17][x+20] = 1;

    map[y-18][x+6] = 1;
    map[y-18][x+7] = 1;
    map[y-18][x+9] = 1;
    map[y-18][x+11] = 1;
    map[y-18][x+13] = 1;
    map[y-18][x+14] = 1;

    map[y-19][x-1] = 1;
    map[y-19][x] = 1;
    map[y-19][x+4] = 1;
    map[y-19][x+5] = 1;
    map[y-19][x+6] = 1;
    map[y-19][x+7] = 1;
    map[y-19][x+9] = 1;
    map[y-19][x+11] = 1;
    map[y-19][x+13] = 1;
    map[y-19][x+14] = 1;
    map[y-19][x+15] = 1;
    map[y-19][x+16] = 1;
    map[y-19][x+20] = 1;
    map[y-19][x+21] = 1;

    map[y-20][x+6] = 1;
    map[y-20][x+7] = 1;
    map[y-20][x+9] = 1;
    map[y-20][x+11] = 1;
    map[y-20][x+13] = 1;
    map[y-20][x+14] = 1;

    map[y-21][x-1] = 1;
    map[y-21][x+2] = 1;
    map[y-21][x+4] = 1;
    map[y-21][x+5] = 1;
    map[y-21][x+15] = 1;
    map[y-21][x+16] = 1;
    map[y-21][x+18] = 1;
    map[y-21][x+21] = 1;

    map[y-22][x] = 1;
    map[y-22][x+2] = 1;
    map[y-22][x+5] = 1;
    map[y-22][x+15] = 1;
    map[y-22][x+18] = 1;
    map[y-22][x+20] = 1; 

}
//ªø½bÀY 
void la(int x, int y, int map[][100]) {
    map[y][x] = 1;
    map[y][x + 1] = 1;

    map[y + 1][x] = 1;
    map[y + 1][x + 2] = 1;

    map[y +2][x + 1] = 1;
    map[y +2][x + 3] = 1;

    map[y + 3][x + 2] = 1;
    map[y + 3][x + 4] = 1;

    map[y +4][x + 3] = 1;
    map[y + 4][x + 4] = 1;
}
//¤Ïªø½bÀY 
void laR(int x, int y, int map[][100]){
    map[y][x] = 1;
    map[y][x+1] = 1;
    
    map[y-1][x] = 1;
    map[y-1][x+2] = 1;

    map[y-2][x+1] = 1;
    map[y-2][x+3] = 1;
    
    map[y-3][x+2] = 1;
    map[y-3][x+4] = 1;

    map[y-4][x+3] = 1;
    map[y-4][x+4] = 1;
}

/******************wei**************************/
void big(int x ,int y, int map[][100])  //end
{
    map[y][x+11]=1;
    map[y][x+12]=1;
    map[y][x+13]=1;
    map[y][x+17]=1;
    map[y][x+18]=1;
    map[y][x+19]=1;
    map[y-2][x+9]=1;
    map[y-3][x+9]=1;
    map[y-4][x+9]=1;
    map[y-8][x+9]=1;
    map[y-9][x+9]=1;
    map[y-10][x+9]=1;
    map[y-12][x+11]=1;
    map[y-12][x+12]=1;
    map[y-12][x+13]=1;
    map[y-12][x+17]=1;
    map[y-12][x+18]=1;
    map[y-12][x+19]=1;
    map[y-5][x+11]=1;
    map[y-5][x+12]=1;
    map[y-5][x+13]=1;
    map[y-5][x+17]=1;
    map[y-5][x+18]=1;
    map[y-5][x+19]=1;
    map[y-7][x+11]=1;
    map[y-7][x+12]=1;
    map[y-7][x+13]=1;
    map[y-7][x+17]=1;
    map[y-7][x+18]=1;
    map[y-7][x+19]=1;
    map[y-2][x+14]=1;
    map[y-3][x+14]=1;
    map[y-4][x+14]=1;
    map[y-8][x+14]=1;
    map[y-9][x+14]=1;
    map[y-10][x+14]=1;
    map[y-2][x+16]=1;
    map[y-3][x+16]=1;
    map[y-4][x+16]=1;
    map[y-8][x+16]=1;
    map[y-9][x+16]=1;
    map[y-10][x+16]=1;
    map[y-2][x+21]=1;
    map[y-3][x+21]=1;
    map[y-4][x+21]=1;
    map[y-8][x+21]=1;
    map[y-9][x+21]=1;
    map[y-10][x+21]=1;

    map[y-16][x+11]=1;
    map[y-16][x+12]=1;
    map[y-16][x+13]=1;
    map[y-16][x+17]=1;
    map[y-16][x+18]=1;
    map[y-16][x+19]=1;
    map[y-18][x+9]=1;
    map[y-19][x+9]=1;
    map[y-20][x+9]=1;
    map[y-24][x+9]=1;
    map[y-25][x+9]=1;
    map[y-26][x+9]=1;
    map[y-28][x+11]=1;
    map[y-28][x+12]=1;
    map[y-28][x+13]=1;
    map[y-28][x+17]=1;
    map[y-28][x+18]=1;
    map[y-28][x+19]=1;
    map[y-21][x+11]=1;
    map[y-21][x+12]=1;
    map[y-21][x+13]=1;
    map[y-21][x+17]=1;
    map[y-21][x+18]=1;
    map[y-21][x+19]=1;
    map[y-23][x+11]=1;
    map[y-23][x+12]=1;
    map[y-23][x+13]=1;
    map[y-23][x+17]=1;
    map[y-23][x+18]=1;
    map[y-23][x+19]=1;
    map[y-18][x+14]=1;
    map[y-19][x+14]=1;
    map[y-20][x+14]=1;
    map[y-24][x+14]=1;
    map[y-25][x+14]=1;
    map[y-26][x+14]=1;
    map[y-18][x+16]=1;
    map[y-19][x+16]=1;
    map[y-20][x+16]=1;
    map[y-24][x+16]=1;
    map[y-25][x+16]=1;
    map[y-26][x+16]=1;
    map[y-18][x+21]=1;
    map[y-19][x+21]=1;
    map[y-20][x+21]=1;
    map[y-24][x+21]=1;
    map[y-25][x+21]=1;
    map[y-26][x+21]=1;

    map[y-8][x+55]=1;
    map[y-8][x+56]=1;
    map[y-8][x+57]=1;
    map[y-8][x+61]=1;
    map[y-8][x+62]=1;
    map[y-8][x+63]=1;
    map[y-10][x+53]=1;
    map[y-11][x+53]=1;
    map[y-12][x+53]=1;
    map[y-16][x+53]=1;
    map[y-17][x+53]=1;
    map[y-18][x+53]=1;
    map[y-20][x+55]=1;
    map[y-20][x+56]=1;
    map[y-20][x+57]=1;
    map[y-20][x+61]=1;
    map[y-20][x+62]=1;
    map[y-20][x+63]=1;
    map[y-13][x+55]=1;
    map[y-13][x+56]=1;
    map[y-13][x+57]=1;
    map[y-13][x+61]=1;
    map[y-13][x+62]=1;
    map[y-13][x+63]=1;
    map[y-15][x+55]=1;
    map[y-15][x+56]=1;
    map[y-15][x+57]=1;
    map[y-15][x+61]=1;
    map[y-15][x+62]=1;
    map[y-15][x+63]=1;
    map[y-10][x+58]=1;
    map[y-11][x+58]=1;
    map[y-12][x+58]=1;
    map[y-16][x+58]=1;
    map[y-17][x+58]=1;
    map[y-18][x+58]=1;
    map[y-10][x+60]=1;
    map[y-11][x+60]=1;
    map[y-12][x+60]=1;
    map[y-16][x+60]=1;
    map[y-17][x+60]=1;
    map[y-18][x+60]=1;
    map[y-10][x+65]=1;
    map[y-11][x+65]=1;
    map[y-12][x+65]=1;
    map[y-16][x+65]=1;
    map[y-17][x+65]=1;
    map[y-18][x+65]=1;

}

void light(int x,int y ,int map[][100]){
    map[y-5][x+29]=1;
    map[y-5][x+30]=1;
    map[y-5][x+28]=1;
    map[y-6][x+29]=1;
    map[y-6][x+28]=1;
    map[y-6][x+27]=1;

    map[y-5][x+41]=1;
    map[y-5][x+40]=1;
    map[y-5][x+42]=1;
    map[y-6][x+39]=1;
    map[y-6][x+41]=1;
    map[y-6][x+40]=1;

    map[y-7][x+34]=1;
    map[y-7][x+35]=1;
    map[y-7][x+36]=1;
    map[y-8][x+33]=1;
    map[y-8][x+34]=1;
    map[y-8][x+35]=1;

    map[y-7][x+48]=1;
    map[y-7][x+47]=1;
    map[y-7][x+46]=1;
    map[y-8][x+47]=1;
    map[y-8][x+46]=1;
    map[y-8][x+45]=1;

    map[y-23][x+29]=1;
    map[y-23][x+30]=1;
    map[y-23][x+28]=1;
    map[y-22][x+29]=1;
    map[y-22][x+28]=1;
    map[y-22][x+27]=1;

    map[y-23][x+41]=1;
    map[y-23][x+40]=1;
    map[y-23][x+42]=1;
    map[y-22][x+39]=1;
    map[y-22][x+41]=1;
    map[y-22][x+40]=1;

    map[y-21][x+34]=1;
    map[y-21][x+35]=1;
    map[y-21][x+36]=1;
    map[y-20][x+33]=1;
    map[y-20][x+34]=1;
    map[y-20][x+35]=1;

    map[y-21][x+48]=1;
    map[y-21][x+47]=1;
    map[y-21][x+46]=1;
    map[y-20][x+47]=1;
    map[y-20][x+46]=1;
    map[y-20][x+45]=1;
}
void h(int x,int y ,int map[][100]){
    map[y-13][x+25]=1;
    map[y-14][x+25]=1;
    map[y-15][x+25]=1;
    map[y-13][x+28]=1;
    map[y-14][x+28]=1;
    map[y-15][x+28]=1;
    map[y-14][x+26]=1;
    map[y-14][x+27]=1;

    map[y-15][x+25]=1;
    map[y-14][x+33]=1;
    map[y-15][x+33]=1;
    map[y-13][x+36]=1;
    map[y-14][x+36]=1;
    map[y-15][x+36]=1;
    map[y-14][x+34]=1;
    map[y-14][x+35]=1;

    map[y-14][x+30]=1;
    map[y-14][x+31]=1;
    map[y-15][x+30]=1;
    map[y-15][x+31]=1;
    map[y-13][x+31]=1;
    map[y-13][x+30]=1;
    map[y-13][x+33]=1;


}
void threespace(int x,int y ,int map[][100]){ //end
    map[y-13][x+42]=1;
    map[y-14][x+42]=1;
    map[y-15][x+42]=1;

    map[y-14][x+47]=1;
    map[y-15][x+47]=1;
    map[y-13][x+47]=1;

    map[y-12][x+71]=1;
    map[y-12][x+72]=1;
    map[y-12][x+73]=1;
    map[y-16][x+71]=1;
    map[y-16][x+72]=1;
    map[y-16][x+73]=1;

    map[y-5][x+75]=1;
    map[y-5][x+76]=1;
    map[y-5][x+77]=1;
    map[y-23][x+75]=1;
    map[y-23][x+76]=1;
    map[y-23][x+77]=1;

}
void cup(int x,int y ,int map[][100]){ //end
    map[y-9][x+76]=1;
    map[y-10][x+76]=1;
    map[y-18][x+76]=1;
    map[y-19][x+76]=1;
    map[y-9][x+77]=1;
    map[y-11][x+77]=1;
    map[y-14][x+77]=1;
    map[y-17][x+77]=1;
    map[y-19][x+77]=1;
    map[y-11][x+78]=1;
    map[y-12][x+78]=1;
    map[y-13][x+78]=1;
    map[y-14][x+78]=1;
    map[y-17][x+78]=1;
    map[y-11][x+79]=1;
    map[y-14][x+79]=1;
    map[y-9][x+79]=1;
    map[y-17][x+79]=1;
    map[y-19][x+79]=1;
    map[y-9][x+80]=1;
    map[y-10][x+80]=1;
    map[y-18][x+80]=1;
    map[y-19][x+80]=1;

    map[y-9][x+83]=1;
    map[y-10][x+83]=1;
    map[y-18][x+83]=1;
    map[y-19][x+83]=1;
    map[y-9][x+84]=1;
    map[y-11][x+84]=1;
    map[y-14][x+84]=1;
    map[y-17][x+84]=1;
    map[y-19][x+84]=1;
    map[y-11][x+85]=1;
    map[y-12][x+85]=1;
    map[y-13][x+85]=1;
    map[y-14][x+85]=1;
    map[y-17][x+85]=1;
    map[y-11][x+86]=1;
    map[y-14][x+86]=1;
    map[y-9][x+86]=1;
    map[y-17][x+86]=1;
    map[y-19][x+86]=1;
    map[y-9][x+87]=1;
    map[y-10][x+87]=1;
    map[y-18][x+87]=1;
    map[y-19][x+87]=1;
}
void shortstair(int x,int y,int map[][100]){

    map[y-21][x+73]=1;
    map[y-20][x+73]=1;
    map[y-20][x+72]=1;
    map[y-22][x+72]=1;
    map[y-21][x+71]=1;
    map[y-23][x+71]=1;
    map[y-22][x+70]=1;
    map[y-24][x+70]=1;
    map[y-23][x+69]=1;
    map[y-25][x+69]=1;
    map[y-24][x+68]=1;
    
    map[y-7][x+73]=1;
    map[y-8][x+73]=1;
    map[y-8][x+72]=1;
    map[y-6][x+72]=1;
    map[y-5][x+71]=1;
    map[y-7][x+71]=1;
    map[y-6][x+70]=1;
    map[y-4][x+70]=1;
    map[y-5][x+69]=1;
    map[y-3][x+69]=1;
    map[y-4][x+68]=1;

    map[y-19][x+1]=1;
    map[y-20][x+2]=1;
    map[y-18][x+2]=1;
    map[y-19][x+3]=1;
    map[y-17][x+3]=1;
    map[y-18][x+4]=1;
    map[y-16][x+4]=1;
    map[y-17][x+5]=1;
    map[y-15][x+5]=1;
    map[y-16][x+6]=1;
    map[y-15][x+6]=1;

    map[y-8][x+1]=1;
    map[y-7][x+2]=1;
    map[y-9][x+2]=1;
    map[y-10][x+3]=1;
    map[y-8][x+3]=1;
    map[y-9][x+4]=1;
    map[y-11][x+4]=1;
    map[y-10][x+5]=1;
    map[y-12][x+5]=1;
    map[y-11][x+6]=1;
    map[y-12][x+6]=1;


}
void longstair(int x,int y ,int map[][100]){
    map[y-22][x+84]=1;
    map[y-23][x+83]=1;
    map[y-22][x+82]=1;
    map[y-24][x+82]=1;
    map[y-23][x+81]=1;
    map[y-25][x+81]=1;
    map[y-24][x+80]=1;
    map[y-26][x+80]=1;
    map[y-25][x+79]=1;
    map[y-27][x+79]=1;
    map[y-26][x+78]=1;
    map[y-28][x+78]=1;
    map[y-27][x+77]=1;
    map[y-28][x+77]=1;

    map[y][x+77]=1;
    map[y][x+78]=1;
    map[y-1][x+77]=1;
    map[y-1][x+79]=1;
    map[y-2][x+78]=1;
    map[y-2][x+80]=1;
    map[y-3][x+79]=1;
    map[y-3][x+81]=1;
    map[y-4][x+80]=1;
    map[y-4][x+82]=1;
    map[y-5][x+81]=1;
    map[y-5][x+83]=1;
    map[y-6][x+82]=1;
    map[y-6][x+84]=1;

    map[y-1][x+1]=1;
    map[y-1][x+2]=1;
    map[y-2][x+1]=1;
    map[y-2][x+3]=1;
    map[y-3][x+4]=1;
    map[y-4][x+5]=1;
    map[y-5][x+6]=1;
    map[y-6][x+5]=1;
    map[y-6][x+6]=1;

    map[y-26][x+1]=1;
    map[y-26][x+2]=1;
    map[y-25][x+1]=1;
    map[y-25][x+3]=1;
    map[y-24][x+4]=1;
    map[y-23][x+5]=1;
    map[y-22][x+6]=1;
    map[y-21][x+5]=1;
    map[y-21][x+6]=1;

}
void line(int x,int y ,int map[][100]){ //é‚Šæ¡†end
    map[y][x+23]=1;
    map[y][x+24]=1;
    map[y][x+25]=1;
    map[y][x+26]=1;
    map[y][x+29]=1;
    map[y][x+30]=1;
    map[y][x+31]=1;
    map[y][x+32]=1;
    map[y][x+35]=1;
    map[y][x+36]=1;
    map[y][x+37]=1;
    map[y][x+38]=1;
    map[y][x+41]=1;
    map[y][x+42]=1;
    map[y][x+43]=1;
    map[y][x+44]=1;
    map[y][x+47]=1;
    map[y][x+48]=1;
    map[y][x+49]=1;
    map[y][x+50]=1;
    map[y][x+53]=1;
    map[y][x+54]=1;
    map[y][x+55]=1;
    map[y][x+56]=1;
    map[y][x+59]=1;
    map[y][x+60]=1;
    map[y][x+61]=1;
    map[y][x+62]=1;
    map[y][x+65]=1;
    map[y][x+66]=1;
    map[y][x+67]=1;
    map[y][x+68]=1;
    map[y][x+72]=1;
    map[y][x+70]=1;
    map[y][x+71]=1;
    map[y][x+73]=1;

    map[y-28][x+23]=1;
    map[y-28][x+24]=1;
    map[y-28][x+25]=1;
    map[y-28][x+26]=1;
    map[y-28][x+29]=1;
    map[y-28][x+30]=1;
    map[y-28][x+31]=1;
    map[y-28][x+32]=1;
    map[y-28][x+35]=1;
    map[y-28][x+36]=1;
    map[y-28][x+37]=1;
    map[y-28][x+38]=1;
    map[y-28][x+41]=1;
    map[y-28][x+42]=1;
    map[y-28][x+43]=1;
    map[y-28][x+44]=1;
    map[y-28][x+47]=1;
    map[y-28][x+48]=1;
    map[y-28][x+49]=1;
    map[y-28][x+50]=1;
    map[y-28][x+53]=1;
    map[y-28][x+54]=1;
    map[y-28][x+55]=1;
    map[y-28][x+56]=1;
    map[y-28][x+59]=1;
    map[y-28][x+60]=1;
    map[y-28][x+61]=1;
    map[y-28][x+62]=1;
    map[y-28][x+65]=1;
    map[y-28][x+66]=1;
    map[y-28][x+67]=1;
    map[y-28][x+68]=1;
    map[y-28][x+72]=1;
    map[y-28][x+70]=1;
    map[y-28][x+71]=1;
    map[y-28][x+73]=1;
}
/***************peiwen**************/
void aaa(int x, int y,int map[][100]){
 map[y+2][x-2] = 1;
 map[y+3][x-2] = 1;
 map[y+4][x-2] = 1;
 map[y+8][x-2] = 1;
 map[y+9][x-2] = 1;
 map[y+10][x-2] = 1;
 
 map[y][x] = 1;
 map[y+5][x] = 1;
 map[y+7][x] = 1;
 map[y+12][x] = 1;
 
 map[y][x+1] = 1;
 map[y+5][x+1] = 1;
 map[y+7][x+1] = 1;
 map[y+12][x+1] = 1;
 
 map[y][x+2] = 1;
 map[y+5][x+2] = 1;
 map[y+7][x+2] = 1;
 map[y+12][x+2] = 1;
 
 map[y+2][x+3] = 1;
 map[y+3][x+3] = 1;
 map[y+4][x+3] = 1;
 map[y+8][x+3] = 1;
 map[y+9][x+3] = 1;
 map[y+10][x+3] = 1;
 
 map[y+2][x+5] = 1;
 map[y+3][x+5] = 1;
 map[y+4][x+5] = 1;
 map[y+8][x+5] = 1;
 map[y+9][x+5] = 1;
 map[y+10][x+5] = 1;
 
 map[y][x+6] = 1;
 map[y+5][x+6] = 1;
 map[y+7][x+6] = 1;
 map[y+12][x+6] = 1;

 map[y][x+7] = 1;
 map[y+5][x+7] = 1;
 map[y+7][x+7] = 1;
 map[y+12][x+7] = 1; 

 map[y][x+8] = 1;
 map[y+5][x+8] = 1;
 map[y+7][x+8] = 1;
 map[y+12][x+8] = 1;
 
 map[y+2][x+10] = 1;
 map[y+3][x+10] = 1;
 map[y+4][x+10] = 1;
 map[y+8][x+10] = 1;
 map[y+9][x+10] = 1;
 map[y+10][x+10] = 1;
 
}

void bbb(int x, int y,int map[][100]){
 map[y+20][x-2] = 1;
 map[y+26][x-2] = 1;

 map[y+20][x-1] = 1;
 map[y+26][x-1] = 1;
 
 map[y+20][x] = 1;
 map[y+21][x] = 1;
 map[y+25][x] = 1; 
 map[y+26][x] = 1;
 
 map[y+16][x+2] = 1; 
 map[y+17][x+2] = 1;
 map[y+18][x+2] = 1;
 map[y+21][x+2] = 1;
 map[y+22][x+2] = 1;
 map[y+24][x+2] = 1;
 map[y+25][x+2] = 1;
 map[y+28][x+2] = 1;
 map[y+29][x+2] = 1;
 map[y+30][x+2] = 1;
 
 map[y+18][x+3] = 1;
 map[y+20][x+3] = 1;
 map[y+22][x+3] = 1;
 map[y+24][x+3] = 1;
 map[y+26][x+3] = 1;
 map[y+28][x+3] = 1;
 
 map[y+20][x+4] = 1;
 map[y+21][x+4] = 1;
 map[y+25][x+4] = 1;
 map[y+26][x+4] = 1; 
 
 map[y+20][x+6] = 1;
 map[y+21][x+6] = 1;
 map[y+25][x+6] = 1;
 map[y+26][x+6] = 1;

 map[y+18][x+7] = 1;
 map[y+20][x+7] = 1;
 map[y+22][x+7] = 1;
 map[y+24][x+7] = 1;
 map[y+26][x+7] = 1;
 map[y+28][x+7] = 1;
 
 map[y+16][x+8] = 1; 
 map[y+17][x+8] = 1;
 map[y+18][x+8] = 1;
 map[y+21][x+8] = 1;
 map[y+22][x+8] = 1;
 map[y+24][x+8] = 1;
 map[y+25][x+8] = 1;
 map[y+28][x+8] = 1;
 map[y+29][x+8] = 1;
 map[y+30][x+8] = 1; 
 
 map[y+20][x+10] = 1;
 map[y+21][x+10] = 1;
 map[y+25][x+10] = 1; 
 map[y+26][x+10] = 1;
 
 map[y+20][x+11] = 1;
 map[y+26][x+11] = 1;

 map[y+20][x+12] = 1;
 map[y+26][x+12] = 1;
}

