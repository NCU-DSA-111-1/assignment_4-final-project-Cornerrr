#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <conio.h>
#include <time.h>
#include"define.h"
#include"drawUI.h"
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

void game_start();
void show_health(COORD* current_xy);
void show_mp();
int keybord_control(COORD* current_xy);
void show_all_data(COORD* current_xy);
void character(int i);
void print_character(COORD* current_xy, int i);
int choose_role();
int exceed_map(COORD* current_xy);
void story2_print();
int exceed_map1(COORD* current_xy);
void Holt_chat(COORD* current_xy);
void show_Holt_health(COORD* current_xy);

//2023/01/06子彈製作
#define SHOOT_HOW_FAST 20			//子彈射擊的頻率(數字越大設越慢
void print_all(COORD* current_xy);
void print_bullet();
void PRINT_bullet_function(struct bullet_pos* first_bullet);
void generate_bullet(COORD* current_xy, int direction);
void JUDGE_bullet_function(struct bullet_pos** first_bullet, int* bullet_amount);
void judge_bullet();
void UPDATE_bullet_list(struct bullet_pos* first_point);
void update_bullet_xy();
void free_bullet_function(struct bullet_pos** current_bullet);
//void Linked_all_bullet();
//void deLinked_all_bullet();
struct bullet_pos* First_Node_of_All_bullet;
struct bullet_pos* last_Node_of_All_bullet;
int bullet_amount = 0;  //計算子彈多少個鏈節串在一起
struct bullet_pos* first_bullet = NULL;  //1號武器的頭指針，
struct bullet_pos* last_bullet = NULL;
COORD tmp_old_bullet;
int surplus_bullet = 20;
//2023/01/07 敵人製作(簡單設設只是為了測子彈碰撞，目前先以nidandan當敵人看子彈會不會消失
struct enermy holt;
void print_holt();
void generate_holt();
int update_holt(COORD* current_xy);


int count_main_while_time = 0;
int health = 6;
int mp = 10;
COORD old_character_pos;
int map1_agree = 1;
int rolechoice;
int Holt_chat_agree;
int battle_agree;
int map1_exceed_agree;
int holtchat;
int invincible_time = 0;
int skillone;

