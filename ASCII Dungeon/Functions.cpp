#include <stdio.h>
#include <stdlib.h> 
#include <conio.h>
#include <windows.h>
#include "Core.h"


//COLORS LIST
//0: Black
//1: Blue
//2: Green
//3: Cyan
//4: Red
//5: Purple
//6: Yellow (Dark)
//7: Default white
//8: Gray/Grey
//9: Bright blue
//10: Brigth green
//11: Bright cyan
//12: Bright red
//13: Pink/Magenta
//14: Yellow
//15: Bright white
//Numbers after 15 include background colors

void Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void debug(int i) {
	Color(7);
	printf("%d\n", i);
	Sleep(1000);
}

void printslow(const char Input[], int Delay)
{
	for (int i = 0; i < strlen(Input); i++) {
		printf("%c", Input[i]);
		Sleep(Delay);
	}
}

void PrintScreen(WorldState& W, PlayerState& P)
{
	int y = 0;
	int x = 0;
	int tab = 0;
	//Sets correct verticle spacing 
	for (int i = 0; i < 9; i++) printf("\n");
	//First For-Loop iterates off x values and adds a new line after the second loop
	//Second For-Loop interates off y values and prints the current x and y values of both loops which should be the same at all times 
	for (x = 0; x < W.Rooms[P.CRI].MaxGrid; x++)
	{
		for (y = 0; y < W.Rooms[P.CRI].MaxGrid; y++)
		{
			// adds correct horizontal spacing 
			while (tab < 5)
			{
				printf("\t");
				tab++;
			}
			// SET COLOR Based on value of current entry being printed 
			if (W.Rooms[P.CRI].Grid[x][y] == W.v || W.Rooms[P.CRI].Grid[x][y] == W.h || W.Rooms[P.CRI].Grid[x][y] == W.c || W.Rooms[P.CRI].Grid[x][y] == W.C || W.Rooms[P.CRI].Grid[x][y] == W.l || W.Rooms[P.CRI].Grid[x][y] == W.L || W.Rooms[P.CRI].Grid[x][y] == W.T || W.Rooms[P.CRI].Grid[x][y] == W.t || W.Rooms[P.CRI].Grid[x][y] == W.F || W.Rooms[P.CRI].Grid[x][y] == W.f) Color(0);
			if (W.Rooms[P.CRI].Grid[x][y] == P.E) Color(0);
			if (W.Rooms[P.CRI].Grid[x][y] == W.D) Color(0);
			if (W.Rooms[P.CRI].Grid[x][y] == W.LD) Color(0);
			
			// If the currently printed out corrodinate is a wall or door check if it matches a corrodinate set from the echo list
			// If yes set the color to White or Blue accordingly
			if (W.Rooms[P.CRI].Grid[x][y] == W.D || W.Rooms[P.CRI].Grid[x][y] == W.LD || W.Rooms[P.CRI].Grid[x][y] == W.v || W.Rooms[P.CRI].Grid[x][y] == W.h || W.Rooms[P.CRI].Grid[x][y] == P.E ||  W.Rooms[P.CRI].Grid[x][y] == W.c || W.Rooms[P.CRI].Grid[x][y] == W.C || W.Rooms[P.CRI].Grid[x][y] == W.l || W.Rooms[P.CRI].Grid[x][y] == W.L || W.Rooms[P.CRI].Grid[x][y] == W.T || W.Rooms[P.CRI].Grid[x][y] == W.t || W.Rooms[P.CRI].Grid[x][y] == W.F || W.Rooms[P.CRI].Grid[x][y] == W.f) {
				for (int i = 0; i < W.Rooms[P.CRI].ScannedSpaces.size(); i++) {
					if ((x == W.Rooms[P.CRI].ScannedSpaces[i][0]) && (y == W.Rooms[P.CRI].ScannedSpaces[i][1])) {
						if (W.Rooms[P.CRI].Grid[x][y] == W.v || W.Rooms[P.CRI].Grid[x][y] == W.h) Color(7);
						else if(W.Rooms[P.CRI].Grid[x][y] == W.c || W.Rooms[P.CRI].Grid[x][y] == W.C || W.Rooms[P.CRI].Grid[x][y] == W.l || W.Rooms[P.CRI].Grid[x][y] == W.L) Color(7);
						else if(W.Rooms[P.CRI].Grid[x][y] == W.T || W.Rooms[P.CRI].Grid[x][y] == W.t || W.Rooms[P.CRI].Grid[x][y] == W.F || W.Rooms[P.CRI].Grid[x][y] == W.f) Color(7);
						else if (W.Rooms[P.CRI].Grid[x][y] == W.D) Color(6);
						else if (W.Rooms[P.CRI].Grid[x][y] == W.LD) Color(14);
						//Enemy Color fades 
						else if (W.Rooms[P.CRI].Grid[x][y] == P.E) {
							for (int n = 0; n < W.Rooms[P.CRI].Enemies.size(); n++) {
								if ((x == W.Rooms[P.CRI].Enemies[n].X) && (y == W.Rooms[P.CRI].Enemies[n].Y)) {
									if (W.Rooms[P.CRI].Enemies[n].fading == 2) Color(4);
									else Color(12);
								}
							}
						}
					}
				}
			}
			if (W.Rooms[P.CRI].Grid[x][y] == P.c) Color(9);
			else if (W.Rooms[P.CRI].Grid[x][y] == '0') Color(0);
			else if (W.Rooms[P.CRI].Grid[x][y] == P.eH) Color(13);
			else if (W.Rooms[P.CRI].Grid[x][y] == P.k) Color(2);
			else if (W.Rooms[P.CRI].Grid[x][y] == '!') Color(2);
			else if (W.Rooms[P.CRI].Grid[x][y] == P.S || W.Rooms[P.CRI].Grid[x][y] == 'v' || W.Rooms[P.CRI].Grid[x][y] == '^' || W.Rooms[P.CRI].Grid[x][y] == '>' || W.Rooms[P.CRI].Grid[x][y] == '<') {
				if (P.KillingBlow) Color(4); 
				else Color(11);
			}

			printf("%c ", W.Rooms[P.CRI].Grid[x][y]);
			// This removes the previously scanned location from the echo list 
			// Compare current x, y against each enemyscannedroom 
			if (W.Rooms[P.CRI].Grid[x][y] == P.E) {
				for (int i = 0; i < W.Rooms[P.CRI].EnemyScannedSpaces.size(); i++) {
					if ((x == W.Rooms[P.CRI].EnemyScannedSpaces[i][0]) && (y == W.Rooms[P.CRI].EnemyScannedSpaces[i][1])) {
						for (int n = 0; n < W.Rooms[P.CRI].ScannedSpaces.size(); n++) {
							if ((W.Rooms[P.CRI].ScannedSpaces[n][0] == W.Rooms[P.CRI].EnemyScannedSpaces[i][0]) && (W.Rooms[P.CRI].ScannedSpaces[n][1] == W.Rooms[P.CRI].EnemyScannedSpaces[i][1])){
								W.Rooms[P.CRI].ScannedSpaces.erase(W.Rooms[P.CRI].ScannedSpaces.begin() + n);
							}		
						}
					}
				}
			}
		}
		tab = 0;
		printf("\n");
	}
	//Controls for Room 1
	if (P.CRI == 0) {
		Color(7); 
		printf("\n"); 
		for (int i = 0; i < 4; i++) printf("\t");
		printf("WASD to Move.\n"); 
		for (int i = 0; i < 4; i++) printf("\t");
		printf("Arrow Keys to ECHOLOCATE\n");
		for (int i = 0; i < 4; i++) printf("\t");
		printf("X for Key Code and Inventory\n");
		for (int i = 0; i < 4; i++) printf("\t");
		printf("C for Map\n"); 
		for (int i = 0; i < 4; i++) printf("\t");
		printf("V for Hints\n");
		for (int i = 0; i < 4; i++) printf("\t");
		printf("Q to Quit\n"); 
	}
	//Controls for Room 6
	if (P.CRI == 5) {
		Color(7);
		printf("\n");
		for (int i = 0; i < 4; i++) printf("\t");
		printf("Take up the sword\n");
		for (int i = 0; i < 4; i++) printf("\t");
		printf("Strike back against the darkness!\n");
		for (int i = 0; i < 4; i++) printf("\t");
		printf("Press E to attack\n");
	}
}

