#pragma once
#include "Tools.hpp"
#include "Player.hpp"

#define SIZE_BUFFS 30
#define RADIUS_PLAYER_SHOOT 11
#define RADIUS_ENNEMIES_SHOOT 9
#define RADIUS_ENNEMIES 45

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
void UpdateGameToSave();
void UpdateGameToMenu();


void DisplayGame();
void DisplayGamePause();

void GameInit();

