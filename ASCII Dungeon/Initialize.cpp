#include <stdio.h>
#include <stdlib.h> 
#include <conio.h>
#include <windows.h>
#include "Core.h"
#include "Functions.h"

void AddExit(RoomExits& R, int ExitX, int ExitY, int TarRoom, int TarX, int TarY) {
	R.x = ExitX;
	R.y = ExitY;
	R.targetRoom = TarRoom - 1; 
	R.targetx = TarX;
	R.targety = TarY;
}
void AddEnemy(EnemyState& E, int X, int Y) {
	E.X = X; 
	E.Y = Y; 
	E.TarX = X;
	E.TarY = Y;
	E.RX = X; 
	E.RY = Y; 
}

void InitializeGame(PlayerState& P, WorldState& W) {
	///////////////////////////////ROOM 1/////////////////////////////////////////////////
	// Creates Room and Room Data
	RoomData Room1{};
	Room1.MaxGrid = 5;
	Room1.Entered = true; 
	Room1.Grid = {
	{W.v,W.D,W.h,'0',W.v},
	{W.v,'0','0','0',W.v},
	{W.v,'0',P.c,'0',W.v},
	{'0',P.S,'0','0',W.v},
	{W.v,'0',W.c,W.D,W.v}
	};
// Exit to 2
	RoomExits R1ExitTo2{};
	AddExit(R1ExitTo2, 1, 0, 2, 1, 7); 
	//Adds Room to global roomdata 
	Room1.Exits.push_back(R1ExitTo2);
// Exit to 7
	RoomExits R1ExitTo7{};
	AddExit(R1ExitTo7, 3, 4, 7, 1, 1);
	//Adds Room to global roomdata 
	Room1.Exits.push_back(R1ExitTo7);
	W.Rooms.push_back(Room1);

	///////////////////////////////ROOM 2/////////////////////////////////////////////////
	RoomData Room2{};
	Room2.MaxGrid = 9;
	Room2.Grid = {
	{W.v,W.h,W.h,W.h,W.h,W.v,W.h,W.t,W.v},
	{W.v,P.E,'0','0','0',W.v,P.E,'0',W.v},
	{W.v,'0','0',W.v,'0',W.v,'0','0',W.L},
	{W.v,'0','0',W.v,'0','0','0','0',W.D},
	{W.v,W.h,W.h,W.t,W.h,W.c,'0',W.h,W.v},
	{W.v,'0','0','0','0',W.v,'0','0',W.v},
	{W.v,'0','0','0','0',W.v,'0','0',W.v},
	{W.v,'0','0','0','0','0','0','0',W.v},
	{W.v,W.D,W.h,W.h,W.T,W.h,W.h,W.h,W.v}
	};
// Exit to 1
	RoomExits R2ExitTo1{};
	AddExit(R2ExitTo1, 1, 8, 1, 1, 1); 
	Room2.Exits.push_back(R2ExitTo1);
// Exit to 3
	RoomExits R2ExitTo3{};
	AddExit(R2ExitTo3, 8, 3, 3, 1, 4); 
	Room2.Exits.push_back(R2ExitTo3);
// Enemy 1
	EnemyState E2_1{};
	AddEnemy(E2_1, 1, 6); 
	Room2.Enemies.push_back(E2_1);
// Enemy 2
	EnemyState E2_2{};
	AddEnemy(E2_2, 1, 1);
	Room2.Enemies.push_back(E2_2);
	W.Rooms.push_back(Room2);

	///////////////////////////////ROOM 3/////////////////////////////////////////////////
	RoomData Room3{};
	Room3.MaxGrid = 9;
	Room3.Grid = {
	{'0','0','0','0',W.h,W.D,W.L,W.h,'0'},
	{'0','0','0','0',W.v,P.E,'0',W.v,'0'},
	{'0','0','0','0',W.v,'0','0',W.v,'0'},
	{W.v,W.h,W.h,W.h,W.C,'0','0',W.L,'0'},
	{W.D,'0','0','0','0','0','0',W.LD,'0'},
	{W.v,W.h,W.h,W.h,W.c,'0','0',W.l,'0'},
	{'0','0','0','0',W.v,'0','0',W.v,'0'},
	{'0','0','0','0',W.v,P.E,P.E,W.v,'0'},
	{'0','0','0','0',W.h,W.D,W.l,W.h,'0'}
	};
// Exit to 2
	RoomExits R3ExitTo2{};
	AddExit(R3ExitTo2, 0, 4, 2, 7, 3); 
	Room3.Exits.push_back(R3ExitTo2);
// Exit to 4
	RoomExits R3ExitTo4{};
	AddExit(R3ExitTo4, 5, 0, 4, 6, 1);
	Room3.Exits.push_back(R3ExitTo4);
// Exit to 5
	RoomExits R3ExitTo5{};
	AddExit(R3ExitTo5, 5, 8, 5, 5, 5);
	Room3.Exits.push_back(R3ExitTo5);
// Exit to 6
	RoomExits R3ExitTo6{};
	AddExit(R3ExitTo6, 7, 4, 6, 1, 3);
	Room3.Exits.push_back(R3ExitTo6);
// Enemy 1
	EnemyState E3_1{};
	AddEnemy(E3_1, 1, 5);
	Room3.Enemies.push_back(E3_1);
// Enemy 2
	EnemyState E3_2{};
	AddEnemy(E3_2, 7, 5);
	Room3.Enemies.push_back(E3_2);
// Enemy 3
	EnemyState E3_3{};
	AddEnemy(E3_3, 7, 6);
	Room3.Enemies.push_back(E3_3);
	W.Rooms.push_back(Room3);

	///////////////////////////////ROOM 4/////////////////////////////////////////////////
	// Creates Room and Room Data
	RoomData Room4{};
	Room4.MaxGrid = 8;
	Room4.Grid = {
	{W.v,W.h,W.h,W.h,W.h,W.h,W.h,W.v},
	{W.v,'0',P.k,W.v,'0','0','0',W.v},
	{W.v,'0','0',W.v,'0',W.v,W.D,W.v},
	{W.v,W.c,'0',W.v,'0',W.v,'0','0'},
	{W.v,W.v,'0','0','0',W.v,'0','0'},
	{W.v,W.v,W.h,W.h,W.h,W.v,'0','0'},
	{'0','0','0','0','0','0','0','0'},
	{'0','0','0','0','0','0','0','0'}
	};
// Exit to 3
	RoomExits R4ExitTo3{};
	AddExit(R4ExitTo3, 6, 2, 3, 5, 1);
	//Adds Room to global roomdata 
	Room4.Exits.push_back(R4ExitTo3);
	W.Rooms.push_back(Room4);

	///////////////////////////////ROOM 5/////////////////////////////////////////////////
	// Creates Room and Room Data
	RoomData Room5{};
	Room5.MaxGrid = 7;
	Room5.Grid = {
	{'0','0','0','0','0','0','0'},
	{W.v,W.h,W.h,W.h,W.h,'0','0'},
	{W.v,'0','0','0',W.v,'0','0'},
	{W.v,'0',P.k,'0',W.v,'0','0'},
	{W.v,'0','0','0',W.v,W.D,W.v},
	{W.F,'0','0','0','0','0',W.v},
	{W.v,W.h,W.h,W.h,W.h,W.T,W.v},
	
	};
	// Exit to 3
	RoomExits R5ExitTo3{};
	AddExit(R5ExitTo3, 5, 4, 3, 5, 7); 
	//Adds Room to global roomdata 
	Room5.Exits.push_back(R5ExitTo3);
	W.Rooms.push_back(Room5);
	///////////////////////////////ROOM 6/////////////////////////////////////////////////
	// Creates Room and Room Data
	RoomData Room6{};
	Room6.MaxGrid = 6;
	Room6.Grid = {
	{'0','0','0','0','0','0'},
	{'0','0','0','0','0','0'},
	{W.v,W.h,W.h,W.h,W.h,W.h},
	{W.D,'0','0','0',P.S,W.v},
	{W.v,W.h,W.h,W.h,W.h,W.h},
	{'0','0','0','0','0','0'}
	};
	// Exit to 3
	RoomExits R6ExitTo3{};
	AddExit(R6ExitTo3, 0, 3, 3, 6, 4);
	//Adds Room to global roomdata 
	Room6.Exits.push_back(R6ExitTo3);
	W.Rooms.push_back(Room6);
	///////////////////////////////ROOM 7/////////////////////////////////////////////////
	// Creates Room and Room Data
	RoomData Room7{};
	Room7.MaxGrid = 6;
	Room7.Grid = {
	{W.v,W.D,W.v,'0','0','0'},
	{W.v,'0',W.v,'0','0','0'},
	{W.v,'0',W.v,'0','0','0'},
	{W.v,'0',W.L,W.h,W.h,W.h},
	{W.v,P.E,'0','0',P.E,W.D}, 
	{W.v,W.h,W.h,W.h,W.h,W.h},
	};
	// Exit to 1
	RoomExits R7ExitTo1{};
	AddExit(R7ExitTo1, 1, 0, 1, 3, 3);
	//Adds Room to global roomdata 
	Room7.Exits.push_back(R7ExitTo1);
	// Exit to 8
	RoomExits R7ExitTo8{};
	AddExit(R7ExitTo8, 5, 4, 8, 4, 8);
	//Adds Room to global roomdata 
	Room7.Exits.push_back(R7ExitTo8);
// Enemy 1
	EnemyState E7_1{};
	AddEnemy(E7_1, 4, 1);
	Room7.Enemies.push_back(E7_1);
// Enemy 2
	EnemyState E7_2{};
	AddEnemy(E7_2, 4, 4);
	Room7.Enemies.push_back(E7_2);
	W.Rooms.push_back(Room7);
	///////////////////////////////ROOM 8/////////////////////////////////////////////////
	// Creates Room and Room Data
	RoomData Room8{};
	Room8.MaxGrid = 10;
	Room8.Grid = {
	{W.v,W.h,W.h,W.h,'0','0','0','0','0','0'},
	{W.v,'0','!','0',W.f,W.h,W.h,W.h,W.h,W.h},
	{W.v,'0',W.h,W.h,W.C,'0','0','0','0',W.v},
	{W.v,'0','0','0','0','0',W.l,W.c,'0',W.v},
	{W.v,'0',W.l,W.T,W.c,'0',W.L,W.C,'0',W.v},
	{W.v,'0',W.L,W.t,W.C,'0','0','0','0',W.v},
	{W.v,'0','0','0','0','0',W.l,W.c,'0',W.v},
	{W.v,W.h,W.h,W.h,W.h,W.h,W.t,W.C,'0',W.v},
	{'0','0','0',W.D,'0','0','0','0','0',W.v},
	{'0','0','0','0',W.h,W.h,W.h,W.h,W.h,W.v},
	};
	// Exit to 7
	RoomExits R8ExitTo7{};
	AddExit(R8ExitTo7, 3, 8, 7, 4, 4);
	//Adds Room to global roomdata 
	Room8.Exits.push_back(R8ExitTo7);
	W.Rooms.push_back(Room8);
	///////////////////////////////ROOM 9/////////////////////////////////////////////////
	// Creates Room and Room Data
	RoomData Room9{};
	Room9.MaxGrid = 5;
	Room9.Grid = {
	{W.v,W.h,W.h,W.h,W.v},
	{W.v,'0','0','0',W.v},
	{W.v,'0','0','0',W.D},
	{W.v,P.S,'0','0',W.v},
	{W.v,W.h,W.c,W.h,W.v}
	};
	// Exit to 2
	RoomExits R9ExitTo2{};
	AddExit(R9ExitTo2, 4, 2, 2, 1, 3);
	//Adds Room to global roomdata 
	Room9.Exits.push_back(R9ExitTo2);
	W.Rooms.push_back(Room9);

	P.CRI = 0;
	W.MapList.push_back(W.Room1);
}

