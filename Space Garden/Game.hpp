#pragma once
#include "Tools.hpp"
#include "Player.hpp"

#define SIZE_BUFFS 30
#define RADIUS_PLAYER_SHOOT 11
#define RADIUS_ENNEMIES_SHOOT 9
#define RADIUS_ENNEMIES 45

extern Player Player1;
extern Player Player2;

////////////////
/// \brief Remove all Player Shoots with 0 life
////////////////
void RemoveDeadPlayerShoots();

////////////////
/// \brief Remove all Buffs with 0 life
////////////////
void RemoveDeadBuffs();

////////////////
/// \brief Check the collision between buffs and a player
/// \param _Player player to check collision
////////////////
void BuffsCollisions(Player& _Player);

////////////////
/// \brief Check the collision between Players shoots and ennemies
////////////////
void PlayerShootsColisions();

////////////////
/// \brief Remove all ennemies with 0 life
////////////////
void RemoveDeadEnnemies();

////////////////
/// \brief Remove all ennemies shoots with 0 life
////////////////
void RemoveDeadEnnemiesShoots();

////////////////
/// \brief Remove all explosions with 0 life
////////////////
void RemoveDeadExplosions();



////////////////
/// \brief Init of the Game
////////////////
void GameInit();

////////////////
/// \brief Update of the Game
////////////////
void UpdateGame();

////////////////
/// \brief Update of the in-game menu
////////////////
void UpdateGamePause();

////////////////
/// \brief Switch between Game to save state
////////////////
void UpdateGameToSave();

////////////////
/// \brief Switch between Game to game menu
////////////////
void UpdateGameToMenu();

////////////////
/// \brief Display of the Game
////////////////
void DisplayGame();

////////////////
/// \brief Display of the in-game menu
////////////////
void DisplayGamePause();


