#pragma once
#include "Core.h"; 

void Color(int color); 

void PrintScreen(WorldState& World, PlayerState& P);

int GetEnemyIndex(PlayerState& P, WorldState& W); 

void printslow(const char Input[], int Delay); 

void Inventory(WorldState& W, PlayerState& P);

void Map(WorldState& W, PlayerState& P);

void Hints(WorldState& W, PlayerState& P);

void Respawn(WorldState& W, PlayerState& P);

void Kill(WorldState& W, PlayerState& P, int X, int Y);

void KillBoss(WorldState& W, PlayerState& P, int X, int Y); 

void debugI(int i); 

void debugC(char i);

