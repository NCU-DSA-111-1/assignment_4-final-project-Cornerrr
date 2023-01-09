#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

void Goxy(int x, int y) {
	COORD xy;
	xy.X = x - 1;
	xy.Y = y - 1;
}
void SetColor(int ForgC)
{
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
}
struct position
{
	COORD pos;
	COORD old_pos;
	int line_count;
	int old_line_count;
	struct position* nextp;
	struct position* last_nextp;
};
//2023/01/06 子彈製作
struct bullet_pos
{
	COORD pos;
	int bullet_type;//1:弓箭 2:魔法球
	int direction; //1 2 3 4 代表上下左右
	int damage;		//子彈打到人的傷害
	struct bullet_pos* pnext;
	struct bullet_pos* last_pnext;
};

//2023/01/07 敵人製作(簡單設設只是為了測子彈碰撞
struct enermy
{
	COORD pos;
	COORD old_pos;
	int hp;
	int damage;
};