int main() {
	srand((unsigned int)time(NULL));
	system("mode con cols=140 lines=30");
	system("title Starry        created by Corner and nihowma");
	story_print();
	game_start();
	system("pause");
}
//開始遊戲
void game_start() {
	bullet_amount = 0;//數據初始化
	COORD current_xy;
	current_xy.X = 7;
	current_xy.Y = 22;
	COORD time_xy;
	time_xy.X = 113;
	time_xy.Y = 15;
	count_main_while_time = 1;
	rolechoice = choose_role();
	Holt_chat_agree = 1;
	battle_agree = 0;
	map1_exceed_agree = 1;
	holtchat = 1;
	skillone = 0;
	generate_holt();
	while (1) {
		if (map1_agree == 1) {//地圖一
			back_ground2();
			//story2_print();
			map1_agree = 0;
		}
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), time_xy);//時間
		printf("時間 : %d", count_main_while_time);
		keybord_control(&current_xy);//鍵盤控制
		exceed_map(&current_xy);//邊界判定
		if (Holt_chat_agree == 1) {
			Holt_chat(&current_xy);
		}
		if (battle_agree == 1) {
			if (GetAsyncKeyState(0x45) && mp > 0) {
				skillone = 1;
			}
			if (GetAsyncKeyState(0x51)) {
				skillone = 0;
			}
			print_holt();
			show_Holt_health(&current_xy);
			update_holt(&current_xy);
		}
		if (map1_exceed_agree == 1) {
			exceed_map1(&current_xy);//圖一邊界判定
		}

		print_character(&current_xy, rolechoice);
		print_all(&current_xy);
		if ((bullet_amount) >= 1)
		{
			judge_bullet();//判斷是否超邊界要釋放記憶體
			update_bullet_xy();
		}
		show_all_data(&current_xy);
		count_main_while_time++;
		Sleep(25);
		if (count_main_while_time > 999999) {
			count_main_while_time = 1;
		}
		if (count_main_while_time % 3500 == 0) {
			mciSendString((LPCWSTR)("seek music1 to start"), NULL, 0, NULL);
			mciSendString((LPCWSTR)("play music1"), NULL, 0, NULL);
		}
	}


}
void show_all_data(COORD* current_xy) {
	show_health(current_xy);
	show_mp();
}
//角色血量
void show_health(COORD* current_xy)
{
	int i;
	COORD health_pos;
	health_pos.X = 120;			//放血條那邊的中心點
	health_pos.Y = 17;
	COORD rim;
	COORD word;
	rim.X = health_pos.X - 2;
	rim.Y = health_pos.Y - 1;
	word.X = health_pos.X - 7;
	word.Y = health_pos.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), health_pos);//先把舊的清除
	printf("            ");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rim);
	printf("┌                ┐");
	rim.Y += 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rim);
	printf("└                ┘");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), word);
	printf("HP:");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), health_pos);
	for (i = 0; i < health; i++)
	{
		SetColor(4);
		printf("▇");
	}
	/*SetColor(4);
	printf("8=====D");*/
	if (health == 0) {
		COORD text_pos;
		text_pos.X = 40;
		text_pos.Y = 24;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), text_pos);
		printf("霍特: %s,你還是回去種田吧", name);
		Sleep(2000);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), text_pos);
		printf("                           ");
		current_xy->X = 72;
		current_xy->Y = 19;
		back_ground2();
		battle_agree = 0;
		Holt_chat_agree = 1;
		health = 6; //預設改成current_health
		mp = 10;
		invincible_time = 0;
		generate_holt();
	}
	printf("\n");
	SetColor(7);
}
//霍特血量
void show_Holt_health(COORD* current_xy)
{
	int i;
	COORD holt_health_pos;
	holt_health_pos.X = 24;			//放血條那邊的中心點
	holt_health_pos.Y = 2;
	COORD holt_rim;
	COORD holt_word;
	holt_rim.X = holt_health_pos.X - 2;
	holt_rim.Y = holt_health_pos.Y - 1;
	holt_word.X = holt_health_pos.X - 7;
	holt_word.Y = holt_health_pos.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), holt_health_pos);//先把舊的清除
	printf("                                          ");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), holt_rim);
	printf("┌                                         ┐");
	holt_rim.Y += 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), holt_rim);
	printf("└                                         ┘");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), holt_word);
	printf("HOLT:");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), holt_health_pos);
	for (i = 0; i < holt.hp; i++)
	{
		SetColor(4);
		printf("▇");
	}
	if (holt.hp <= 0) {
		COORD text_pos;
		text_pos.X = 40;
		text_pos.Y = 24;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), text_pos);
		printf("霍特: %s,身手變得不錯了呢", name);
		Sleep(2000);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), text_pos);
		printf("                           ");
		current_xy->X = 72;
		current_xy->Y = 19;
		back_ground2();
		map1_exceed_agree = 1;
		battle_agree = 0;
		holtchat = 2;
		map1_exceed_agree = 1;
		Holt_chat_agree = 1;
		mp = 10;
	}
	SetColor(7);
}
//角色魔量
void show_mp()
{
	int i;
	COORD mp_pos;
	mp_pos.X = 120;			//放血條那邊的中心點
	mp_pos.Y = 21;
	COORD rim;
	COORD word;
	rim.X = mp_pos.X - 2;
	rim.Y = mp_pos.Y - 1;
	word.X = mp_pos.X - 7;
	word.Y = mp_pos.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mp_pos);//先把舊的清除
	printf("            ");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rim);
	printf("┌            ┐");
	rim.Y += 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rim);
	printf("└            ┘");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), word);
	printf("MP:");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mp_pos);
	for (i = 0; i < mp; i++)
	{
		SetColor(3);
		printf("▇");
	}


	printf("\n");
	SetColor(7);
}
void story2_print() {
	COORD chat_pos;
	chat_pos.X = 13;
	chat_pos.Y = 4;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	SetColor(7);
	printf("星星消失的原因無人得知，");
	Sleep(2500);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("                         ");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("所以阿，");
	Sleep(1500);
	chat_pos.Y = chat_pos.Y + 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("少年下定決心，踏上旅程，");
	Sleep(2500);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("                         ");
	chat_pos.Y = chat_pos.Y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("                         ");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("朝著隕石降落的彼端，");
	Sleep(1500);
	chat_pos.Y = chat_pos.Y + 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("前進——");
	Sleep(2500);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("                         ");
	chat_pos.Y = chat_pos.Y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("                         ");
}
//霍特對話
void Holt_chat(COORD* current_xy) {
	if (current_xy->X >= 68 && current_xy->Y <= 19 && current_xy->X <= 85 && current_xy->Y >= 15) {
		COORD chat_pos;
		chat_pos.X = 13;
		chat_pos.Y = 4;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
		SetColor(7);
		printf("按下空白開始對話");
		if (GetAsyncKeyState(0x20)) {
			if (holtchat == 1) {
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                         ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("霍特 : %s 長大了阿", name);
				Sleep(2500);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                         ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("霍特 : 聽話 讓我看看");
				Sleep(2500);
				chat_pos.Y += 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("       你的實力!");
				Sleep(2500);
				chat_pos.Y -= 1;
				current_xy->X = 33;
				current_xy->Y = 14;
				battle_print();
				battle_agree = 1;
				Holt_chat_agree = 0;
				map1_exceed_agree = 0;
			}
			if (holtchat == 2) {
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                         ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("霍特 : %s 看來師父", name);
				Sleep(2500);
				chat_pos.Y += 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("       已經沒什麼可以教你的了");
				Sleep(2500);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                              ");
				chat_pos.Y -= 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                        ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("霍特 : 快走吧 朝著你的目標...");
				Sleep(2500);
				chat_pos.Y += 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("        你已經可以了!");
				Sleep(2500);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                                 ");
				chat_pos.Y -= 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                                  ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("霍特 : 等等,這個星葉項鍊就給你吧");
				Sleep(2500);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                                  ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("霍特 : 相信它會對你有幫助的");
				Sleep(2500);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                                  ");
				SetColor(6);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("獲得星葉項鍊");
				Sleep(2500);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("擊敗敵人後 項鍊會累積星星的能量");
				Sleep(2500);
				chat_pos.Y += 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("並提升血量");
				Sleep(2500);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                 ");
				chat_pos.Y -= 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                                  ");
				health = 8;
				COORD health_pos;
				health_pos.X = 120;			//放血條那邊的中心點
				health_pos.Y = 17;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), health_pos);//先把舊的清除
				printf("            ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), health_pos);
				for (int i = 0; i < health; i++)
				{
					SetColor(4);
					printf("▇");
				}
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("血量已提升");
				Sleep(2500);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                  ");
				SetColor(7);
				Holt_chat_agree = 0;
			}
		}
	}
}
//鍵盤控制
int keybord_control(COORD* current_xy)
{
	static int count_up_key = 0;
	static int count_down_key = 0;
	static int count_rightup_key = 0;
	static int count_leftup_key = 0;
	static int count_rightdown_key = 0;
	static int count_leftdown_key = 0;
	static int count_space_key = 3;
	int w, a, s, d, up, down, left, right;
	w = GetKeyState(0x57);
	d = GetKeyState(0x44);
	a = GetKeyState(0x41);
	s = GetKeyState(0x53);
	up = GetAsyncKeyState(0x26);
	down = GetAsyncKeyState(0x28);
	left = GetAsyncKeyState(0x25);
	right = GetAsyncKeyState(0x27);
	//2023/01/06子彈更新_多方向攻擊
	if (battle_agree == 1) {
		if (count_space_key < SHOOT_HOW_FAST)		//如果沒等於SOOT_HOW_FAST就加一
			count_space_key++;
		if (GetAsyncKeyState(0x26))//方向鍵上攻擊
		{
			if (count_space_key == SHOOT_HOW_FAST)		//用SHOOT_HOW_FAST決定要射多快
			{
				generate_bullet(current_xy, 1);   //已經是指針就不用再傳遞地址
				count_space_key = 0;
			}
			count_space_key++;		//把這個變數改到外面

		}
		else if (GetAsyncKeyState(0x28))//方向鍵下攻擊
		{
			if (count_space_key == SHOOT_HOW_FAST)
			{
				generate_bullet(current_xy, 2);   //已經是指針就不用再傳遞地址
				count_space_key = 0;
			}
			count_space_key++;

		}
		else if (GetAsyncKeyState(0x25))//方向鍵左攻擊
		{
			if (count_space_key == SHOOT_HOW_FAST)
			{
				generate_bullet(current_xy, 3);   //已經是指針就不用再傳遞地址
				count_space_key = 0;
			}
			count_space_key++;

		}
		else if (GetAsyncKeyState(0x27))//方向鍵右攻擊
		{
			if (count_space_key == SHOOT_HOW_FAST)
			{
				generate_bullet(current_xy, 4);   //已經是指針就不用再傳遞地址
				count_space_key = 0;
			}
			count_space_key++;

		}
	}
	if (w < 0 && d < 0 /*|| right < 0 && up < 0*/) //右上
	{
		if (count_rightup_key == 1)
		{
			current_xy->Y -= 1;
			current_xy->X += 1;
			count_rightup_key = 0;
		}
		else
			count_rightup_key++;
		return 0;
	}
	if (w < 0 && a < 0 /*|| left < 0 && up < 0*/) //左上
	{
		if (count_leftup_key == 1)
		{
			current_xy->Y -= 1;
			current_xy->X -= 1;
			count_leftup_key = 0;
		}
		else
			count_leftup_key++;
		return 0;
	}
	if (d < 0 && s < 0 /*|| right < 0 && down < 0*/) //右下
	{
		if (count_rightdown_key == 1)
		{
			current_xy->Y += 1;
			current_xy->X += 1;
			count_rightdown_key = 0;
		}
		else
			count_rightdown_key++;
		return 0;
	}
	if (a < 0 && s < 0 /*|| left < 0 && down < 0*/) //左下
	{
		if (count_leftdown_key == 1)
		{
			current_xy->Y += 1;
			current_xy->X -= 1;
			count_leftdown_key = 0;
		}
		else
			count_leftdown_key++;
		return 0;
	}
	if (GetAsyncKeyState(0x41) /*|| GetAsyncKeyState(0x25)*/) //左
	{
		current_xy->X -= 1;
		return 0;
	}
	if (GetAsyncKeyState(0x44) /*|| GetAsyncKeyState(0x27)*/)//右
	{
		current_xy->X += 1;
		return 0;
	}
	if (GetAsyncKeyState(0x57) /*|| GetAsyncKeyState(0x26)*/)//上
	{
		if (count_up_key == 2)
		{
			current_xy->Y -= 1;
			count_up_key = 0;
		}
		count_up_key++;
		return 0;
	}
	if (GetAsyncKeyState(0x53)/* || GetAsyncKeyState(0x28)*/)//下
	{
		if (count_down_key == 2)
		{
			current_xy->Y += 1;
			count_down_key = 0;
		}
		count_down_key++;
		return 0;
	}
	return 0;
}
//選擇職業
int choose_role() {
	COORD choose_role_text;
	choose_role_text.X = 40;
	choose_role_text.Y = 24;
	char rolenum[20];
	int role_num;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), choose_role_text);
	SetColor(9);
	printf("請選擇職業...");
	Sleep(2000);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), choose_role_text);
	printf("5秒內按下1.「戰士」; 按下2.「遊俠」:  ");
	Sleep(2000);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), choose_role_text);
	printf("                                      ");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), choose_role_text);
	printf("Loading...");
	Sleep(1000);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), choose_role_text);
	printf("                                      ");
	if (GetAsyncKeyState(0x31))//1
	{
		SetColor(7);
		role_num = 1;
		return role_num;
	}
	else if (GetAsyncKeyState(0x32))//2
	{
		SetColor(7);
		role_num = 2;
		return role_num;
	}
}
//2023/1/5晚上，優化邊界判定
int exceed_map(COORD* current_xy) {

	if (current_xy->X > 104) {
		current_xy->X = 104;
	}
	if (current_xy->X < 2) {
		current_xy->X = 2;
	}
	if (current_xy->Y > 24) {
		current_xy->Y = 24;
	}
	if (current_xy->Y < 1) {
		current_xy->Y = 1;
	}
	if (holt.pos.X > 104) {
		holt.pos.X = 104;
	}
	if (holt.pos.X < 2) {
		holt.pos.X = 2;
	}
	if (holt.pos.Y > 24) {
		holt.pos.Y = 24;
	}
	if (holt.pos.Y < 1) {
		holt.pos.Y = 1;
	}
	return 0;
}
//地圖一邊界判定
int exceed_map1(COORD* current_xy) {
	if (current_xy->Y > 22) {
		current_xy->Y = 22;
	}
	if (current_xy->Y < 16) {
		current_xy->Y = 16;
	}
	for (int i = 0; i < 25; i++) {
		if ((current_xy->X == (3 + i)) && (current_xy->Y == 21)) {
			current_xy->X = (3 + i);
			current_xy->Y = 22;
		}
	}
	for (int i = 0; i < 6; i++) {
		if ((current_xy->X == 28) && (current_xy->Y == (21 - i))) {
			current_xy->X = 29;
			current_xy->Y = (21 - i);
		}
	}
	for (int i = 0; i < 3; i++) {
		if ((current_xy->X == 69) && (current_xy->Y == (18 - i))) {
			current_xy->X = 68;
			current_xy->Y = (18 - i);
		}
	}
	for (int i = 0; i < 16; i++) {
		if ((current_xy->X == (69 + i)) && (current_xy->Y == 18)) {
			current_xy->X = (69+ i);
			current_xy->Y = 19;
		}
	}
	for (int i = 0; i < 3; i++) {
		if ((current_xy->X == 89) && (current_xy->Y == (21 - i))) {
			current_xy->X = 88;
			current_xy->Y = (21 - i);
		}
	}
	for (int i = 0; i < 25; i++) {
		if ((current_xy->X == (90 + i)) && (current_xy->Y == 21)) {
			current_xy->X = (90 + i);
			current_xy->Y = 22;
		}
	}
	return 0;
}
void print_character(COORD* current_xy, int rolechoice) {
	COORD xy;
	xy.X = current_xy->X;
	xy.Y = current_xy->Y;
	if (count_main_while_time != 1)  //如果是第一次迴圈 就跳過隱藏舊的人
	{
		for (int i = 0; i < 3; i++)
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), old_character_pos);
			printf("      ");
			old_character_pos.Y += 1;
		}
	}
	old_character_pos = xy;
	if (invincible_time != 0 && health != 0) {
		SetColor(invincible_time);
	}
	for (int i = 0, j = 3; i < 3, j < 6; i++, j++) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
		switch (rolechoice) {
		case 1:
			character(i);
			break;
		case 2:
			character(j);
			break;
		}
		xy.Y += 1;
	}
}
//2023/01/06 子彈製作
void free_bullet_function(struct bullet_pos** current_bullet)
{
	COORD xy = (*current_bullet)->pos;
	xy.Y += 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
	printf(" ");
	if ((*current_bullet)->last_pnext == NULL && (*current_bullet)->pnext == NULL)   //假如三個彈鏈加起來只有一顆
	{
		First_Node_of_All_bullet = NULL;
		last_Node_of_All_bullet = NULL;
	}
	else if ((*current_bullet)->last_pnext == NULL && (*current_bullet)->pnext != NULL)  //三個以上第一個
	{
		First_Node_of_All_bullet = (*current_bullet)->pnext;
		First_Node_of_All_bullet->last_pnext = NULL;
	}
	else if ((*current_bullet)->last_pnext != NULL && (*current_bullet)->pnext == NULL) //三個以上 最後一個
	{
		(*current_bullet)->last_pnext->pnext = NULL;
		last_Node_of_All_bullet = (*current_bullet)->last_pnext;
		last_Node_of_All_bullet->pnext = NULL;
	}
	else
	{
		(*current_bullet)->last_pnext->pnext = (*current_bullet)->pnext; //第一個指向第三個
		(*current_bullet)->pnext->last_pnext = (*current_bullet)->last_pnext;//第三個指向第一個
	}
}


