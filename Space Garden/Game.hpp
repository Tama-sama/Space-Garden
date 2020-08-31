#pragma once
#include "Tools.hpp"
#include "Player.hpp"


extern Player Player1;
extern Player Player2;


void RemoveDeadPlayerShoots();
void RemoveDeadBuffs();
void BuffsCollisions(Player& _Player);
void PlayerShootsColisions();
void RemoveDeadEnnemies();
void RemoveDeadEnnemiesShoots();
void RemoveDeadExplosions();

void UpdateGame();
void UpdateGamePause();

void DisplayGame();
void DisplayGamePause();

void GameInit();