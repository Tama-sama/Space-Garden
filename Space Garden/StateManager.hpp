#pragma once
#include "Tools.hpp"

// state enum
enum class State
{
	RTNULL,
	MAIN_MENU,
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