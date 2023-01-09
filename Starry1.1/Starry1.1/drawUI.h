#define STORY_TEXT_TIME 2500
#define GROUND_Y_POSITION 20
void show_meteor();
void story_text();
void back_ground1();
void back_ground2();
void story_print();
void battle_print();
char name[20];
int rolechoice;
void story_print() {
	for (int i = 1; i <= 28; i++) {
		for (int j = 1; j <= 110; j++) {
			if (i == 1 || i == 28) {
				if (j != 1) {
					printf("=");
				}
				else {
					printf(" ");
				}
			}
			else {
				if (j == 1 || j == 110) {
					printf("||");
				}
				else {
					printf(" ");
				}
			}
		}
		printf("\n");

	}
	printf("Name : ");
	scanf_s("%s", name, 19);
	back_ground1();



	/*story_text();*/
}

void story_text()
{
	COORD text_pos;
	text_pos.X = 40;
	text_pos.Y = 24;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), text_pos);
	SetColor(9);
	printf("天空降下了黑夜的帷幕...");
	Sleep(STORY_TEXT_TIME);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), text_pos);
	printf("                                                           ");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), text_pos);
	printf("維爾城邊一棵樹旁...");
	Sleep(STORY_TEXT_TIME);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), text_pos);
	printf("一個少年眺望著滿天的星斗...");
	Sleep(STORY_TEXT_TIME);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), text_pos);
	printf("倏忽之間，一道流星劃過..");
	show_meteor();							//印出雨時拉
	SetColor(9);
	Sleep(STORY_TEXT_TIME - 1500);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), text_pos);
	printf("那天之後，從此夜晚再無光明，進入了無盡的黑暗中!");
	Sleep(STORY_TEXT_TIME + 1500);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), text_pos);
	printf("                                                           ");
	SetColor(7);

}

