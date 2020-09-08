#pragma once 
#include "Tools.hpp"


extern std::string SoloNames[5];
extern int SoloScores[5];

extern std::string DuoNames[5][2];
extern int DuoScores[5][2];
extern int DuoScoresTotal[5];

extern std::string SoloLines[5];
extern std::string DuoLines[5];

extern char ShipsColorsSolo[5];
extern char ShipsColorsDuo[5][2];


////////////////
/// \brief Manage Updates of differents menus
////////////////
void UpdateMenu();

////////////////
/// \brief Switch between Menu state and Game
////////////////
void UpdateMenuToGame();



////////////////
/// \brief Update of the Main Menu
////////////////
void UpdateMainMenu();

////////////////
/// \brief Update of the Ship Selection Menu
////////////////
void UpdateShipMenu();

////////////////
/// \brief Update of the ScoreBoard Menu
////////////////
void UpdateScoreBoardMenu();

////////////////
/// \brief Update of the Option Menu
////////////////
void UpdateOptionMenu();

////////////////
/// \brief Update of the Credits Menu
////////////////
void UpdateCredits();

////////////////
/// \brief Update of the How to play Menu
////////////////
void UpdateHowToPlay();








////////////////
/// \brief Manage Display of differents menus
////////////////
void DisplayMenu();



////////////////
/// \brief Display of the Main Menu
////////////////
void DisplayMainMenu();

////////////////
/// \brief Display of the Ship Selection Menu
////////////////
void DisplayShipSelection();

////////////////
/// \brief Display of the ScoreBoard Menu
////////////////
void DisplayScoreBoardMenu();

////////////////
/// \brief Display of the Option Menu
////////////////
void DisplayOptionMenu();

////////////////
/// \brief Display of the Credits Menu
////////////////
void DisplayCredits();

////////////////
/// \brief Display of the How to play Menu
////////////////
void DisplayHowToPlay();