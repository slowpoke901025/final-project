#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "Windows.h"
#include "Conway.h"
#include "Level.h"
#include "Map.h"
#include "Screen.h"
#include "SaveFile.h"


/*****主函式*****/

int main()
{
	system("title Flea's Adventure");
	system("color 0F");
	full_screen();
	
	
	startUp();
	story();
	getName(Bug.name);
	animationStart();
	
	for(int i=0;i<5;i++)
	{
		showBeforeRun(i);
			
		setLevel(i);
		resetMap();
		setMap(Map.main,Map.treasure,i);
		
		Bound();
		InfoBox();	
		
		Time.start=time(NULL);
		
		while(pTime()&&Level.pass==0&&Bug.blood>0)
		{
			pSit();
			if(Level.speed-- == 0)
			{   
				Evolution();
				printMap();
				Level.speed = 4000;
			}
			else
			{
				printBug();	
			}

			bugMove();		
		}
		
		system("cls");
	
		if(Level.pass==0)
		{
			break;//失敗畫面 
		}
		else
		{
			Time.total+=(Time.limit-Time.left);
		}		
	}

	if(Level.pass!=0)
	{
		animationEnd();
		printResult(Time.total);
		showBoard();
		updateRank(Bug.name,Time.total);
	}
	else
	{
		fail();
	}
	
}



