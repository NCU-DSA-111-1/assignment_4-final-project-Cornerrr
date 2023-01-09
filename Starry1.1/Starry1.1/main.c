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
void show_health();
void show_mp();
int keybord_control(COORD* current_xy);
void show_all_data();
void character(int i);
void print_character(COORD* current_xy, int i);
int choose_role();
int exceed_map(COORD* current_xy);
void story2_print();
int exceed_map1(COORD* current_xy);
void Holt_chat(COORD* current_xy);
void show_Holt_health(COORD* current_xy);

//2023/01/06�l�u�s�@
#define SHOOT_HOW_FAST 20			//�l�u�g�����W�v(�Ʀr�V�j�]�V�C
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
int bullet_amount = 0;  //�p��l�u�h�֭���`��b�@�_
struct bullet_pos* first_bullet = NULL;  //1���Z�����Y���w�A
struct bullet_pos* last_bullet = NULL;
COORD tmp_old_bullet;
int surplus_bullet = 20;
//2023/01/07 �ĤH�s�@(²��]�]�u�O���F���l�u�I���A�ثe���Hnidandan��ĤH�ݤl�u�|���|����
struct enermy holt;
void print_holt();
void generate_holt();
int update_holt(COORD* current_xy);


int count_main_while_time = 0;
int health = 6;
int mp = 7;
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
//�}�l�C��
void game_start() {
	bullet_amount = 0;//�ƾڪ�l��
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
		if (map1_agree == 1) {//�a�Ϥ@
			back_ground2();
			//story2_print();
			map1_agree = 0;
		}
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), time_xy);//�ɶ�
		printf("�ɶ� : %d", count_main_while_time);
		keybord_control(&current_xy);//��L����
		exceed_map(&current_xy);//��ɧP�w
		if (Holt_chat_agree == 1) {
			Holt_chat(&current_xy);
		}
		if (battle_agree == 1) {
			print_holt();
			show_Holt_health(&current_xy);
			update_holt(&current_xy);
		}
		if (map1_exceed_agree == 1) {
			exceed_map1(&current_xy);//�Ϥ@��ɧP�w
		}
		print_character(&current_xy, rolechoice);
		print_all(&current_xy);
		if ((bullet_amount) >= 1)
		{
			judge_bullet();//�P�_�O�_�W��ɭn����O����
			update_bullet_xy();
		}
		show_all_data();
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
void show_all_data() {
	show_health();
	show_mp();
}
//�����q
void show_health()
{
	int i;
	COORD health_pos;
	health_pos.X = 120;			//�������䪺�����I
	health_pos.Y = 17;
	COORD rim;
	COORD word;
	rim.X = health_pos.X - 2;
	rim.Y = health_pos.Y - 1;
	word.X = health_pos.X - 7;
	word.Y = health_pos.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), health_pos);//�����ª��M��
	printf("            ");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rim);
	printf("�z                �{");
	rim.Y += 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rim);
	printf("�|                �}");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), word);
	printf("HP:");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), health_pos);
	for (i = 0; i < health; i++)
	{
		SetColor(4);
		printf("�h");
	}
	/*SetColor(4);
	printf("8=====D");*/
	if (health == 0) {
		COORD text_pos;
		text_pos.X = 40;
		text_pos.Y = 24;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), text_pos);
		printf("�N�S: %s,�A�٬O�^�h�إЧa", name);
		Sleep(2000);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), text_pos);
		printf("                           ");
		current_xy->X = 72;
		current_xy->Y = 19;
		back_ground2();
		battle_agree = 0;
		Holt_chat_agree = 1;
		health = 6; //�w�]�令current_health
		mp = 10;
	}
	printf("\n");
	SetColor(7);
}
//�N�S��q
void show_Holt_health(COORD* current_xy)
{
	int i;
	COORD holt_health_pos;
	holt_health_pos.X = 24;			//�������䪺�����I
	holt_health_pos.Y = 3;
	COORD holt_rim;
	COORD holt_word;
	holt_rim.X = holt_health_pos.X - 2;
	holt_rim.Y = holt_health_pos.Y - 1;
	holt_word.X = holt_health_pos.X - 7;
	holt_word.Y = holt_health_pos.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), holt_health_pos);//�����ª��M��
	printf("                                             ");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), holt_rim);
	printf("�z                                         �{");
	holt_rim.Y += 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), holt_rim);
	printf("�|                                         �}");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), holt_word);
	printf("HOLT:");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), holt_health_pos);
	for (i = 0; i < holt.hp; i++)
	{
		SetColor(4);
		printf("�h");
	}
	if (holt.hp == 0) {
		COORD text_pos;
		text_pos.X = 40;
		text_pos.Y = 24;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), text_pos);
		printf("�N�S: %s,�����ܱo�����F�O", name);
		Sleep(2000);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), text_pos);
		printf("                           ");
		current_xy->X = 72;
		current_xy->Y = 19;
		back_ground2();
		map1_exceed_agree = 1;
		battle_agree = 0;
		holtchat = 2;
		Holt_chat_agree = 1;
		mp = 10;
	}
	SetColor(7);
}
//�����]�q
void show_mp()
{
	int i;
	COORD mp_pos;
	mp_pos.X = 120;			//�������䪺�����I
	mp_pos.Y = 21;
	COORD rim;
	COORD word;
	rim.X = mp_pos.X - 2;
	rim.Y = mp_pos.Y - 1;
	word.X = mp_pos.X - 7;
	word.Y = mp_pos.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mp_pos);//�����ª��M��
	printf("            ");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rim);
	printf("�z            �{");
	rim.Y += 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rim);
	printf("�|            �}");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), word);
	printf("MP:");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mp_pos);
	for (i = 0; i < mp; i++)
	{
		SetColor(3);
		printf("�h");
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
	printf("�P�P��������]�L�H�o���A");
	Sleep(2500);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("                         ");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("�ҥH���A");
	Sleep(1500);
	chat_pos.Y = chat_pos.Y + 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("�֦~�U�w�M�ߡA��W�ȵ{�A");
	Sleep(2500);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("                         ");
	chat_pos.Y = chat_pos.Y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("                         ");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("�µ۹k�ۭ��������ݡA");
	Sleep(1500);
	chat_pos.Y = chat_pos.Y + 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("�e�i�X�X");
	Sleep(2500);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("                         ");
	chat_pos.Y = chat_pos.Y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
	printf("                         ");
}
//�N�S���
void Holt_chat(COORD* current_xy) {
	if (current_xy->X >= 68 && current_xy->Y <= 19 && current_xy->X <= 85 && current_xy->Y >= 15) {
		COORD chat_pos;
		chat_pos.X = 13;
		chat_pos.Y = 4;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
		SetColor(7);
		printf("���U�ťն}�l���");
		if (GetAsyncKeyState(0x20)) {
			if (holtchat == 1) {
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                         ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("�N�S : %s ���j�F��", name);
				Sleep(2500);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                         ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("�N�S : ť�� ���ڬݬ�");
				Sleep(2500);
				chat_pos.Y += 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("       �A����O!");
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
				printf("�N�S : %s �ݨӮv��", name);
				Sleep(2500);
				chat_pos.Y += 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("       �w�g�S����i�H�ЧA���F");
				Sleep(2500);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                              ");
				chat_pos.Y -= 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                        ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("�N�S : �֨��a �µۧA���ؼ�...");
				Sleep(2500);
				chat_pos.Y += 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("        �A�w�g�i�H�F!");
				Sleep(2500);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                                 ");
				chat_pos.Y -= 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                                  ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("�N�S : ����,�o�ӬP������N���A�a");
				Sleep(2500);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                                  ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("�N�S : �۫H���|��A�����U��");
				Sleep(2500);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                                  ");
				SetColor(6);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("��o�P������");
				Sleep(2500);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("���ѼĤH�� ����|�ֿn�P�P����q");
				Sleep(2500);
				chat_pos.Y += 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("�ô��ɦ�q");
				Sleep(2500);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                 ");
				chat_pos.Y -= 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                                  ");
				health = 8;
				COORD health_pos;
				health_pos.X = 120;			//�������䪺�����I
				health_pos.Y = 17;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), health_pos);//�����ª��M��
				printf("            ");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), health_pos);
				for (int i = 0; i < health; i++)
				{
					SetColor(4);
					printf("�h");
				}
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("��q�w����");
				Sleep(2500);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
				printf("                  ");
				SetColor(7);
				Holt_chat_agree = 0;
			}
		}
	}
}
//��L����
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
	if (GetAsyncKeyState(0x45) && mp > 0) {
		skillone = 1;
	}
	if (GetAsyncKeyState(0x51)) {
		skillone = 0;
	}
	//2023/01/06�l�u��s_�h��V����
	if (battle_agree == 1) {
		if (count_space_key < SHOOT_HOW_FAST)		//�p�G�S����SOOT_HOW_FAST�N�[�@
			count_space_key++;
		if (GetAsyncKeyState(0x26))//��V��W����
		{
			if (count_space_key == SHOOT_HOW_FAST)		//��SHOOT_HOW_FAST�M�w�n�g�h��
			{
				if (mp >= 1)		//���ȩw���]�O�~�i�o�g?(
				{
					generate_bullet(current_xy, 1);   //�w�g�O���w�N���ΦA�ǻ��a�}
				}
				count_space_key = 0;
			}
			//count_space_key++;		//��o���ܼƧ��~��

		}
		else if (GetAsyncKeyState(0x28))//��V��U����
		{
			if (count_space_key == SHOOT_HOW_FAST)
			{
				if (mp >= 1)		//���ȩw���]�O�~�i�o�g?(
				{
					generate_bullet(current_xy, 2);   //�w�g�O���w�N���ΦA�ǻ��a�}
				}
				count_space_key = 0;
			}
			count_space_key++;

		}
		else if (GetAsyncKeyState(0x25))//��V�䥪����
		{
			if (count_space_key == SHOOT_HOW_FAST)
			{
				if (mp >= 1)		//���ȩw���]�O�~�i�o�g?(
				{
					generate_bullet(current_xy, 3);   //�w�g�O���w�N���ΦA�ǻ��a�}
				}
				count_space_key = 0;
			}
			count_space_key++;

		}
		else if (GetAsyncKeyState(0x27))//��V��k����
		{
			if (count_space_key == SHOOT_HOW_FAST)
			{
				if (mp >= 1)		//���ȩw���]�O�~�i�o�g?(
				{
					generate_bullet(current_xy, 4);   //�w�g�O���w�N���ΦA�ǻ��a�}
				}
				count_space_key = 0;
			}
			count_space_key++;

		}
	}
	if (w < 0 && d < 0 /*|| right < 0 && up < 0*/) //�k�W
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
	if (w < 0 && a < 0 /*|| left < 0 && up < 0*/) //���W
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
	if (d < 0 && s < 0 /*|| right < 0 && down < 0*/) //�k�U
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
	if (a < 0 && s < 0 /*|| left < 0 && down < 0*/) //���U
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
	if (GetAsyncKeyState(0x41) /*|| GetAsyncKeyState(0x25)*/) //��
	{
		current_xy->X -= 1;
		return 0;
	}
	if (GetAsyncKeyState(0x44) /*|| GetAsyncKeyState(0x27)*/)//�k
	{
		current_xy->X += 1;
		return 0;
	}
	if (GetAsyncKeyState(0x57) /*|| GetAsyncKeyState(0x26)*/)//�W
	{
		if (count_up_key == 2)
		{
			current_xy->Y -= 1;
			count_up_key = 0;
		}
		count_up_key++;
		return 0;
	}
	if (GetAsyncKeyState(0x53)/* || GetAsyncKeyState(0x28)*/)//�U
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
//���¾�~
int choose_role() {
	COORD choose_role_text;
	choose_role_text.X = 40;
	choose_role_text.Y = 24;
	char rolenum[20];
	int role_num;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), choose_role_text);
	SetColor(9);
	printf("�п��¾�~...");
	Sleep(2000);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), choose_role_text);
	printf("5�����U1.�u�Ԥh�v; ���U2.�u�C�L�v:  ");
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
//2023/1/5�ߤW�A�u����ɧP�w
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
	return 0;
}
//�a�Ϥ@��ɧP�w
int exceed_map1(COORD* current_xy) {
	if (current_xy->Y > 22) {
		current_xy->Y = 22;
	}
	if (current_xy->Y < 16) {
		current_xy->Y = 16;
	}
	for (int i = 0;i < 25;i++) {
		if ((current_xy->X == (3 + i)) && (current_xy->Y == 21)) {
			current_xy->X = (3 + i);
			current_xy->Y = 22;
		}
	}
	for (int i = 0;i < 6;i++) {
		if ((current_xy->X == 28) && (current_xy->Y == (21 - i))) {
			current_xy->X = 29;
			current_xy->Y = (21 - i);
		}
	}
	for (int i = 0;i < 3;i++) {
		if ((current_xy->X == 69) && (current_xy->Y == (18 - i))) {
			current_xy->X = 68;
			current_xy->Y = (18 - i);
		}
	}
	for (int i = 0;i < 16;i++) {
		if ((current_xy->X == (75 + i)) && (current_xy->Y == 18)) {
			current_xy->X = (75 + i);
			current_xy->Y = 19;
		}
	}
	for (int i = 0;i < 3;i++) {
		if ((current_xy->X == 89) && (current_xy->Y == (21 - i))) {
			current_xy->X = 88;
			current_xy->Y = (21 - i);
		}
	}
	for (int i = 0;i < 25;i++) {
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
	if (count_main_while_time != 1)  //�p�G�O�Ĥ@���j�� �N���L�����ª��H
	{
		for (int i = 0; i < 3; i++)
		{
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), old_character_pos);
			printf("      ");
			old_character_pos.Y += 1;
		}
	}
	old_character_pos = xy;
	if (invincible_time != 0) {
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
//2023/01/06 �l�u�s�@
void free_bullet_function(struct bullet_pos** current_bullet)
{
	COORD xy = (*current_bullet)->pos;
	xy.Y += 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
	printf(" ");
	if ((*current_bullet)->last_pnext == NULL && (*current_bullet)->pnext == NULL)   //���p�T�Ӽu��[�_�ӥu���@��
	{
		First_Node_of_All_bullet = NULL;
		last_Node_of_All_bullet = NULL;
	}
	else if ((*current_bullet)->last_pnext == NULL && (*current_bullet)->pnext != NULL)  //�T�ӥH�W�Ĥ@��
	{
		First_Node_of_All_bullet = (*current_bullet)->pnext;
		First_Node_of_All_bullet->last_pnext = NULL;
	}
	else if ((*current_bullet)->last_pnext != NULL && (*current_bullet)->pnext == NULL) //�T�ӥH�W �̫�@��
	{
		(*current_bullet)->last_pnext->pnext = NULL;
		last_Node_of_All_bullet = (*current_bullet)->last_pnext;
		last_Node_of_All_bullet->pnext = NULL;
	}
	else
	{
		(*current_bullet)->last_pnext->pnext = (*current_bullet)->pnext; //�Ĥ@�ӫ��V�ĤT��
		(*current_bullet)->pnext->last_pnext = (*current_bullet)->last_pnext;//�ĤT�ӫ��V�Ĥ@��
	}
}


//2023/01/09�s�W����I�����
//�Ω�P�_���
void JUDGE_bullet_function(struct bullet_pos** first_bullet, int* bullet_amount)  //�ѩ�|���s���ܫ��w���V �ҥH�ݭn�ΤG�ū��w �P�_�l�u�O�_�W�L���
{
	struct bullet_pos* current_bullet = NULL;//�Ψ������run�@�M�����w
	struct bullet_pos* tmp = NULL;
	current_bullet = (*first_bullet);
	int condition = 0;						//�S�I�� = 0, ���I����� = 1, ���I���ĤH = 2;

	while (current_bullet != NULL)
	{
		condition = 0;		//�C���O�o�k�s
		if (holt.pos.X + 10 >= current_bullet->pos.X && current_bullet->pos.X >= holt.pos.X - 2 && holt.pos.Y + 3 >= current_bullet->pos.Y && current_bullet->pos.Y >= holt.pos.Y - 1) {		//����H
			condition = 2;
			holt.hp -= current_bullet->damage;
		}
		else if (current_bullet->pos.Y <= 1 || current_bullet->pos.X <= 3 || current_bullet->pos.Y >= 26 || current_bullet->pos.X >= 106) {	//������
			condition = 1;
		}
		//2023/01/07�ĤH�I���P�_(�ثe���N�S��ĤH
		if (condition != 0)  //�p�G�W�L��ɩμ���ĤH
		{
			struct bullet_pos* ready_to_free = NULL;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current_bullet->pos);
			printf("  ");
			ready_to_free = current_bullet;
			if (current_bullet->last_pnext == NULL && current_bullet->pnext == NULL)//�p�G�O�̫�@�o�l�u �N���Y�l�u���VNULL
			{
				current_bullet = NULL;			//���X
				*first_bullet = NULL;
				*bullet_amount = 0;             //�S���l�u�F

			}
			else if (current_bullet->last_pnext == NULL && current_bullet->pnext != NULL)
			{
				(*first_bullet) = current_bullet->pnext;   //���ĤG���l�u ���Ĥ@��l�u
				(*first_bullet)->last_pnext = NULL;      //�]���ĤG���l�u �ܦ��Ĥ@���F �ҥH�n����V�W�@�Ӹ`�I���w ���s���VNULL
				free(ready_to_free);                     //��Ĥ@��l�u���񤺦s
				*bullet_amount -= 1;                    //�l�u�֤@��
				current_bullet = NULL;		//���X
			}
			else if (current_bullet->last_pnext != NULL && current_bullet->pnext != NULL)
			{
				tmp = current_bullet->last_pnext;
				tmp->pnext = current_bullet->pnext; //�Ĥ@�ӫ��V�ĤT��
				current_bullet = current_bullet->pnext;
				current_bullet->last_pnext = tmp;//�ĤT�ӫ��V�Ĥ@��
				*bullet_amount -= 1;

				free(ready_to_free);
			}
			else if (current_bullet->last_pnext != NULL && current_bullet->pnext == NULL)
			{
				tmp = current_bullet->last_pnext;
				tmp->pnext = NULL;
				current_bullet = NULL;	//���X
				*bullet_amount -= 1;
				free(ready_to_free);
			}
		}
		else {
			current_bullet = current_bullet->pnext;
		}

	}
}