void back_ground1()
{
	int i;
	char mountant[15][100] = { "              /\\                              ^                            ",
							 "             /   \\                          /   \\                    ",
							 "            /      \\                      /       \\          ",
							 "           /         \\                   /          \\                   ",
							 "          /           \\                /              \\    ",
							 "         /             \\             /                  \\    ",
							 "        /               \\          /                     \\                 ",
							 "       /                 \\       /                        \\                ",
							 "      /                   \\    /                            \\               ",
							 "     /                     \\ /                                \\             ",
							 "    /                       \\                                   \\          ",
							 "   /                         \\                                    \\        ",
							 "  /                           \\                                    \\       ",
							 " /                                                                   \\    ",
							 "/                                                                      \\  " };
	COORD ground_pos;
	//印出地面
	ground_pos.X = 2;
	ground_pos.Y = GROUND_Y_POSITION;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ground_pos);
	SetColor(3);
	for (i = 0; i < 108; i++) {
		printf("=");
	}
	SetColor(7);
	//印出山
	for (i = 0; i < 15; i++) {
		ground_pos.X = 4;
		ground_pos.Y = GROUND_Y_POSITION - 15 + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ground_pos);
		SetColor(2);
		printf("%s", mountant[i]);
		SetColor(7);
	}
	//印星星
	COORD star_pos;
	star_pos.X = 81;
	star_pos.Y = 4;
	char star[4][25] = {
		"★",
		"       ★",
		"                   ★",
		"            ★",
	};
	for (i = 0; i < 4; i++) {
		star_pos.Y = GROUND_Y_POSITION - 16 + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), star_pos);
		SetColor(6);
		printf("%s", star[i]);
		SetColor(7);
	}
	//印出樹
	ground_pos.X = 8;
	ground_pos.Y = GROUND_Y_POSITION - 8;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ground_pos);
	SetColor(10);
	printf("      ● ");
	ground_pos.X = 8;
	ground_pos.Y = GROUND_Y_POSITION - 7;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ground_pos);
	printf("    ●●●");
	ground_pos.X = 8;
	ground_pos.Y = GROUND_Y_POSITION - 6;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ground_pos);
	printf("  ●●●●●");
	ground_pos.X = 8;
	ground_pos.Y = GROUND_Y_POSITION - 5;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ground_pos);
	printf("●●●●●●●");
	ground_pos.X = 10;
	ground_pos.Y = GROUND_Y_POSITION - 4;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ground_pos);
	SetColor(7);
	printf("  |   |   ");
	ground_pos.X = 10;
	ground_pos.Y = GROUND_Y_POSITION - 3;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ground_pos);
	printf(" | |  |●");
	ground_pos.X = 10;
	ground_pos.Y = GROUND_Y_POSITION - 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ground_pos);
	printf("| |   | |-");
	ground_pos.X = 9;
	ground_pos.Y = GROUND_Y_POSITION - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ground_pos);
	printf("|  ||   \\\\\\");
}
void back_ground2() {
	//去背
	COORD ground_pos;
	ground_pos.X = 2;
	ground_pos.Y = 2;
	for (int i = 0;i < 25;i++) {
		ground_pos.Y = GROUND_Y_POSITION - 18 + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ground_pos);
		printf("                                                                                                            ");
	}
	//印幹
	COORD trunk_pos;
	trunk_pos.X = 2;
	trunk_pos.Y = 2;
	char map1_trunk[19][7] = {
		"|    |",
		"| |  |",
		"| |  |",
		"| |  |",
		"|| | |",
		"|| | |",
		"|  | |",
		"||   |",
		"||  ||",
		"||  ||",
		"|   ||",
		"|  |||",
		"|  |||",
		"|  | |",
		"| || |",
		"| || |",
		"| || |",
		"| |  |",
		"|____|",
	};
	for (int i = 0;i < 19;i++) {
		trunk_pos.Y = GROUND_Y_POSITION - 19 + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), trunk_pos);
		SetColor(6);
		printf("%s", map1_trunk[i]);
		SetColor(7);
	}
	//印路2023/1/6
	COORD road_pos;
	road_pos.X = 2;
	road_pos.Y = GROUND_Y_POSITION + 5;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), road_pos);
	SetColor(3);
	for (int i = 0;i < 54;i++) {
		printf("﹎");
	}
	road_pos.X = 2;
	road_pos.Y = GROUND_Y_POSITION + 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), road_pos);
	for (int i = 0;i < 14;i++) {
		printf("﹊");
	}
	road_pos.X = 28;
	for (int i = 0;i < 6;i++) {
		road_pos.Y = GROUND_Y_POSITION - i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), road_pos);
		printf("｜");
	}
	road_pos.X = 28;
	road_pos.Y = GROUND_Y_POSITION - 6;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), road_pos);
	for (int i = 0;i < 13;i++) {
		printf("﹎");
	}
	road_pos.X = 78;
	road_pos.Y = GROUND_Y_POSITION - 6;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), road_pos);
	for (int i = 0;i < 4;i++) {
		printf("﹎");
	}
	road_pos.X = 84;
	for (int i = 0;i < 4;i++) {
		road_pos.Y = GROUND_Y_POSITION - 5 + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), road_pos);
		printf("｜");
	}
	road_pos.X = 84;
	road_pos.Y = GROUND_Y_POSITION - 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), road_pos);
	printf("└");
	for (int i = 1;i < 10;i++) {
		printf("─");
	}
	printf("┐ ");
	road_pos.X = 94;
	for (int i = 0;i < 2;i++) {
		road_pos.Y = GROUND_Y_POSITION - 1 + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), road_pos);
		printf("｜");
	}
	road_pos.X = 94;
	road_pos.Y = GROUND_Y_POSITION + 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), road_pos);
	for (int i = 0;i < 8;i++) {
		printf("﹊");
	}
	//印對話框2023/1/6
	COORD chat_pos;
	chat_pos.X = 8;
	chat_pos.Y = 2;
	char chat_frame[8][45] = {
		"┌———————————————————┐ ",
		"｜ 『                                  ｜",
		"｜                                     ｜",
		"｜                                     ｜",
		"｜                                     ｜",
		"｜                                     ｜",
		"｜                                  』 ｜",
		"└———————————————————┘ ",
	};
	for (int i = 0;i < 8;i++) {
		chat_pos.Y = GROUND_Y_POSITION - 19 + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), chat_pos);
		SetColor(4);
		printf("%s", chat_frame[i]);
	}
	//印房2023/01/06 09:23
	COORD house_pos;
	house_pos.X = 55;
	char house[12][29] = {
		"        ╱ ￣￣￣╲ ",
		"      ╱ ｜￣║ ￣｜╲ ",
		"    ╱   ｜—╬ —｜  ╲ ",
		"  ╱     ｜ˍ║ ˍ｜    ╲ ",
		"╱ˍˍˍˍˍˍˍˍˍˍˍ ╲ ",
		"｜｜                  ｜｜",
		"｜｜                  ｜｜",
		"｜｜    ｜￣￣￣｜    ｜｜",
		"｜｜    ｜ ｜   ｜    ｜｜",
		"｜｜    ｜ ｜ ｜｜    ｜｜",
		"｜｜    ｜    ｜｜    ｜｜",
		"｜｜ˍˍ｜ˍˍˍ｜ˍˍ｜｜",
	};
	for (int i = 0;i < 12;i++) {
		house_pos.Y = GROUND_Y_POSITION - 16 + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), house_pos);
		SetColor(6);
		printf("%s", house[i]);
	}
	//印樹
	COORD tree_pos;
	tree_pos.X = 99;
	char tree[17][20] = {
		"      ╱ ",
		"    ╱ ",
		"    ╲ ",
		"   ∕ ╲ ",
		"  ∕    ╲ ",
		"  ╲       ",
		"    ╲     ",
		"  ∕  ╲   ",
		" ∕     ╲ ",
		"   ╲     ",
		"     ◣    ",
		"     █◣╱ ",
		"      ╱ ",
		"      ╲ ",
		"      ╱ ╲ ",
		"    ∠ ",
		"      ◣ ",
	};
	for (int i = 0;i < 17;i++) {
		tree_pos.Y = GROUND_Y_POSITION - 16 + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), tree_pos);
		SetColor(2);
		printf("%s", tree[i]);
	}
	//印叢
	COORD clump_pos;
	clump_pos.X = 28;
	char clump[3][35] = {
		"╭  ─  ─  ─  ╮─  ─  ─  ╮ ",
		"｜          ｜        ｜ ",
		"╰  ─  ─  ─  ╯─  ─  ─  ╯ ",
	};
	for (int i = 0;i < 3;i++) {
		clump_pos.Y = GROUND_Y_POSITION - 10 + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), clump_pos);
		SetColor(10);
		printf("%s", clump[i]);
	}
	//印霍特
	COORD Holt_pos;
	Holt_pos.X = 75;
	char Holt[3][12] = {
		"  ●",
		"o ▇  o§→",
		"︻┴ ︻",
	};
	for (int i = 0;i < 3;i++) {
		Holt_pos.Y = GROUND_Y_POSITION - 4 + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Holt_pos);
		SetColor(7);
		printf("%s", Holt[i]);
	}
}
void battle_print() {
	//去背
	COORD ground_pos;
	ground_pos.X = 2;
	ground_pos.Y = 2;
	for (int i = 0;i < 25;i++) {
		ground_pos.Y = GROUND_Y_POSITION - 19 + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ground_pos);
		printf("                                                                                                            ");
	}
	//印霍特
	COORD Holt_pos;
	Holt_pos.X = 75;
	char Holt[3][12] = {
		"  ●",
		"o ▇  o§→",
		"︻┴ ︻",
	};
	for (int i = 0;i < 3;i++) {
		Holt_pos.Y = GROUND_Y_POSITION - 6 + i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Holt_pos);
		SetColor(7);
		printf("%s", Holt[i]);
	}
}
//這是流星不用懷疑
void show_meteor()
{
	COORD meteor_pos;
	meteor_pos.X = 90;
	meteor_pos.Y = GROUND_Y_POSITION - 8;
	COORD next_meteor_pos;
	next_meteor_pos.X = meteor_pos.X - 1;
	next_meteor_pos.Y = meteor_pos.Y + 1;

	SetColor(6);
	for (int i = 0; i < 7; i++) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), meteor_pos);
		printf(" //     ");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), next_meteor_pos);
		printf("★");
		Sleep(300);
		meteor_pos.X = meteor_pos.X - 2;
		meteor_pos.Y = meteor_pos.Y + 1;
		next_meteor_pos.X = next_meteor_pos.X - 2;
		next_meteor_pos.Y = next_meteor_pos.Y + 1;

	}
	SetColor(7);
	meteor_pos.X = 90;
	meteor_pos.Y = GROUND_Y_POSITION - 8;
	for (int i = 0; i < 8; i++) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), meteor_pos);
		printf("      ");
		meteor_pos.X = meteor_pos.X - 2;
		meteor_pos.Y = meteor_pos.Y + 1;

	}
}

void character(int i)
{

	if (i == 0)
		printf("  ●↓");
	else if (i == 1)
		printf("※▇ ┘");
	else if (i == 2)
		printf("︻┴ ︻");
	else if (i == 3)
		printf("↑●");
	else if (i == 4)
		printf("└ ▇ <}");//→
	else if (i == 5)
		printf("︻┴ ︻");
}
