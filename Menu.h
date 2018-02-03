//#pragma once --- DONT KNOW WHAT THIS IS

#ifndef MENU_H
#define MENU_H



class Menu
{
	int m_playX;
	int m_playY;
	sf::Text m_play;
	sf::Font m_font;


public:

	Menu(); // default constructor

	void startMenu(sf::RenderWindow& window);
	void setPosition(int x, int y);
	sf::FloatRect getBounds();
};


#endif
