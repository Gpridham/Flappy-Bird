#include <SFML/Graphics.hpp>
#include "Menu.h"




Menu::Menu()
{
	m_font.loadFromFile("Font/OpenSans-Regular.ttf");
	m_play.setString("Play");
	m_play.setFont(m_font);
	m_playX = 50;
	m_playY = 280;

}

void Menu::startMenu(sf::RenderWindow& window)
{
	m_play.setPosition(m_playX, m_playY);
	m_play.setStyle(sf::Text::Bold);
	m_play.setCharacterSize(25);
	m_play.setFillColor(sf::Color::Color(255, 69, 0)); // sets to color orangered
	window.draw(m_play);
}
void Menu::setPosition(int x, int y)
{
	m_playX = x;
	m_playY = y;

	m_play.setPosition(m_playX, m_playY);

}
sf::FloatRect Menu::getBounds()
{
	return m_play.getGlobalBounds();
}