void judge_bullet()//�P�_�l�u�ϧ_�W�X��� �Y�W�X�h���񱼰O����
{
	if (first_bullet != NULL)
	{
		JUDGE_bullet_function(&first_bullet, &bullet_amount);
	}

}
void UPDATE_bullet_list(struct bullet_pos* first_point) //��s�l�u�y�СA���L���S�w�a��]
{
	struct bullet_pos* current_bullet = NULL;//�Ψ������run�@�M�����w
	current_bullet = first_point;
	while (current_bullet != NULL)
	{

		switch (current_bullet->direction)
		{
		case 1:
			current_bullet->pos.Y -= 1;		//�V�W�]
			break;
		case 2:
			current_bullet->pos.Y += 1;		//�V�U�]
			break;
		case 3:
			current_bullet->pos.X -= 1;		//�V���]
			break;
		case 4:
			current_bullet->pos.X += 1;		//�V�k�]

			break;
		}
		current_bullet = current_bullet->pnext;

	}
}

void generate_bullet(COORD* current_xy, int direction)
{
	if (direction == 1)		//�V�W�g
	{
		struct bullet_pos* bullet = (struct bullet_pos*)malloc(sizeof(struct bullet_pos));
		bullet_amount++;
		bullet->pos.X = current_xy->X + 2;
		bullet->pos.Y = current_xy->Y - 2;
		bullet->bullet_type = 1;//�ĴX�ؼu��
		bullet->direction = 1;//��V���W
		if (skillone == 1) {//skillone�ˮ`�W�[
			bullet->damage = 2;
			mp--;
			if (mp == 0) {
				skillone = 0;
			}
		}
		else if (skillone == 0) {
			bullet->damage = 1;		//�ˮ`�]��1
		}		//�ˮ`�]��1
		bullet->last_pnext = NULL;
		if (bullet_amount == 1)              //�Ĥ@���l�u
		{
			first_bullet = bullet;
			last_bullet = bullet;
		}
		else
		{
			bullet->last_pnext = last_bullet;//�ثe���`�I ���V�W�@�ӱo�`�I=�W�@�Ӹ`�I
			last_bullet->pnext = bullet;//�W�@�Ӹ`�I ���V�o�U�@�Ӹ`�I=�ثe���`�I
			last_bullet = bullet;       //���w�ثe���`�I���̫�@��
		}
		bullet->pnext = NULL;
	}
	else if (direction == 2)		//�V�U�g
	{
		struct bullet_pos* bullet = (struct bullet_pos*)malloc(sizeof(struct bullet_pos));
		bullet_amount++;
		if (skillone == 1) {//skillone�ˮ`�W�[
			bullet->damage = 2;
			mp--;
			if (mp == 0) {
				skillone = 0;
			}
		}
		else if (skillone == 0) {
			bullet->damage = 1;		//�ˮ`�]��1
		}
		/*bullet->pos.X = current_xy->X + 3;
		bullet->pos.Y = current_xy->Y - 1;*/
		bullet->pos.X = current_xy->X + 2;
		bullet->pos.Y = current_xy->Y + 3;
		bullet->bullet_type = 1;//�ĴX�ؼu��
		bullet->direction = 2;//��V���U
		bullet->last_pnext = NULL;
		if (bullet_amount == 1)              //�Ĥ@���l�u
		{
			first_bullet = bullet;
			last_bullet = bullet;
		}
		else
		{
			bullet->last_pnext = last_bullet;//�ثe���`�I ���V�W�@�ӱo�`�I=�W�@�Ӹ`�I
			last_bullet->pnext = bullet;//�W�@�Ӹ`�I ���V�o�U�@�Ӹ`�I=�ثe���`�I
			last_bullet = bullet;       //���w�ثe���`�I���̫�@��
		}
		bullet->pnext = NULL;
	}
	else if (direction == 3)		//�V���g
	{
		struct bullet_pos* bullet = (struct bullet_pos*)malloc(sizeof(struct bullet_pos));
		bullet_amount++;
		if (skillone == 1) {//skillone�ˮ`�W�[
			bullet->damage = 2;
			mp--;
			if (mp == 0) {
				skillone = 0;
			}
		}
		else if (skillone == 0) {
			bullet->damage = 1;		//�ˮ`�]��1
		}
		bullet->pos.X = current_xy->X;
		bullet->pos.Y = current_xy->Y + 1;
		bullet->bullet_type = 1;//�ĴX�ؼu��
		bullet->direction = 3;//��V����
		bullet->last_pnext = NULL;
		if (bullet_amount == 1)              //�Ĥ@���l�u
		{
			first_bullet = bullet;
			last_bullet = bullet;
		}
		else
		{
			bullet->last_pnext = last_bullet;//�ثe���`�I ���V�W�@�ӱo�`�I=�W�@�Ӹ`�I
			last_bullet->pnext = bullet;//�W�@�Ӹ`�I ���V�o�U�@�Ӹ`�I=�ثe���`�I
			last_bullet = bullet;       //���w�ثe���`�I���̫�@��
		}
		bullet->pnext = NULL;
	}
	else if (direction == 4)		//�V�k�g
	{
		struct bullet_pos* bullet = (struct bullet_pos*)malloc(sizeof(struct bullet_pos));
		bullet_amount++;
		if (skillone == 1) {//skillone�ˮ`�W�[
			bullet->damage = 2;
			mp--;
			if (mp == 0) {
				skillone = 0;
			}
		}
		else if (skillone == 0) {
			bullet->damage = 1;		//�ˮ`�]��1
		}
		/*bullet->pos.X = current_xy->X + 3;
		bullet->pos.Y = current_xy->Y - 1;*/
		bullet->pos.X = current_xy->X + 5;
		bullet->pos.Y = current_xy->Y + 1;
		bullet->bullet_type = 1;//�ĴX�ؼu��
		bullet->direction = 4;//��V���k
		bullet->last_pnext = NULL;
		if (bullet_amount == 1)              //�Ĥ@���l�u
		{
			first_bullet = bullet;
			last_bullet = bullet;
		}
		else
		{
			bullet->last_pnext = last_bullet;//�ثe���`�I ���V�W�@�ӱo�`�I=�W�@�Ӹ`�I
			last_bullet->pnext = bullet;//�W�@�Ӹ`�I ���V�o�U�@�Ӹ`�I=�ثe���`�I
			last_bullet = bullet;       //���w�ثe���`�I���̫�@��
		}
		bullet->pnext = NULL;
	}


}

