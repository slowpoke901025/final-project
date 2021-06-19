#include<stdio.h>
#include<string.h>
#include "SaveFile.h"
#include "Windows.h"
struct File
{
	char Dump[5];
	char Name[20];
	int Time;	
};

void updateRank(char name[],int timeTotal) 
{
	struct File file;
	int rank=0;
	char list[500]={};
	char temp[200]={};
	FILE *F = fopen("TT.txt","a+");
	
	color(15);
	gotoxy(31,19);
	printf("%-16s%-13s%-10s\n","RANK","NAME","TIME(S)");
	gotoxy(67,19);
	printf("%-16s%-13s%-10s\n","RANK","NAME","TIME(S)");
	
	while(!feof(F)&&rank<=10)
	{   
		if(rank>0)
		{	
			if(timeTotal<=file.Time)
			{
				color(6);
				printRank(rank,name,timeTotal,temp,list);
				rank++;
				timeTotal=10000;
				continue;
			}
			color(10);
			printRank(rank,file.Name,file.Time,temp,list);
			
		}
		fscanf(F,"%s%s%d",file.Dump,file.Name,&file.Time);
		rank++;
	}
	
	if(rank<=10&&timeTotal<10000)
	{
		color(6);
		printRank(rank,name,timeTotal,temp,list);
	}
	
	fclose(F);
	saveFile(list);
	
}

void printRank(int Rank,char Name[],int Time,char temp[],char list[] )
{
	static int lineR=23,lineL=23;
	
	sprintf(temp,"No.%-13d%-13s%4d\n",Rank,Name,Time);
	if(Rank<=5)
	{
		gotoxy(31,lineL);
		lineL+=5;
	}
	else
	{
		gotoxy(67,lineR);
		lineR+=5;
	}
	printf("%s",temp);
	strncat(list,temp,100);
}

void saveFile(char list[])
{
	FILE *F = fopen("TT.txt","w");
	fprintf(F,"%s",list);
	fclose(F);
	pressToContinue();
}
