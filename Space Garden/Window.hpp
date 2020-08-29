#pragma once
#include "Tools.hpp"
#include "View.hpp"

// Class for a Window With a view automaticaly adapted
class Windows
{
public:
	Windows(sf::VideoMode VideoMode, std::string Name, int _FrameRate = 120, sf::Uint32 Style = sf::Style::Default)
	{
		m_videomode = VideoMode;
		m_Name = Name;
		m_Fps = _FrameRate;
		m_Style = Style;
		m_VSync = true;
		m_Window.create(m_videomode, m_Name, m_Style);
		m_Window.setFramerateLimit(m_Fps);
		m_Window.setVerticalSyncEnabled(m_VSync);
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

	int getFrameRate() { return m_Fps; };

	sf::Uint32 getStyle() { return m_Style; };

	bool getVerticalSync() { return m_VSync; };

	void setFrameRate(int New_Fps) { m_Fps = New_Fps; m_Window.setFramerateLimit(m_Fps); };

	void setStyle(sf::Uint32 Style) 
	{ 
		m_Style = Style;

		m_Window.close();  
		m_Window.create(m_videomode, m_Name, m_Style);
		m_Window.setFramerateLimit(m_Fps);
		m_Window.setVerticalSyncEnabled(m_VSync);
	};

	void setVerticalSync(bool VSync) { m_VSync = VSync;  m_Window.setVerticalSyncEnabled(m_VSync); };

private:
	sf::VideoMode m_videomode;
	std::string m_Name;
	sf::Uint32 m_Style;
	sf::RenderWindow m_Window;
	Views m_view;
	sf::Event m_event;
	int m_Fps;
	bool m_VSync;
};
extern Windows win;