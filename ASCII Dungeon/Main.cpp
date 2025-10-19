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
	//MainMenu(); 
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