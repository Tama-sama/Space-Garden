#pragma once
#include "Tools.hpp"

// Class for a adapatative view
class Views
{
public:
	Views()
	{
		// Initializing variables
		m_defaultDesktopMode = sf::VideoMode::getDesktopMode();
		m_defaultVideoMode = sf::Vector2i(1920, 1080);
		m_ratioResolution = sf::Vector2f((float)m_defaultDesktopMode.width / m_defaultVideoMode.x, (float)m_defaultDesktopMode.height / m_defaultVideoMode.y);
		m_rectViewPort = sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f);
		m_rectView = sf::FloatRect((float)m_defaultDesktopMode.width / 2, (float)m_defaultDesktopMode.height / 2, m_defaultDesktopMode.width / m_ratioResolution.x * m_rectViewPort.width, m_defaultDesktopMode.height / m_ratioResolution.y * m_rectViewPort.height);
		m_PosView = sf::Vector2f(m_rectView.width / 2, m_rectView.height / 2);

		// sf::View
		m_view.reset(m_rectView);
		m_view.setCenter(m_PosView);
		m_view.setViewport(m_rectViewPort);
	};
	~Views() {};

	/////////////
	/// \brief get the position of the center af the view
	/// \return sf::vector2f
	/////////////
	sf::Vector2f getCenterPos() const { return m_PosView; };

	/////////////
	/// \brief get the size of the view
	/// \return sf::vector2i
	/////////////
	sf::Vector2i getSize() const { return sf::Vector2i(m_view.getSize()); };

	/////////////
	/// \brief get the ratio of the default and actual size
	/// \return sf::vector2f
	/////////////
	sf::Vector2f getRatio() const { return m_ratioResolution; };

	/////////////
	/// \brief get the sfml view 
	/// \return sf::View&
	/////////////
	sf::View& View() { return m_view; };

	/////////////
	/// \brief redefine the zone the view cover
	/// \param sf::FloatRect new size and zone
	/////////////
	void setRectView(sf::FloatRect _rectview) { m_rectView = _rectview;	m_view.reset(m_rectView); };

	/////////////
	/// \brief set the center of the view to a new position
	/// \param sf::Vector2f new pos
	/////////////
	void SetCenterPosition(sf::Vector2f _position) { m_PosView = _position;	m_view.setCenter(m_PosView); };


private:
	sf::View m_view;
	sf::Vector2i m_defaultVideoMode;
	sf::VideoMode m_defaultDesktopMode;
	sf::Vector2f m_ratioResolution;
	sf::FloatRect m_rectViewPort;
	sf::Vector2f m_PosView;
	sf::FloatRect m_rectView;
};