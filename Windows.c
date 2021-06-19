#include<windows.h>
#include<conio.h>

void full_screen()
{   
    HWND hwnd = GetForegroundWindow();
    int cx = GetSystemMetrics(SM_CXSCREEN);            
    int cy = GetSystemMetrics(SM_CYSCREEN);           

    LONG l_WinStyle = GetWindowLong(hwnd,GWL_STYLE);  
 
    SetWindowLong(hwnd,GWL_STYLE,(l_WinStyle | WS_POPUP | WS_MAXIMIZE) );

    SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}
void gotoxy(int x, int y)//游標位移(windows.h) 
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD pos;

	pos.X = 2*x;

	pos.Y = y;

	SetConsoleCursorPosition(handle, pos);
}
void HideCursor() // 用於隱藏光標
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void color(short x)    //自定義函式根據參數改變顏色 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x); 
}

void sound()//發出聲音,並清空緩衝區(避免重複判斷撞擊) 
{
	Beep(500,1000);
	char ch;
	while (kbhit()) 
	{
		ch=getch();
	}	
}
void pressToContinue()
{
	gotoxy(85,52);
	system("pause Press any key to continue...... ");
	system("cls");
}
void sleep(int ms)
{
	
	Sleep(ms);
}
