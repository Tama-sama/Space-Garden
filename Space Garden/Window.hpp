#pragma once
#include "Tools.hpp"
#include "View.hpp"

// Class for a Window With a view automaticaly adapted
class Windows
{
public:
	Windows(sf::VideoMode VideoMode, std::string Name, int _FrameRate = 120)
	{
		m_Window.create(VideoMode, Name);
		m_Window.setFramerateLimit(_FrameRate);

		// histoire d'initialiser car il fait chier avec c'est warnings alors qu'il existe un constructeur vide
		m_event = sf::Event();
	};
	~Windows() {};

	/////////////
	/// \brief get if the Window is open
	/// \return bool
	/////////////
	bool isDone() { return !m_Window.isOpen(); };

	/////////////
	/// \brief get a poiter to the RenderWindow
	/// \return	sf::RenderWindow&
	/////////////
	sf::RenderWindow& Window() { return m_Window; };

	/////////////
	/// \brief get a poiter to the View
	/// \return	Views&
	/////////////
	Views& getView() { return m_view; };

	/////////////
	/// \brief get a poiter to events
	/// \return	sf::Event&
	/////////////
	sf::Event& Events() { return m_event; };

private:
	sf::RenderWindow m_Window;
	Views m_view;
	sf::Event m_event;
};
extern Windows win;