#pragma once
#include <string>
#include <vector>

struct PlayerState
{
	// X is verticle and Y is horizontal 
	// Don't ask I messed something up and now it's too confusing to fix
	// Its so the Grid prints right side up instead of being sideways. It make level editing easier
	int X = 2;
	int Y = 2; 
	int PreviewX;
	int PreviewY;

	//Respawn 
	int RespawnX = X;
	int RespawnY = Y;
	int RespawnCRI = 0; 

	//Sword v^<>
	//1: Up
	//2: Right
	//3: Down
	//4: Left
	bool SwordFound = false; 
	bool Attacking = false;
	bool KillingBlow = false; 
	int Facing; 
	int PreSX;
	int PreSY; 
	char PreSChar; 
	
	// Echo
	int EchoX = X;
	int EchoY = Y; 
	int AtEchoX;
	int AtEchoY;
	int PreEchoX;
	int PreEchoY;
	bool Echoing; 
	bool CanEcho = true; 
	bool EchoingN;
	bool EchoingE;
	bool EchoingS;
	bool EchoingW;

	// Exit Conditions 
	bool Died;
	bool WantsToExit;
	bool WontheGame = false; 

	// Current Room Index
	int CRI;

	// Symbols
	char c = (char)234; //Player
	char E = (char)232; //Enemy
	char G = (char)235; //Ghost
	char eH = (char)238; //Echo
	char k = (char)168;	//Key
	char S = (char)245; //Sword
	char BL = (char)35; //Boss Lightning 
	char B = (char)225; //Boss HitPoints 
	char BC = (char)250; //BossCharge 

	//Keys 
	float KeyNum = 0; 

	//Inventory Text
	int GoalProgression = 0; 
	const char* Goal = "Make your way to The Market";
	const char* Sword = "Not Found\t"; 
};

struct EnemyState 
{
	//Position 
	int X;
	int Y;
	int PreX;
	int PreY;
	int TarX; 
	int TarY; 
	int RX;
	int RY;

	//Direction 
	bool SetTar = false;

	bool Dead = false; 

	int fading = 0; 
	
	//Ghost Mode
	bool Ghost = false; 
	bool GhostFade = true; 
	char Replace = '0'; 

};

struct BossState
{
	int X;
	int Y;
	bool Dead = false; 
	//1: Up
	//2: Down
	//3: Left
	//4: Right
	int PreX; 
	int PreY;
	int TarDirection; 
	std::vector<int> LList; 
	bool Strike = false; 
	bool Struck = false; 
};

struct RoomExits
{
	int x;
	int y; 
	int targetRoom; 
	int targetx;
	int targety;
};

struct RoomData
{
	int MaxGrid = 5;
	std::vector<std::vector<char>> Grid;
	std::vector<RoomExits> Exits; 
	std::vector<std::vector<int>> ScannedSpaces;
	std::vector<std::vector<int>> ResetList; 
	std::vector<EnemyState> Enemies; 
	std::vector<std::vector<int>> EnemyScannedSpaces;
	std::vector<BossState> Boss;

	bool Entered = false; 
};

struct WorldState
{
	std::vector<RoomData> Rooms;
	// 3D Vector for the Map
	std::vector<std::vector<std::vector<int>>> MapList = {};
	char v = (char)186; //Verticle Wall
	char h = (char)205; //Horizontal Wall
	char c = (char)187; //left down corner
	char C = (char)188; //left up corner
	char l = (char)201; //right down corner
	char L = (char)200; //right up corner
	char T = (char)203; //down T
	char t = (char)202; //up T
	char F = (char)185; //left T
	char f = (char)204; //right T
	char M = (char)178; //Dark map
	char m = (char)177; //Light map
	char b = (char)176; //Background map

	char D = (char)219; //Door
	char LD = (char)254; //Locked Door

	//Map Data
	std::vector<std::vector<int>>Room1 = {
		{4,4},{5,4},{6,4},
		{4,5},{5,5},{6,5}
	};
	std::vector<std::vector<int>>Room2 = {
		{4,2},{5,2},{6,2},
		{4,3},{5,3},{6,3}
	};
	std::vector<std::vector<int>>Room3 = {
		{7,2},{8,2},{9,2},
		{7,3},{8,3},{9,3}
	};
	std::vector<std::vector<int>>Room4 = {
		{7,0},{8,0},{9,0},
		{7,1},{8,1},{9,1}
	};
	std::vector<std::vector<int>>Room5 = {
		{7,4},{8,4},{9,4},
		{7,5},{8,5},{9,5}
	};
	std::vector<std::vector<int>>Room6 = {
		{10,2},{11,2},{12,2},
		{10,3},{11,3},{12,3}
	};
	std::vector<std::vector<int>>Room7 = {
		{4,6},{5,6},{6,6},
		{4,7},{5,7},{6,7}
	};
	std::vector<std::vector<int>>Room8 = {
		{7,6},{8,6},{9,6},
		{7,7},{8,7},{9,7}
	};
	std::vector<std::vector<int>>Room9 = {
		{1,2},{2,2},{3,2},
		{1,3},{2,3},{3,3}
	};
	std::vector<std::vector<int>>Room10 = {
		{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},
		{1,1},{2,1},{3,1},{4,1},{5,1},{6,1}
	};
};

void RenderGame(PlayerState& P, WorldState& W);
void UpdateGame(PlayerState& P, WorldState& W);
void PlayerInput(PlayerState& P, WorldState& W);
void CleanupGame(PlayerState& P, WorldState& W); 