void MainMenu() {
	char input = 0;
	while (input == 0) {
		printf("(Press Anything)");
		input = tolower(_getch());
		system("cls");
	}
	// Shout out to patorjk.com for the ascii art generator 
	Sleep(500); 
	printslow("Welcome to:\n", 80);
	Sleep(500);
	printf("HX%c", char(234));
	Sleep(1000); 
	printf("\n");
	printf("______ \n"); 
	printf("| ___ \\ \n");
	printf("| |_/ /___  ___  ___  _ __   __ _ _ __ ___ \n");
	printf("|    // _ \\/ __|/ _ \\| '_ \\ / _` | '__/ _ \\ \n");
	printf("| |\\ \\  __/\\__ \\ (_) | | | | (_| | | |  __/ \n"); 
	printf("\\_| \\_\\___||___/\\___/|_| |_|\\__,_|_|  \\___| \n");
	Sleep(1000); 
	printf("          _____                    _____                    _____                   _______         \n");
	printf("         /\\    \\                  /\\    \\                  /\\    \\                 /::\\    \\        \n");
	printf("        /::\\    \\                /::\\    \\                /::\\____\\               /::::\\    \\       \n");
	printf("       /::::\\    \\              /::::\\    \\              /:::/    /              /::::::\\    \\      \n");
	printf("      /::::::\\    \\            /::::::\\    \\            /:::/    /              /::::::::\\    \\     \n");
	printf("     /:::/\\:::\\    \\          /:::/\\:::\\    \\          /:::/    /              /:::/~~\\:::\\    \\    \n");
	printf("    /:::/__\\:::\\    \\        /:::/  \\:::\\    \\        /:::/____/              /:::/    \\:::\\    \\   \n");
	printf("   /::::\\   \\:::\\    \\      /:::/    \\:::\\    \\      /::::\\    \\             /:::/    / \\:::\\    \\  \n");
	printf("  /::::::\\   \\:::\\    \\    /:::/    / \\:::\\    \\    /::::::\\    \\   _____   /:::/____/   \\:::\\____\\ \n");
	printf(" /:::/\\:::\\   \\:::\\    \\  /:::/    /   \\:::\\    \\  /:::/\\:::\\    \\ /\\    \\ |:::|    |     |:::|    |\n");
	printf("/:::/__\\:::\\   \\:::\\____\\/:::/____/     \\:::\\____\\/:::/  \\:::\\    /::\\____\\|:::|____|     |:::|    |\n");
	printf("\\:::\\   \\:::\\   \\::/    /\\:::\\    \\      \\::/    /\\::/    \\:::\\  /:::/    / \\:::\\    \\   /:::/    / \n"); 
	printf(" \\:::\\   \\:::\\   \\/____/  \\:::\\    \\      \\/____/  \\/____/ \\:::\\/:::/    /   \\:::\\    \\ /:::/    /  \n");
	printf("  \\:::\\   \\:::\\    \\       \\:::\\    \\                       \\::::::/    /     \\:::\\    /:::/    /   \n");
	printf("   \\:::\\   \\:::\\____\\       \\:::\\    \\                       \\::::/    /       \\:::\\__/:::/    /    \n");
	printf("    \\:::\\   \\::/    /        \\:::\\    \\                      /:::/    /         \\::::::::/    /     \n");
	printf("     \\:::\\   \\/____/          \\:::\\    \\                    /:::/    /           \\::::::/    /      \n");
	printf("      \\:::\\    \\               \\:::\\    \\                  /:::/    /             \\::::/    /       \n"); 
	printf("       \\:::\\____\\               \\:::\\____\\                /:::/    /               \\::/____/        \n"); 
	printf("        \\::/    /                \\::/    /                \\::/    /                 ~~              \n");
	printf("         \\/____/                  \\/____/                  \\/____/                                  \n"); 
	Sleep(500);
	input = 0; 
	printf("(Press R to start)");
	while (input != 'r') {
		input = tolower(_getch());	
	}
	system("cls");
}