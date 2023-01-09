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
//2023/01/06 �l�u�s�@
struct bullet_pos
{
	COORD pos;
	int bullet_type;//1:�}�b 2:�]�k�y
	int direction; //1 2 3 4 �N��W�U���k
	int damage;		//�l�u����H���ˮ`
	struct bullet_pos* pnext;
	struct bullet_pos* last_pnext;
};

//2023/01/07 �ĤH�s�@(²��]�]�u�O���F���l�u�I��
struct enermy
{
	COORD pos;
	COORD old_pos;
	int hp;
	int damage;
};