//2023/01/09新增分辨碰撞到誰
//用於判斷邊界
void JUDGE_bullet_function(struct bullet_pos** first_bullet, int* bullet_amount)  //由於會重新改變指針指向 所以需要用二級指針 判斷子彈是否超過邊界
{
	struct bullet_pos* current_bullet = NULL;//用來讓鏈表run一遍的指針
	struct bullet_pos* tmp = NULL;
	current_bullet = (*first_bullet);
	int condition = 0;						//沒碰撞 = 0, 有碰撞邊界 = 1, 有碰撞敵人 = 2;

	while (current_bullet != NULL)
	{
		condition = 0;		//每次記得歸零
		if (holt.pos.X + 10 >= current_bullet->pos.X && current_bullet->pos.X >= holt.pos.X - 2 && holt.pos.Y + 3 >= current_bullet->pos.Y && current_bullet->pos.Y >= holt.pos.Y - 1) {		//撞到人
			condition = 2;
			holt.hp -= current_bullet->damage;
		}
		else if (current_bullet->pos.Y <= 1 || current_bullet->pos.X <= 3 || current_bullet->pos.Y >= 26 || current_bullet->pos.X >= 106) {	//撞到邊
			condition = 1;
		}
		//2023/01/07敵人碰撞判斷(目前打霍特當敵人
		if (condition != 0)  //如果超過邊界或撞到敵人
		{
			struct bullet_pos* ready_to_free = NULL;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current_bullet->pos);
			printf("  ");
			ready_to_free = current_bullet;
			if (current_bullet->last_pnext == NULL && current_bullet->pnext == NULL)//如果是最後一發子彈 就把頭子彈指向NULL
			{
				current_bullet = NULL;			//跳出
				*first_bullet = NULL;
				*bullet_amount = 0;             //沒有子彈了

			}
			else if (current_bullet->last_pnext == NULL && current_bullet->pnext != NULL)
			{
				(*first_bullet) = current_bullet->pnext;   //讓第二顆子彈 當成第一科子彈
				(*first_bullet)->last_pnext = NULL;      //因為第二顆子彈 變成第一顆了 所以要把指向上一個節點指針 重新指向NULL
				free(ready_to_free);                     //把第一科子彈釋放內存
				*bullet_amount -= 1;                    //子彈少一科
				current_bullet = NULL;		//跳出
			}
			else if (current_bullet->last_pnext != NULL && current_bullet->pnext != NULL)
			{
				tmp = current_bullet->last_pnext;
				tmp->pnext = current_bullet->pnext; //第一個指向第三個
				current_bullet = current_bullet->pnext;
				current_bullet->last_pnext = tmp;//第三個指向第一個
				*bullet_amount -= 1;

				free(ready_to_free);
			}
			else if (current_bullet->last_pnext != NULL && current_bullet->pnext == NULL)
			{
				tmp = current_bullet->last_pnext;
				tmp->pnext = NULL;
				current_bullet = NULL;	//跳出
				*bullet_amount -= 1;
				free(ready_to_free);
			}
		}
		else {
			current_bullet = current_bullet->pnext;
		}

	}
}