void update_bullet_xy()//�Ψӭp��l�u�C�����ʱo�s��l
{
	if (first_bullet != NULL)
	{
		UPDATE_bullet_list(first_bullet);
	}
}
void PRINT_bullet_function(struct bullet_pos* first_bullet)
{
	struct bullet_pos* current_bullet = NULL;//�Ψ������run�@�M�����w
	current_bullet = first_bullet;
	//if (current_bullet->last_pnext != NULL) {		//�p�Gfirst���O�u��first
	//	current_bullet = current_bullet->last_pnext;
	//	printf("�٦���");
	//}
	while (current_bullet != NULL)
	{
		tmp_old_bullet = current_bullet->pos;
		//printf("�L�U�@��");
		switch (current_bullet->direction)
		{
		case 1:	//�W
			tmp_old_bullet.Y += 1;//���M���¸��
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_old_bullet);
			printf("   ");
			tmp_old_bullet.Y -= 1;//���L�s����l
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_old_bullet);
			SetColor(11);
			if (rolechoice == 2) {
				printf("��");
			}
			if (rolechoice == 1) {
				printf("�U");
			}
			break;
		case 2:	//�U
			tmp_old_bullet.Y -= 1;//���M���¸��
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_old_bullet);
			printf("  ");
			tmp_old_bullet.Y += 1;//���L�s����l
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_old_bullet);
			SetColor(11);
			if (rolechoice == 2) {
				printf("��");
			}
			if (rolechoice == 1) {
				printf("�U");
			}
			break;
		case 3:	//��
			tmp_old_bullet.X -= 1;//���M���¸��
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_old_bullet);
			printf("    ");
			tmp_old_bullet.X += 1;//���L�s����l
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_old_bullet);
			SetColor(11);
			if (rolechoice == 2) {
				printf("��");
			}
			if (rolechoice == 1) {
				printf("�X");
			}
			break;
		case 4:	//�k
			tmp_old_bullet.X -= 1;//���M���¸��
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_old_bullet);
			printf("   ");
			tmp_old_bullet.X += 1;//���L�s����l
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tmp_old_bullet);
			SetColor(11);
			if (rolechoice == 2) {
				printf("��");
			}
			if (rolechoice == 1) {
				printf("�X");
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
	//PRINT_airplane(current_xy, weapon_choose);  //���L����
	if (bullet_amount >= 1)   //�p�G���l�u�~���L
		print_bullet();
	/*printf_all_enemy();
	print_explosion();*/
}


