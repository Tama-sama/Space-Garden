#pragma once
#include "Tools.hpp"

// state enum
enum class State
{
	RTNULL,
	ALL,
	INTRO,
	MAIN_MENU,
	GAME,
	SAVE,
};
extern State state;

/////////////
/// \brief Managements of updates based on state
/// \param Windows
/// /////////////
void UpdateManager();

/////////////
/// \brief Managements of diplays based on state
/// \param Windows
/// /////////////
void DisplayManager();

void EventsManager();

void ChangeState(State NextStage);

void InitManager();

void Intro();