void judge_bullet()//判斷子彈使否超出邊界 若超出則釋放掉記憶體
{
	if (first_bullet != NULL)
	{
		JUDGE_bullet_function(&first_bullet, &bullet_amount);
	}

}
void UPDATE_bullet_list(struct bullet_pos* first_point) //更新子彈座標，讓他往特定地方跑
{
	struct bullet_pos* current_bullet = NULL;//用來讓鏈表run一遍的指針
	current_bullet = first_point;
	while (current_bullet != NULL)
	{

		switch (current_bullet->direction)
		{
		case 1:
			current_bullet->pos.Y -= 1;		//向上跑
			break;
		case 2:
			current_bullet->pos.Y += 1;		//向下跑
			break;
		case 3:
			current_bullet->pos.X -= 1;		//向左跑
			break;
		case 4:
			current_bullet->pos.X += 1;		//向右跑

			break;
		}
		current_bullet = current_bullet->pnext;

	}
}

void generate_bullet(COORD* current_xy, int direction)
{
	if (direction == 1)		//向上射
	{
		struct bullet_pos* bullet = (struct bullet_pos*)malloc(sizeof(struct bullet_pos));
		bullet_amount++;
		bullet->pos.X = current_xy->X + 2;
		bullet->pos.Y = current_xy->Y - 2;
		bullet->bullet_type = 1;//第幾種彈鏈
		bullet->direction = 1;//方向往上
		if (skillone == 1) {//skillone傷害增加
			bullet->damage = 2;
			mp--;
			if (mp == 0) {
				skillone = 0;
			}
		}
		else if (skillone == 0) {
			bullet->damage = 1;		//傷害設為1
		}		//傷害設為1
		bullet->last_pnext = NULL;
		if (bullet_amount == 1)              //第一顆子彈
		{
			first_bullet = bullet;
			last_bullet = bullet;
		}
		else
		{
			bullet->last_pnext = last_bullet;//目前的節點 指向上一個得節點=上一個節點
			last_bullet->pnext = bullet;//上一個節點 指向得下一個節點=目前的節點
			last_bullet = bullet;       //假定目前的節點為最後一個
		}
		bullet->pnext = NULL;
	}
	else if (direction == 2)		//向下射
	{
		struct bullet_pos* bullet = (struct bullet_pos*)malloc(sizeof(struct bullet_pos));
		bullet_amount++;
		if (skillone == 1) {//skillone傷害增加
			bullet->damage = 2;
			mp--;
			if (mp == 0) {
				skillone = 0;
			}
		}
		else if (skillone == 0) {
			bullet->damage = 1;		//傷害設為1
		}
		/*bullet->pos.X = current_xy->X + 3;
		bullet->pos.Y = current_xy->Y - 1;*/
		bullet->pos.X = current_xy->X + 2;
		bullet->pos.Y = current_xy->Y + 3;
		bullet->bullet_type = 1;//第幾種彈鏈
		bullet->direction = 2;//方向往下
		bullet->last_pnext = NULL;
		if (bullet_amount == 1)              //第一顆子彈
		{
			first_bullet = bullet;
			last_bullet = bullet;
		}
		else
		{
			bullet->last_pnext = last_bullet;//目前的節點 指向上一個得節點=上一個節點
			last_bullet->pnext = bullet;//上一個節點 指向得下一個節點=目前的節點
			last_bullet = bullet;       //假定目前的節點為最後一個
		}
		bullet->pnext = NULL;
	}
	else if (direction == 3)		//向左射
	{
		struct bullet_pos* bullet = (struct bullet_pos*)malloc(sizeof(struct bullet_pos));
		bullet_amount++;
		if (skillone == 1) {//skillone傷害增加
			bullet->damage = 2;
			mp--;
			if (mp == 0) {
				skillone = 0;
			}
		}
		else if (skillone == 0) {
			bullet->damage = 1;		//傷害設為1
		}
		bullet->pos.X = current_xy->X;
		bullet->pos.Y = current_xy->Y + 1;
		bullet->bullet_type = 1;//第幾種彈鏈
		bullet->direction = 3;//方向往左
		bullet->last_pnext = NULL;
		if (bullet_amount == 1)              //第一顆子彈
		{
			first_bullet = bullet;
			last_bullet = bullet;
		}
		else
		{
			bullet->last_pnext = last_bullet;//目前的節點 指向上一個得節點=上一個節點
			last_bullet->pnext = bullet;//上一個節點 指向得下一個節點=目前的節點
			last_bullet = bullet;       //假定目前的節點為最後一個
		}
		bullet->pnext = NULL;
	}
	else if (direction == 4)		//向右射
	{
		struct bullet_pos* bullet = (struct bullet_pos*)malloc(sizeof(struct bullet_pos));
		bullet_amount++;
		if (skillone == 1) {//skillone傷害增加
			bullet->damage = 2;
			mp--;
			if (mp == 0) {
				skillone = 0;
			}
		}
		else if (skillone == 0) {
			bullet->damage = 1;		//傷害設為1
		}
		/*bullet->pos.X = current_xy->X + 3;
		bullet->pos.Y = current_xy->Y - 1;*/
		bullet->pos.X = current_xy->X + 5;
		bullet->pos.Y = current_xy->Y + 1;
		bullet->bullet_type = 1;//第幾種彈鏈
		bullet->direction = 4;//方向往右
		bullet->last_pnext = NULL;
		if (bullet_amount == 1)              //第一顆子彈
		{
			first_bullet = bullet;
			last_bullet = bullet;
		}
		else
		{
			bullet->last_pnext = last_bullet;//目前的節點 指向上一個得節點=上一個節點
			last_bullet->pnext = bullet;//上一個節點 指向得下一個節點=目前的節點
			last_bullet = bullet;       //假定目前的節點為最後一個
		}
		bullet->pnext = NULL;
	}


}

