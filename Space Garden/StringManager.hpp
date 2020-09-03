#pragma once
#include "Tools.hpp"
#include "StateManager.hpp"

class Strings
{
public:
	Strings() {};
	~Strings() {};
	void Construct(std::string name, std::string string, State state) { m_name = name; m_string = string, m_state = state; };

	std::string getName() const { return m_name; };
	std::string getString() const { return m_string; };
	State getState() const { return m_state; };
	
	bool operator== (const Strings s) const { return m_name == s.m_name && m_string == s.m_string && m_state == s.m_state; };
	bool operator!= (const Strings s) const { return !operator==(s); };

private:
	std::string m_name;
	std::string m_string;
	State m_state = State::RTNULL;
};

extern std::list<Strings*> StringsList;

void LoadStrings(State _state);
std::string getString(std::string Name);
void RemoveStateStrings(State _state);
void RemoveAllStrings();

extern std::string Lang;