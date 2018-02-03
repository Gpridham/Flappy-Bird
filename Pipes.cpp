#include <SFML/Graphics.hpp>
#include "Pipes.h"
#include <iostream>



Pipes::Pipes(const std::string filenameUp , const std::string fileDown )
	: m_filenameUp(filenameUp), m_fileDown(fileDown)
{
	// CONSTRUCTOR
	if (!m_pipeUp.loadFromFile(m_filenameUp))
		std::cout << "Error Loading Pipe image" << std::endl;
	if (!m_pipeDown.loadFromFile(m_fileDown))
		std::cout << "Error Loading Pipe image" << std::endl;


	m_pipeUpSprite.setTexture(m_pipeUp);
	m_pipeDownSprite.setTexture(m_pipeDown);

}

void Pipes::initPipesDefault(double x , double upY , double downY )
{
	m_x = x;
	m_upY = upY;
	m_downY = downY;
}
// Min and Max values of the up pipes
void Pipes::randomPipeHeights(int min, int max)
{
	m_upY = rand() % (min - max) + max;
	m_downY = m_upY - 90 - 160; // 90 is the Width Gap and 160 is the height of the pipe texture
}
void Pipes::resetPipes(int min, int max)
{
	m_x = 288;
	m_upY = rand() % (min - max) + max;
	m_downY = m_downY = m_upY - 90 - 160;
}
void Pipes::swapPositions(double x, double upY, double downY)
{
	m_x = x;
	m_upY = upY;
	m_downY = downY;

}
void Pipes::setX(double x)
{
	m_x = x;
}
void Pipes::setPipePosition()
{
	m_pipeUpSprite.setPosition(m_x, m_upY);
	m_pipeDownSprite.setPosition(m_x, m_downY);
}


double Pipes::getX()
{
	return m_x;
}

double Pipes::getUpY()
{
	return m_upY;
}
double Pipes::getDownY()
{
	return m_downY;
}


void Pipes::drawPipes(sf::RenderWindow & window)
{
	window.draw(m_pipeDownSprite);
	window.draw(m_pipeUpSprite);
}



void Pipes::pipeMove(double speed)
{
	m_x = m_x - speed;
	m_pipeUpSprite.move(m_x, m_upY);
	m_pipeDownSprite.move(m_x, m_downY);

}

sf::FloatRect Pipes::getUpBounds()
{
	return m_pipeUpSprite.getGlobalBounds();
}

sf::FloatRect Pipes::getDownBounds()
{
	return m_pipeDownSprite.getGlobalBounds();
}