void update_bullet_xy()//用來計算子彈每次移動得新位子
{
	if (first_bullet != NULL)
	{
		UPDATE_bullet_list(first_bullet);
	}
}
void PRINT_bullet_function(struct bullet_pos* first_bullet)
{
	struct bullet_pos* current_bullet = NULL;//用來讓鏈表run一遍的指針
	current_bullet = first_bullet;
	//if (current_bullet->last_pnext != NULL) {		//如果first不是真的first
	//	current_bullet = current_bullet->last_pnext;
	//	printf("還有ㄟ");
	//}
	while (current_bullet != NULL)
	{
		tmp_old_bullet = current_bullet->pos;
		//printf("印下一個");
		switch (current_bullet->direction)
		{
		case 1:	//上
			tmp_old_bullet.Y += 1;//先清除舊資料
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_old_bullet);
			printf("   ");
			tmp_old_bullet.Y -= 1;//打印新的位子
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_old_bullet);
			SetColor(11);
			if (rolechoice == 2) {
				printf("↑");
			}
			if (rolechoice == 1) {
				printf("｜");
			}
			break;
		case 2:	//下
			tmp_old_bullet.Y -= 1;//先清除舊資料
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_old_bullet);
			printf("  ");
			tmp_old_bullet.Y += 1;//打印新的位子
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_old_bullet);
			SetColor(11);
			if (rolechoice == 2) {
				printf("↓");
			}
			if (rolechoice == 1) {
				printf("｜");
			}
			break;
		case 3:	//左
			tmp_old_bullet.X -= 1;//先清除舊資料
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_old_bullet);
			printf("    ");
			tmp_old_bullet.X += 1;//打印新的位子
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_old_bullet);
			SetColor(11);
			if (rolechoice == 2) {
				printf("←");
			}
			if (rolechoice == 1) {
				printf("—");
			}
			break;
		case 4:	//右
			tmp_old_bullet.X -= 1;//先清除舊資料
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_old_bullet);
			printf("   ");
			tmp_old_bullet.X += 1;//打印新的位子
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_old_bullet);
			SetColor(11);
			if (rolechoice == 2) {
				printf("→");
			}
			if (rolechoice == 1) {
				printf("—");
			}
			break;
		}
		current_bullet = current_bullet->pnext;
	}
	SetColor(7);
}
void print_bullet()
{
	if (first_bullet != NULL)
	{
		PRINT_bullet_function(first_bullet);
	}
	/*if (first_bullet_2 != NULL)
	{
		PRINT_bullet_function(first_bullet_2);
	}
	if (first_bullet_3 != NULL)
	{
		PRINT_bullet_function(first_bullet_3);
	}*/
}
void print_all(COORD* current_xy)
{
	//PRINT_airplane(current_xy, weapon_choose);  //打印飛機
	if (bullet_amount >= 1)   //如果有子彈才打印
		print_bullet();
	/*printf_all_enemy();
	print_explosion();*/
}


