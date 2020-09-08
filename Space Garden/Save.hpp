#pragma once
#include "Tools.hpp"

////////////////
/// \brief Switch between Save state and Menu
////////////////
void UpdateSaveToMenu();

////////////////
/// \brief Update of the save state
////////////////
void UpdateSave();

////////////////
/// \brief Display of the save state
////////////////
void DisplaySave();


extern std::string NameP1;
extern std::string NameP2;
extern bool NameDone[2];