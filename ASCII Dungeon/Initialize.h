#pragma once
#include "Core.h"; 

void AddExit(RoomExits& R, int ExitX, int ExitY, int TarRoom, int TarX, int TarY);

void InitializeGame(PlayerState& Player, WorldState& World);

void MainMenu(); 