void Inventory(WorldState& W, PlayerState& P) {
	system("cls");
	Color(7);
	printf("CURRENT GOAL: %s\n\n", P.Goal); 
	printf("|-----------------------|\n");
	printf("|\t\t\t|\n");
	printf("|INVENTORY:\t\t| \n"); 
	printf("|\t\t\t|\n");
	printf("|- Key Pieces: %d\t|\n", (int)(P.KeyNum * 2));
	printf("|- Sword: %s|\n", P.Sword);
	printf("|\t\t\t|\n");
	printf("|-----------------------|\n\n");
	printf("KEY CODE: \n\n");
	Color(9);
	printf("%c", P.c); 
	Color(7); 
	printf(": Player\n\n"); 
	Color(13);
	printf("%c", P.eH);
	Color(7);
	printf(": Echolocation (Echolocate to see whats in front of you)\n\n");
	Color(7);
	printf("%c,%c,%c,%c,etc", W.h, W.v, W.L, W.T);
	printf(": Walls\n\n");
	Color(6);
	printf("%c", W.D);
	Color(7);
	printf(": Door\n\n");
	Color(14);
	printf("%c", W.LD);
	Color(7);
	printf(": Locked Door (Probably needs a key) \n\n");
	Color(12);
	printf("%c", P.E);
	Color(7);
	printf(": Enemy (Moves towards whatever it hears)\n\n");
	Color(2);
	printf("%c", P.k);
	Color(7);
	printf(": Key Piece (Two make a key)\n\n");
	Color(11); 
	printf("%c", P.S);
	Color(7);
	printf(": The Sword\n\n");

	char input = 0;
	printf("(Press R to close)");
	while (input != 'r') {
		input = tolower(_getch());
	}
	system("cls");
}
void Hints(WorldState& W, PlayerState& P) {
	system("cls");
	Color(7);
	printf("----------------------------------------------"); 
	Color(13); printf("\nECHOLOCATION: \n\n");
	Color(7); printf("- The ");
	Color(13); printf("%c", P.eH);
	Color(7);
	printf(" moves on its own everytime the player presses an input\n\n");
	printf("- Stay close to walls and pay attention to their direction. You'll know a wall ends if you reach a %c, %c, %c, or %c\n\n", W.C,W.c,W.L,W.l);
	printf("- AVOID pressing arrow keys while echolocating. You might miss instructions or Enemies\n\n");
	printf("----------------------------------------------");
	Color(12); printf("\nENEMIES: \n\n");
	Color(7); printf("- When scanned the ");
	Color(12); printf("%c", P.E);
	Color(7);
	printf(" moves towards the position the player was at when they echolocated then stops\n\n");
	Color(7); printf("- The ");
	Color(12); printf("%c", P.E);
	Color(7);
	printf(" is invisible while moving\n\n"); 
	printf("- Try to learn where the enemies are positioned and move around them\n\n"); 
	printf("- Remember everything is reset when you die so if you're softlocked die to reset\n\n"); 
	printf("----------------------------------------------");
	Color(9); printf("\nGENERAL\n\n");
	Color(7);
	printf("- Don't move too fast. Some information is only on screen until you press an input\n\n"); 
	printf("- Check the Key Code and Inventory for information on what every item and object looks like\n\n"); 
	printf("- Check your Map for descriptions of rooms and maybe some hints\n\n"); 

	char input = 0;
	printf("(Press R to close)");
	while (input != 'r') {
		input = tolower(_getch());
	}
	system("cls");
} 
void Map(WorldState& W, PlayerState& P) {
	system("cls");
	std::vector<std::vector<int>> CurrRoom = {};
	const char* CurrName = "";
	const char* CurrDesc = "";
	
	switch (P.CRI) {
	case 0:
		CurrRoom = W.Room1;
		CurrName = "Your Glade:\n";
		CurrDesc = "Not a word has been uttered in this place since you first awoke.\nOnly the wind whistling through the upper branches gives you voice however faint.\n\n";
		break; 
	case 1:
		CurrRoom = W.Room2;
		CurrName = "A Library:\n";
		CurrDesc = "There is something sinister about this place.\nIt smells of paper and decay.\nYour voice is the distant sound of a book falling from a shelf and the scratch scratch of scholar's quills.\n";
		break;
	case 2:
		CurrRoom = W.Room3;
		CurrName = "A Market Street:\n";
		CurrDesc = "The hustle and bustle of a thousand different lives fills your throat.\nFragments of conversations, Vendors calling, wooden wheels on uneven cobble.\nAll that life and noise threatens to drown you out.\n";
		break;
	case 3:
		CurrRoom = W.Room4;
		CurrName = "Clock Shop:\n";
		CurrDesc = "Finally safety.\nYou can can breath freely to the steady click of the hundreds of clocks all perfectly in sync.\nYour sisters find new life in these rhythmic forms.\n";
		break;
	case 4:
		CurrRoom = W.Room5;
		CurrName = "Candle Maker's Shop:\n";
		CurrDesc = "Finally safety.\nYou hum along with the bubbling cauldrons.\nWhile the flames make you nervous, they burn only string and the hiss of bubbling wax accents your singing.\n"; 
		break;
	case 5:
		CurrRoom = W.Room6;
		CurrName = "";
		CurrDesc = "Take the Sword.\nIt's dangerous to walk alone through this world.\n"; 
		break;
	case 6:
		CurrRoom = W.Room7;
		CurrName = "The Parapet:\n"; 
		CurrDesc = "Your howls; the wind.\nThis haunted place is impassable without a weapon to defend yourself.\n"; 
		break;
	case 7:
		CurrRoom = W.Room8;
		CurrName = "The Castle:\n";
		CurrDesc = "There is a secret in this place you must find.\nYour battle cry is the moans of lost souls come to claim another.\nYou will not go quietly into the night.\n"; 
		break;
	case 8:
		CurrRoom = W.Room9;
		CurrName = "Mountain Top: \n";
		CurrDesc = "Face your tormentor.\nHe strikes with lightning, but you are the thunder ECHOING through the heavens.\n"; 
		break;
	}

	std::vector<std::vector<char>> Map = {
		{'|',' ',' ',' ',' ',' ',' ',W.b,W.b,W.b,' ',' ',' ',' ',' ','|'},
		{'|',' ',' ',' ',' ',' ',' ',W.b,W.b,W.b,' ',' ',' ',' ',' ','|'},
		{'|',W.b,W.b,W.b,W.b,W.b,W.b,W.b,W.b,W.b,W.b,W.b,W.b,' ',' ','|'},
		{'|',W.b,W.b,W.b,W.b,W.b,W.b,W.b,W.b,W.b,W.b,W.b,W.b,' ',' ','|'},
		{'|',' ',' ',' ',W.b,W.b,W.b,W.b,W.b,W.b,' ',' ',' ',' ',' ','|'},
		{'|',' ',' ',' ',W.b,W.b,W.b,W.b,W.b,W.b,' ',' ',' ',' ',' ','|'},
		{'|',' ',' ',' ',W.b,W.b,W.b,W.b,W.b,W.b,' ',' ',' ',' ',' ','|'},
		{'|',' ',' ',' ',W.b,W.b,W.b,W.b,W.b,W.b,' ',' ',' ',' ',' ','|'},
	}; 
	int x = 0;
	int y = 0; 
	Color(7);
	printf("CURRENT GOAL: %s\n\n", P.Goal);
	printf(" MAP: \n"); 
	printf("|--------------|\n"); 
	for (y = 0; y < 8; y++) {
		for (x = 0; x < 16; x++) {
			Color(0);
			for (int q = 0; q < W.MapList.size(); q++) {
				for (int u = 0; u < W.MapList[q].size(); u++) {
					if ((x == W.MapList[q][u][0]) && (y == W.MapList[q][u][1])) Color(8);
				}
			}
			// Check Current room
			for (int n = 0; n < CurrRoom.size(); n++) {
				if ((x == CurrRoom[n][0]) && (y == CurrRoom[n][1])) Color(9); 
			}
			if (Map[y][x] == '|') Color(7);
			printf("%c", Map[y][x]);
		}
		printf("\n");
	}
	Color(7);
	printf("|--------------|\n\n");
	printslow(CurrName, 40); 
	printf(CurrDesc); 

	char input = 0;
	printf("\n(Press R to close)");
	while (input != 'r') {
		input = tolower(_getch());
	}
	system("cls");
}