//01/09	印出敵人霍特
void generate_holt()
{
	holt.pos.X = 75;
	holt.pos.Y = 14;
	holt.hp = 20;
	holt.damage = 1;
}
void print_holt()
{
	COORD tmp_pos;
	tmp_pos.X = holt.old_pos.X;
	tmp_pos.Y = holt.old_pos.Y;
	char Holt[3][12] = {
		"  ●",
		"o ▇  o§→",
		"︻┴ ︻",
	};
	SetColor(10);
	for (int i = 0; i < 3; i++) {
		tmp_pos.Y = holt.old_pos.Y + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_pos);

		printf("          ");
	}
	tmp_pos.X = holt.pos.X;
	for (int i = 0; i < 3; i++) {
		tmp_pos.Y = holt.pos.Y + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_pos);
		SetColor(7);
		printf("%s", Holt[i]);
	}
	holt.old_pos.X = holt.pos.X;
	holt.old_pos.Y = holt.pos.Y;
}

int update_holt(COORD* current_xy)
{
	if (/*count_main_while_time%2 ==*/ 1) {		//用來決定霍特的移動速度
		//我覺得霍特跑太慢，讓他一次跑兩步
		for (int i = 0; i < 2; i++) {
			if (invincible_time != 0) {		//如果在無敵期間
				invincible_time++;
			}
			if (invincible_time >= 25) {	//如果期間結束，把期間記數歸零，結束無敵

				invincible_time = 0;
			}
			if ((max(current_xy->X, holt.pos.X) - min(current_xy->X, holt.pos.X)) <= 8 && (max(current_xy->Y, holt.pos.Y) - min(current_xy->Y, holt.pos.Y)) <= 3) {
				if (invincible_time == 0) {		//如果不再無敵期間，進入無敵期間
					invincible_time++;
					health--;
				}
				return 0;
			}

			switch (rand() % 5)
			{
			case 0:
				if ((current_xy->X + 6) > holt.pos.X) {		//如果ㄚㄚ一一嘿嘿
					holt.pos.X++;
				}
				break;
			case 1:
				if ((current_xy->X - 6) < holt.pos.X) {		//如果ㄚㄚ一一嘿嘿
					holt.pos.X--;
				}
				break;
			case 2:
				if ((current_xy->Y + 3) > holt.pos.Y) {
					holt.pos.Y++;
				}
				break;
			case 3:
				if ((current_xy->Y - 3) < holt.pos.Y) {
					holt.pos.Y--;
				}
				break;
			default:
				break;
			}
		}
	}
}
