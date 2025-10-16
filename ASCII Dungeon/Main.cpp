#include <stdlib.h>
#include <Windows.h>
#include "Core.h"
#include "Functions.h"
#include "Initialize.h"
#include <vector>

int main()
{
	
	PlayerState playerState = {};
	WorldState worldState = {};
	EnemyState enemyState = {}; 

	//Found in Initialize for ease of access 
	MainMenu(); 
	InitializeGame(playerState, worldState);

	while (!playerState.WantsToExit) {
		// Found in Core
		RenderGame(playerState, worldState);
		PlayerInput(playerState, worldState);
		UpdateGame(playerState, worldState);
		system("cls"); 
	}
	//Literally does nothing might display stats 
	CleanupGame(playerState, worldState);
	Color(7);
	system("pause"); 
	return 0;
}
// Just some enemy pathing I'm hiding here so I don't have to look at it 
/* Idle state moving up and down
			if (E.MoveN) {
				E.X--;
				if (W.Rooms[P.CRI].Grid[E.X][E.Y] == W.v) {
					E.X = E.PreX;
					E.MoveN = false;
				}
				else {
					W.Rooms[P.CRI].Grid[E.X][E.Y] = P.E;
					W.Rooms[P.CRI].Grid[E.PreX][E.PreY] = '0';
				}
			}
			if (!E.MoveN) {
				E.X++;
				if (W.Rooms[P.CRI].Grid[E.X][E.Y] == W.v) {
					E.X = E.PreX;
					E.MoveN = true;
					E.X--;
					W.Rooms[P.CRI].Grid[E.X][E.Y] = P.E;
					W.Rooms[P.CRI].Grid[E.PreX][E.PreY] = '0';
				}
				else {
					W.Rooms[P.CRI].Grid[E.X][E.Y] = P.E;
					W.Rooms[P.CRI].Grid[E.PreX][E.PreY] = '0';
				}
			}
			*/