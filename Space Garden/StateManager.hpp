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
extern bool Loading;
extern bool can_Switch;

////////////////
/// \brief Load ressources of a state, change state and remove others ressources
/// \param NextState state need to go
////////////////
void ChangeState(State NextStage);

////////////////
/// \brief Load ressources of a state
/// \param NextState state need to load
////////////////
void LoadNextState(State NextState);

////////////////
/// \brief Managements of inits based on state
////////////////
void InitManager();

////////////////
/// \brief Managements of updates based on state
////////////////
void UpdateManager();

////////////////
/// \brief Managements of diplays based on state
////////////////
void DisplayManager();

////////////////
/// \brief Managements of events
////////////////
void EventsManager();

////////////////
/// \brief Display some dev infos like HitBoxs etc ...
////////////////
void DisplayDevMode();