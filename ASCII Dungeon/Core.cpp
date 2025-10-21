#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include "Functions.h" 
#include "Initialize.h"
#include "Core.h"

// ********************************************* DISPLAY ***************************************************
void RenderGame(PlayerState& P, WorldState& W) {
	//Bit of redunancy to make sure the player never gets over written 
	W.Rooms[P.CRI].Grid[P.X][P.Y] = P.c; 

	PrintScreen(W, P);

	//Sword Reset 
	if (P.Attacking) {
		switch (P.Facing) {
		case 1:
			W.Rooms[P.CRI].Grid[P.PreSX][P.Y] = P.PreSChar;
			break;
		case 2:
			W.Rooms[P.CRI].Grid[P.X][P.PreSY] = P.PreSChar;
			break;
		case 3:
			W.Rooms[P.CRI].Grid[P.PreSX][P.Y] = P.PreSChar;
			break;
		case 4:
			W.Rooms[P.CRI].Grid[P.X][P.PreSY] = P.PreSChar;
			break;
		}
		P.Attacking = false;
		P.KillingBlow = false; 
	}
	// Update Map Data
	if (!W.Rooms[P.CRI].Entered) {
		Color(7);
		printslow("Map Updated", 30);
		W.Rooms[P.CRI].Entered = true;
		switch (P.CRI) {
		case 0:
			W.MapList.push_back(W.Room1);
			break; 
		case 1:
			W.MapList.push_back(W.Room2);
			break;
		case 2:
			W.MapList.push_back(W.Room3);
			break;
		case 3:
			W.MapList.push_back(W.Room4);
			break;
		case 4:
			W.MapList.push_back(W.Room5);
			break;
		case 5:
			W.MapList.push_back(W.Room6);
			break;
		case 6:
			W.MapList.push_back(W.Room7);
			break;
		case 7:
			W.MapList.push_back(W.Room8);
			break;
		case 8:
			W.MapList.push_back(W.Room9);
			break;
		case 9:
			W.MapList.push_back(W.Room10);
			break;
		}
	}
	//Player wins
	/*
	if (P.CRI == 9) {
		P.WontheGame = true;
		P.WantsToExit = true;
	}
	*/
}
// ********************************************** UPDATE ***************************************************	
void UpdateGame(PlayerState& P, WorldState& W) {
	
	//Index of current enemy being effected
	int i = 0; 
	//ECHO
	if (P.Echoing) {
		P.CanEcho = false; 
		P.PreEchoX = P.EchoX;
		P.PreEchoY = P.EchoY; 
		if (P.EchoingN) P.EchoX--;
		if (P.EchoingS) P.EchoX++;
		if (P.EchoingE) P.EchoY++;
		if (P.EchoingW) P.EchoY--;
		// If Not out of bounds 
		if ((P.EchoX < W.Rooms[P.CRI].MaxGrid) && (P.EchoX >= 0) && (P.EchoY < W.Rooms[P.CRI].MaxGrid) && (P.EchoY >= 0)) {
			// If colliding with Floor
			if (W.Rooms[P.CRI].Grid[P.EchoX][P.EchoY] == '0') {
				W.Rooms[P.CRI].Grid[P.EchoX][P.EchoY] = P.eH;
				if (W.Rooms[P.CRI].Grid[P.PreEchoX][P.PreEchoY] != P.c) {
					W.Rooms[P.CRI].Grid[P.PreEchoX][P.PreEchoY] = '0';
				}
			}
			// Else stop echoing 
			else {
				// Add Collision to list as a set of 2 corrodinates 
				W.Rooms[P.CRI].ScannedSpaces.push_back({ P.EchoX, P.EchoY });
				// If you hit an enemy
				if (W.Rooms[P.CRI].Grid[P.EchoX][P.EchoY] == P.E) {
					if (W.Rooms[P.CRI].Enemies.size() - 1 > 0) i = GetEnemyIndex(P, W);
					if (!W.Rooms[P.CRI].Enemies[i].Ghost) {
						W.Rooms[P.CRI].EnemyScannedSpaces.push_back({ P.EchoX, P.EchoY });
						W.Rooms[P.CRI].Enemies[i].SetTar = true;
						W.Rooms[P.CRI].Enemies[i].fading = 2;
					}
				}
				if (W.Rooms[P.CRI].Grid[P.PreEchoX][P.PreEchoY] != P.c) {
					W.Rooms[P.CRI].Grid[P.PreEchoX][P.PreEchoY] = '0';
				}
				P.Echoing = false;
				P.EchoingN = false;
				P.EchoingS = false;
				P.EchoingE = false;
				P.EchoingW = false;
			}
		}
		else {
			P.CanEcho = true;
			P.Echoing = false;
			P.EchoingN = false;
			P.EchoingS = false;
			P.EchoingE = false;
			P.EchoingW = false;
			P.EchoX = P.X;
			P.EchoY = P.Y;
			if (W.Rooms[P.CRI].Grid[P.PreEchoX][P.PreEchoY] != P.c) {
				W.Rooms[P.CRI].Grid[P.PreEchoX][P.PreEchoY] = '0';
			}
		}
	}
	else {
		P.CanEcho = true; 
		P.EchoX = P.X;
		P.EchoY = P.Y;
	}

///////////////////////////////////////////////////////////////////////////////////////////////// ENEMY /////////////////////////////////////////////////////////////////////////////////////////
	// Checks if there are any enemies 
	if (W.Rooms[P.CRI].Enemies.size()) {
		// For each enemy move them 
		for (int i = 0; i < W.Rooms[P.CRI].Enemies.size(); i++) {
			EnemyState& E = W.Rooms[P.CRI].Enemies[i];
			if (!E.Dead) {
				if (E.Ghost) W.Rooms[P.CRI].Grid[E.X][E.Y] = P.G;
				else W.Rooms[P.CRI].Grid[E.X][E.Y] = P.E;
				E.PreX = E.X;
				E.PreY = E.Y;
				if (W.Rooms[P.CRI].Grid[E.TarX][E.TarY] == P.E || W.Rooms[P.CRI].Grid[E.TarX][E.TarY] == P.G) {
					E.TarX = E.X;
					E.TarY = E.Y; 
				}
	// If Target Up
				if (E.X > E.TarX) {
					E.X--;
					if (E.Replace != P.eH && E.Replace != P.G) W.Rooms[P.CRI].Grid[E.PreX][E.PreY] = E.Replace;
					else if (W.Rooms[P.CRI].Grid[E.PreX][E.PreY] != P.c) W.Rooms[P.CRI].Grid[E.PreX][E.PreY] = '0';
					E.Replace = W.Rooms[P.CRI].Grid[E.X][E.Y];
					if (E.Ghost) W.Rooms[P.CRI].Grid[E.X][E.Y] = P.G;
					else {
						W.Rooms[P.CRI].Grid[E.X][E.Y] = P.E;
						if (E.fading >= 2) {
							W.Rooms[P.CRI].ScannedSpaces.push_back({ E.X, E.Y });
							W.Rooms[P.CRI].EnemyScannedSpaces.push_back({ E.X, E.Y });
							E.fading--;
						}
					}
					E.PreX = E.X;
				}
	// If Target Down
				else if (E.X < E.TarX) {
					E.X++;
					if (E.Replace != P.eH && E.Replace != P.G) W.Rooms[P.CRI].Grid[E.PreX][E.PreY] = E.Replace;
					else if (W.Rooms[P.CRI].Grid[E.PreX][E.PreY] != P.c) W.Rooms[P.CRI].Grid[E.PreX][E.PreY] = '0';
					E.Replace = W.Rooms[P.CRI].Grid[E.X][E.Y];
					if (E.Ghost) W.Rooms[P.CRI].Grid[E.X][E.Y] = P.G;
					else {
						W.Rooms[P.CRI].Grid[E.X][E.Y] = P.E;
						if (E.fading >= 2) {
							W.Rooms[P.CRI].ScannedSpaces.push_back({ E.X, E.Y });
							W.Rooms[P.CRI].EnemyScannedSpaces.push_back({ E.X, E.Y });
							E.fading--;
						}
					}
					E.PreX = E.X;
				}
	// If Target Right
				if (E.Y < E.TarY) {
					E.Y++;
					if (E.Replace != P.eH && E.Replace != P.G) W.Rooms[P.CRI].Grid[E.PreX][E.PreY] = E.Replace;
					else if (W.Rooms[P.CRI].Grid[E.PreX][E.PreY] != P.c) W.Rooms[P.CRI].Grid[E.PreX][E.PreY] = '0';
					E.Replace = W.Rooms[P.CRI].Grid[E.X][E.Y];
					if (E.Ghost) W.Rooms[P.CRI].Grid[E.X][E.Y] = P.G;
					else {
						W.Rooms[P.CRI].Grid[E.X][E.Y] = P.E;
						if (E.fading >= 2) {
							W.Rooms[P.CRI].ScannedSpaces.push_back({ E.X, E.Y });
							W.Rooms[P.CRI].EnemyScannedSpaces.push_back({ E.X, E.Y });
							E.fading--;
						}
					}
					E.PreY = E.Y;
				}
	// If Target Left
				else if (E.Y > E.TarY) {
					E.Y--;
					if (E.Replace != P.eH && E.Replace != P.G) W.Rooms[P.CRI].Grid[E.PreX][E.PreY] = E.Replace;
					else if(W.Rooms[P.CRI].Grid[E.PreX][E.PreY] != P.c) W.Rooms[P.CRI].Grid[E.PreX][E.PreY] = '0';
					E.Replace = W.Rooms[P.CRI].Grid[E.X][E.Y];
					if(E.Ghost) W.Rooms[P.CRI].Grid[E.X][E.Y] = P.G;
					else {
						W.Rooms[P.CRI].Grid[E.X][E.Y] = P.E;
						if (E.fading >= 2) {
							W.Rooms[P.CRI].ScannedSpaces.push_back({ E.X, E.Y });
							W.Rooms[P.CRI].EnemyScannedSpaces.push_back({ E.X, E.Y });
							E.fading--;
						}
					}
					E.PreY = E.Y;
				}
	// If Ghost
				if (E.Ghost) {
					if ((E.Replace != '0') && (W.Rooms[P.CRI].Grid[E.X][E.Y] != P.G || W.Rooms[P.CRI].Grid[E.X][E.Y] != P.E)) {
						E.GhostFade = false;
						E.fading = -1; 
						W.Rooms[P.CRI].ScannedSpaces.push_back({ E.X, E.Y });
						W.Rooms[P.CRI].EnemyScannedSpaces.push_back({ E.X, E.Y });
					}
					if (P.Echoing) {
						E.TarX = P.AtEchoX;
						E.TarY = P.AtEchoY;
						if (E.GhostFade) E.fading = 3; 
					}
					if (E.fading >= 1) {
						E.GhostFade = false; 
						W.Rooms[P.CRI].ScannedSpaces.push_back({ E.X, E.Y });
						W.Rooms[P.CRI].EnemyScannedSpaces.push_back({ E.X, E.Y });
						E.fading--;
					}
					if (!P.Echoing) {
						E.GhostFade = true;
					}
				}
				// Player Dies
				if (W.Rooms[P.CRI].Grid[E.X][E.Y] == W.Rooms[P.CRI].Grid[P.X][P.Y]) {
					Respawn(W, P);
				}
			}
		}
		if (W.Rooms[P.CRI].Enemies.size()) {
			// This is placed here so that the enemy doesn't move immediatly but delays
			if (W.Rooms[P.CRI].Enemies[i].SetTar == true) {
				W.Rooms[P.CRI].Enemies[i].TarX = P.AtEchoX;
				W.Rooms[P.CRI].Enemies[i].TarY = P.AtEchoY;
				W.Rooms[P.CRI].Enemies[i].SetTar = false;
			}
		}
		
	} 

///////////////////////////////////////////////////////////////////////////////////////////////// BOSS /////////////////////////////////////////////////////////////////////////////////////////
	if (P.CRI == 9) {
		for (int i = 0; i < W.Rooms[9].Boss.size(); i++) {
			BossState& B = W.Rooms[9].Boss[i]; 

			if (!B.Dead) {
				W.Rooms[9].Grid[B.X][B.Y] = P.B;

				//Check Direction 
				//If Up
				if (B.TarDirection == 1) {
					if (B.Struck) {
						B.Strike = false;
						B.PreX = B.X;
						for (int i = 0; i < B.LList.size(); i++) {
							W.Rooms[9].Grid[B.LList[i]][B.Y] = '0';
						}
						B.LList.clear();
						B.Struck = false;
					}
					if (B.Strike) {
						for (int i = 0; i < B.LList.size(); i++) {
							W.Rooms[9].Grid[B.LList[i]][B.Y] = P.BL;
							if (B.LList[i] == P.X && B.Y == P.Y) Respawn(W, P);
						}
						B.Struck = true;
					}
					else {
						B.PreX--;
						if (W.Rooms[9].Grid[B.PreX][B.Y] == '0' || W.Rooms[9].Grid[B.PreX][B.Y] == P.c) {
							B.LList.push_back(B.PreX);
						}
						else B.Strike = true;
						for (int i = 0; i < B.LList.size(); i++) {
							W.Rooms[9].Grid[B.LList[i]][B.Y] = P.BC;
						}
					}
				}
				//If Down
				if (B.TarDirection == 2) {
					if (B.Struck) {
						B.Strike = false;
						B.PreX = B.X;
						for (int i = 0; i < B.LList.size(); i++) {
							W.Rooms[9].Grid[B.LList[i]][B.Y] = '0';
						}
						B.LList.clear();
						B.Struck = false;
					}
					if (B.Strike) {
						for (int i = 0; i < B.LList.size(); i++) {
							W.Rooms[9].Grid[B.LList[i]][B.Y] = P.BL;
							if (B.LList[i] == P.X && B.Y == P.Y) Respawn(W, P);
						}
						B.Struck = true;
					}
					else {
						B.PreX++;
						if (W.Rooms[9].Grid[B.PreX][B.Y] == '0' || W.Rooms[9].Grid[B.PreX][B.Y] == P.c) {
							B.LList.push_back(B.PreX);
						}
						else B.Strike = true;
						for (int i = 0; i < B.LList.size(); i++) {
							W.Rooms[9].Grid[B.LList[i]][B.Y] = P.BC;
						}
					}
				}
				//If Left
				if (B.TarDirection == 3) {
					if (B.Struck) {
						B.Strike = false;
						B.PreY = B.Y;
						for (int i = 0; i < B.LList.size(); i++) {
							W.Rooms[9].Grid[B.X][B.LList[i]] = '0';
						}
						B.LList.clear();
						B.Struck = false;
					}
					if (B.Strike) {
						for (int i = 0; i < B.LList.size(); i++) {
							W.Rooms[9].Grid[B.X][B.LList[i]] = P.BL;
							if (B.X == P.X && B.LList[i] == P.Y) Respawn(W, P);
						}
						B.Struck = true;
					}
					else {
						B.PreY--;
						if (W.Rooms[9].Grid[B.X][B.PreY] == '0' || W.Rooms[9].Grid[B.X][B.PreY] == P.c) {
							B.LList.push_back(B.PreY);
						}
						else B.Strike = true;
						for (int i = 0; i < B.LList.size(); i++) {
							W.Rooms[9].Grid[B.X][B.LList[i]] = P.BC;
						}
					}
				}
				//If Right
				if (B.TarDirection == 4) {
					if (B.Struck) {
						B.Strike = false;
						B.PreY = B.Y;
						for (int i = 0; i < B.LList.size(); i++) {
							W.Rooms[9].Grid[B.X][B.LList[i]] = '0';
						}
						B.LList.clear();
						B.Struck = false;
					}
					if (B.Strike) {
						for (int i = 0; i < B.LList.size(); i++) {
							W.Rooms[9].Grid[B.X][B.LList[i]] = P.BL;
							if (B.X == P.X && B.LList[i] == P.Y) Respawn(W, P);
						}
						B.Struck = true;
					}
					else {
						B.PreY++;
						if (W.Rooms[9].Grid[B.X][B.PreY] == '0' || W.Rooms[9].Grid[B.X][B.PreY] == P.c) {
							B.LList.push_back(B.PreY);
						}
						else B.Strike = true;
						for (int i = 0; i < B.LList.size(); i++) {
							W.Rooms[9].Grid[B.X][B.LList[i]] = P.BC;
						}
					}
				}
			}
			else {
				if (B.TarDirection == 3 || B.TarDirection == 4) {
					for (int i = 0; i < B.LList.size(); i++) {
					W.Rooms[9].Grid[B.X][B.LList[i]] = '0';
					}
				}
				if (B.TarDirection == 1 || B.TarDirection == 2) {
					for (int i = 0; i < B.LList.size(); i++) {
						W.Rooms[9].Grid[B.LList[i]][B.Y] = '0';
					}
				}
			}
		}
	}
}
// **************************************** INPUT **************************************************
void PlayerInput(PlayerState& P, WorldState& W) {
	
	// Get instant Player input and convert to lower case 
	int Input = tolower(_getch());
	//Previous position for current move = Players current position before the input
	P.PreviewX = P.X;
	P.PreviewY = P.Y;
	// Exit command
	if (Input == 'q') {
		P.WantsToExit = true;
	}
	// Add or subtract Player position depending on input 
	else if (Input == 'w') { P.Facing = 1; P.X--; }
	else if (Input == 's') { P.Facing = 3; P.X++; }
	else if (Input == 'a') { P.Facing = 4; P.Y--; }
	else if (Input == 'd') { P.Facing = 2; P.Y++; }
	// Arrow keys 
	// First else if statement is necessary for some reason 
	else if (Input == 224) {
		P.AtEchoX = P.X;
		P.AtEchoY = P.Y;
	}
	// UP North
	else if ((Input == 104) && (P.CanEcho)) {
		P.Echoing = true;
		P.EchoingN = true;
		P.Facing = 1;
	}
	// RIGHT East
	else if ((Input == 109) && (P.CanEcho)) {
		P.Echoing = true;
		P.EchoingE = true;
		P.Facing = 2;
	}
	// DOWN South
	else if ((Input == 112) && (P.CanEcho)) {
		P.Echoing = true;
		P.EchoingS = true;
		P.Facing = 3;
	}
	// LEFT West
	else if ((Input == 107) && (P.CanEcho)) {
		P.Echoing = true;
		P.EchoingW = true;
		P.Facing = 4;
	}
	else if (Input == 'x') Inventory(W, P);
	else if (Input == 'c') Map(W, P);
	else if (Input == 'v') Hints(W, P); 
	
	// Combat 
	else if (Input == 'e') {
		if (P.SwordFound) {
			switch (P.Facing) {
// Attacking UP
			case 1:
				P.PreSX = (P.X - 1);
				//Error Check
				if (P.PreSX >= 0) {
					if (W.Rooms[P.CRI].Grid[P.PreSX][P.Y] == P.eH) {
						P.PreSChar = '0';
					}
					else if (W.Rooms[P.CRI].Grid[P.PreSX][P.Y] == P.E || W.Rooms[P.CRI].Grid[P.PreSX][P.Y] == P.G) {
						Kill(W, P, P.PreSX, P.Y);
						P.PreSChar = '0';
					}
					//If Boss
					else if (W.Rooms[P.CRI].Grid[P.PreSX][P.Y] == P.B) {
						KillBoss(W, P, P.PreSX, P.Y);
						P.PreSChar = '0';
					}
					else P.PreSChar = W.Rooms[P.CRI].Grid[P.PreSX][P.Y];
					W.Rooms[P.CRI].Grid[P.PreSX][P.Y] = '^';
					P.Attacking = true;
				}
				break;
// Attacking RIGHT 
			case 2:
				P.PreSY = (P.Y + 1);
				if (P.PreSY < W.Rooms[P.CRI].MaxGrid) {
					//If Echo
					if (W.Rooms[P.CRI].Grid[P.X][P.PreSY] == P.eH) {
						P.PreSChar = '0';
					}
					//If Enemy
					else if (W.Rooms[P.CRI].Grid[P.X][P.PreSY] == P.E || W.Rooms[P.CRI].Grid[P.X][P.PreSY] == P.G) {
						Kill(W, P, P.X, P.PreSY);
						P.PreSChar = '0';
					}
					//If Boss
					else if (W.Rooms[P.CRI].Grid[P.X][P.PreSY] == P.B) {
						KillBoss(W, P, P.X, P.PreSY);
						P.PreSChar = '0';
					}
					else P.PreSChar = W.Rooms[P.CRI].Grid[P.X][P.PreSY];
					W.Rooms[P.CRI].Grid[P.X][P.PreSY] = '>';
					P.Attacking = true;
				} 
				break;
// Attacking DOWN
			case 3:
				P.PreSX = (P.X + 1);
				if (P.PreSX < W.Rooms[P.CRI].MaxGrid) {
					//If Echo
					if (W.Rooms[P.CRI].Grid[P.PreSX][P.Y] == P.eH) {
						P.PreSChar = '0';
					}
					//If Enemy
					else if (W.Rooms[P.CRI].Grid[P.PreSX][P.Y] == P.E || W.Rooms[P.CRI].Grid[P.PreSX][P.Y] == P.G) {
						Kill(W, P, P.PreSX, P.Y);
						P.PreSChar = '0';
					}
					//If Boss
					else if (W.Rooms[P.CRI].Grid[P.PreSX][P.Y] == P.B) {
						KillBoss(W, P, P.PreSX, P.Y);
						P.PreSChar = '0';
					}
					else P.PreSChar = W.Rooms[P.CRI].Grid[P.PreSX][P.Y];
					W.Rooms[P.CRI].Grid[P.PreSX][P.Y] = 'v';
					P.Attacking = true;
				}
				break;
// Attacking LEFT
			case 4:
				P.PreSY = (P.Y - 1);
				if (P.PreSY >= 0) {
					//If Echo
					if (W.Rooms[P.CRI].Grid[P.X][P.PreSY] == P.eH) {
						P.PreSChar = '0';
					}
					//If Enemy
					else if (W.Rooms[P.CRI].Grid[P.X][P.PreSY] == P.E || W.Rooms[P.CRI].Grid[P.X][P.PreSY] == P.G) {
						Kill(W, P, P.X, P.PreSY);
						P.PreSChar = '0';
					}
					//If Boss
					else if (W.Rooms[P.CRI].Grid[P.X][P.PreSY] == P.B) {
						KillBoss(W, P, P.X, P.PreSY);
						P.PreSChar = '0';
					}
					else P.PreSChar = W.Rooms[P.CRI].Grid[P.X][P.PreSY];
					W.Rooms[P.CRI].Grid[P.X][P.PreSY] = '<';
					P.Attacking = true;
				}
				break;
			}

		}
		else {
			P.PreSX = P.X;
			P.PreSY = P.Y; 
			P.PreSChar = '0';
		}
	}
	////////////////////////////////////////////IF NOT NULL///////////////////////////////////////////////////
	if ((P.X < W.Rooms[P.CRI].MaxGrid) && (P.X >= 0) && (P.Y < W.Rooms[P.CRI].MaxGrid) && (P.Y >= 0)) {
		////////////////////////////////////////////IF WALL///////////////////////////////////////////////////
		if (W.Rooms[P.CRI].Grid[P.X][P.Y] == W.v || W.Rooms[P.CRI].Grid[P.X][P.Y] == W.h || W.Rooms[P.CRI].Grid[P.X][P.Y] == W.c || W.Rooms[P.CRI].Grid[P.X][P.Y] == W.C || W.Rooms[P.CRI].Grid[P.X][P.Y] == W.l || W.Rooms[P.CRI].Grid[P.X][P.Y] == W.L || W.Rooms[P.CRI].Grid[P.X][P.Y] == W.T || W.Rooms[P.CRI].Grid[P.X][P.Y] == W.t || W.Rooms[P.CRI].Grid[P.X][P.Y] == W.F || W.Rooms[P.CRI].Grid[P.X][P.Y] == W.f) {
			P.X = P.PreviewX;
			P.Y = P.PreviewY;
		}
		///////////////////////////////////////IF DOOR////////////////////////////////////////////////////// 
		else if (W.Rooms[P.CRI].Grid[P.X][P.Y] == W.D || W.Rooms[P.CRI].Grid[P.X][P.Y] == W.LD) {
			// For each possible exit in the room check if the Players position currently matches
			// If yes then set Player position to correct entrance position and change the CRI to the target room 
			for (int i = 0; i < W.Rooms[P.CRI].Exits.size(); i++) {
				if ((P.X == W.Rooms[P.CRI].Exits[i].y) && (P.Y == W.Rooms[P.CRI].Exits[i].x)) {
					//Check if door is locked and unlock if keys is 1 or greater 
					if (W.Rooms[P.CRI].Grid[P.X][P.Y] == W.LD) {
						if (P.KeyNum >= 1) {
							W.Rooms[P.CRI].Grid[P.X][P.Y] = W.D;
							P.KeyNum -= 1;
						}
					}
					// Door is unlocked  
					if (W.Rooms[P.CRI].Grid[P.X][P.Y] == W.D) {
						// New P positions
						P.X = W.Rooms[P.CRI].Exits[i].targety;
						P.Y = W.Rooms[P.CRI].Exits[i].targetx;
						// Replace the old
						W.Rooms[P.CRI].Grid[P.PreviewX][P.PreviewY] = '0';
						if (P.Echoing) {
							W.Rooms[P.CRI].Grid[P.EchoX][P.EchoY] = '0';
						}
						// Change the room 
						P.CRI = W.Rooms[P.CRI].Exits[i].targetRoom;
						W.Rooms[P.CRI].Grid[P.X][P.Y] = P.c;
						P.EchoX = P.X;
						P.EchoY = P.Y;
						P.Echoing = false;
						P.EchoingN = false;
						P.EchoingS = false;
						P.EchoingE = false;
						P.EchoingW = false;
						// Update the goal progression 
						switch (P.CRI) {
						case 0:
							P.RespawnCRI = 0;
							P.RespawnX = 2;
							P.RespawnY = 2;
							break;
						case 2:
							if (P.GoalProgression == 0) {
								P.Goal = "Find the Key Pieces in the shops";
								P.GoalProgression++;
							}
							if (P.GoalProgression == 1 && P.KeyNum == 1) {
								P.Goal = "Unlock the Door";
								P.GoalProgression++;
							}
							break;
						case 5:
							P.RespawnCRI = 5;
							P.RespawnX = 3;
							P.RespawnY = 3;

							P.GoalProgression = 2;
							if (P.GoalProgression == 2) {
								P.Goal = "Take the sword and head south to the castle";
								P.GoalProgression++;
							}
							break;
						case 7:
							if (P.GoalProgression == 3) {
								P.Goal = "Unlock the door and return to the library";
								P.GoalProgression++;
							}
							break; 
						case 8:
							P.RespawnCRI = 8;
							P.RespawnX = 5;
							P.RespawnY = 2;
							break; 
						}

					}
					//Door is still locked
					else {
						P.X = P.PreviewX;
						P.Y = P.PreviewY;
					}
				}
			}
		}
		///////////////////////////////////////IF ENEMY////////////////////////////////////////////////////// 
		else if (W.Rooms[P.CRI].Grid[P.X][P.Y] == P.E || W.Rooms[P.CRI].Grid[P.X][P.Y] == P.G || W.Rooms[P.CRI].Grid[P.X][P.Y] == P.BL || W.Rooms[P.CRI].Grid[P.X][P.Y] == P.B) {
			Respawn(W, P);
		}
		// Otherwise new position becomes 9 and old position becomes a 0 
		else {
			//Collecting Key Piece
			if (W.Rooms[P.CRI].Grid[P.X][P.Y] == P.k) {
				P.KeyNum += 0.5;
				Color(14);
				for (int i = 0; i < 4; i++) printf("\t");
				printslow("KEY PEICE AQUIRED\n", 70);
				char input = 0;
				while (input == 0) {
					input = tolower(_getch());
				}
			}
			//Collecting Sword
			if (W.Rooms[P.CRI].Grid[P.X][P.Y] == P.S) {
				P.SwordFound = true;
				P.Sword = "It's Dangerous";
				Color(11);
				for (int i = 0; i < 4; i++) printf("\t");
				printslow("TAKE THIS!\n", 70);
				char input = 0;
				while (input == 0) {
					input = tolower(_getch());
				}
			}
			//Collecting Lever
			if (W.Rooms[P.CRI].Grid[P.X][P.Y] == '!') {
		//Add Exit from 2 to 9
				RoomExits R2ExitTo9{};
				AddExit(R2ExitTo9, 0, 3, 9, 6, 5);
				W.Rooms[1].Exits.push_back(R2ExitTo9);
				W.Rooms[1].Grid[3][0] = W.D;
				W.MapList.push_back(W.Room9);
		//Add Exit from 2 to 8
				RoomExits R2ExitTo8{};
				AddExit(R2ExitTo8, 7, 8, 8, 3, 1);
				W.Rooms[1].Exits.push_back(R2ExitTo8);
				W.Rooms[1].Grid[8][7] = W.D;
				Color(7);
				for (int i = 0; i < 4; i++) printf("\t");
				printslow("Map updated\n", 70);
				for (int i = 0; i < 4; i++) printf("\t");
				printslow("The lever clicks and a door opens somewhere in the library.\n", 70);
				char input = 0;
				while (input == 0) {
					input = tolower(_getch());
				}
			}
			W.Rooms[P.CRI].Grid[P.X][P.Y] = P.c;
			// unless the new position is the old position then nothing changes 
			if ((P.X != P.PreviewX) || (P.Y != P.PreviewY)) {
				W.Rooms[P.CRI].Grid[P.PreviewX][P.PreviewY] = '0';
			}
		}
	}
	else {
		P.X = P.PreviewX;
		P.Y = P.PreviewY;
		Color(8);
		for (int i = 0; i < 4; i++) printf("\t");
		printslow("ERROR OUT OF BOUNDS", 40); 
	}
}

void CleanupGame(PlayerState& P, WorldState& W) {
	if (P.WontheGame) {
		Color(7); 
		printf("YAY YOU WON!!!\n");
	}
}
	
	