//01/09	�L�X�ĤH�N�S
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
		"  ��",
		"o �h  o����",
		"�k�r �k",
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
	if (/*count_main_while_time%2 ==*/ 1) {		//�ΨӨM�w�N�S�����ʳt��
		//��ı�o�N�S�]�ӺC�A���L�@���]��B
		for (int i = 0; i < 2; i++) {
			if (invincible_time != 0) {		//�p�G�b�L�Ĵ���
				invincible_time++;
			}
			if (invincible_time >= 25) {	//�p�G���������A������O���k�s�A�����L��

				invincible_time = 0;
			}
			if ((max(current_xy->X, holt.pos.X) - min(current_xy->X, holt.pos.X)) <= 8 && (max(current_xy->Y, holt.pos.Y) - min(current_xy->Y, holt.pos.Y)) <= 3) {
				if (invincible_time == 0) {		//�p�G���A�L�Ĵ����A�i�J�L�Ĵ���
					invincible_time++;
					health--;
				}
				return 0;
			}

			switch (rand() % 5)
			{
			case 0:
				if ((current_xy->X + 6) > holt.pos.X) {		//�p�G�����@�@�K�K
					holt.pos.X++;
				}
				break;
			case 1:
				if ((current_xy->X - 6) < holt.pos.X) {		//�p�G�����@�@�K�K
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