void Respawn(WorldState& W, PlayerState& P) {
	system("cls");
	Color(4);
	printslow("In the dark only monsters can hear you scream\n", 60);
	printf("YOU DIED! Enemies have reset\n(Press anything to continue)\n");

	// Reset Enemies 
	int u = 0; 
	for (u; u < W.Rooms.size(); u++) {
		if (W.Rooms[u].Enemies.size() - 1 == 0) {
			W.Rooms[u].Grid[W.Rooms[u].Enemies[0].X][W.Rooms[u].Enemies[0].Y] = '0';
			W.Rooms[u].Enemies[0].X = W.Rooms[u].Enemies[0].RX;
			W.Rooms[u].Enemies[0].Y = W.Rooms[u].Enemies[0].RY;
			W.Rooms[u].Grid[W.Rooms[u].Enemies[0].X][W.Rooms[u].Enemies[0].Y] = P.E;
			W.Rooms[u].Enemies[0].TarX = W.Rooms[u].Enemies[0].X;
			W.Rooms[u].Enemies[0].TarY = W.Rooms[u].Enemies[0].Y;
			W.Rooms[u].Enemies[0].SetTar = false; 
			W.Rooms[u].Enemies[0].Dead = false; 
		}
		else {
			for (int n = 0; n < W.Rooms[u].Enemies.size(); n++) {
				W.Rooms[u].Grid[W.Rooms[u].Enemies[n].X][W.Rooms[u].Enemies[n].Y] = '0';
				W.Rooms[u].Enemies[n].X = W.Rooms[u].Enemies[n].RX;
				W.Rooms[u].Enemies[n].Y = W.Rooms[u].Enemies[n].RY;
				W.Rooms[u].Grid[W.Rooms[u].Enemies[n].X][W.Rooms[u].Enemies[n].Y] = P.E;
				W.Rooms[u].Enemies[n].TarX = W.Rooms[u].Enemies[n].X;
				W.Rooms[u].Enemies[n].TarY = W.Rooms[u].Enemies[n].Y;
				W.Rooms[u].Enemies[n].SetTar = false;
				W.Rooms[u].Enemies[n].Dead = false;
			}
		}
	}
	//Reset Sword
	P.Attacking = false; 

	//Reset Previous Echo 
	W.Rooms[P.CRI].Grid[P.EchoX][P.EchoY] = '0';

	// Reset Player Position
	W.Rooms[P.CRI].Grid[P.PreviewX][P.PreviewY] = '0';
	P.X = P.RespawnX;
	P.Y = P.RespawnY;
	P.CRI = 0; 
	W.Rooms[P.CRI].Grid[P.X][P.Y] = P.c;
	// Reset Echo
	P.EchoX = P.X;
	P.EchoY = P.Y; 
	char input = 0;
	while (input == 0) {
		input = tolower(_getch());
		system("cls");
	}
	system("cls");
}

int GetEnemyIndex(PlayerState& P, WorldState& W) {
	int i; 
	for (i = 0; i < W.Rooms[P.CRI].Enemies.size(); i++) {
		if ((W.Rooms[P.CRI].Enemies[i].X == P.EchoX) && (W.Rooms[P.CRI].Enemies[i].Y == P.EchoY)) {
			
			return i;
		}
	}
	return i; 
}
void Kill(WorldState& W, PlayerState& P, int X, int Y) {

	for (int i = 0; i < W.Rooms[P.CRI].Enemies.size(); i++) {
		if ((W.Rooms[P.CRI].Enemies[i].X == X) && (W.Rooms[P.CRI].Enemies[i].Y == Y)) {
			W.Rooms[P.CRI].Enemies[i].Dead = true; 
		}
	}
	P.KillingBlow = true; 
}


