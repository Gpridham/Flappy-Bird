#include <SFML/Graphics.hpp>
#include<iostream>
#include "Bird.h"
#include "Pipes.h"

Bird::Bird(double x , double y )
	: m_x(x), m_y(y)
{
	if (!m_normalState.loadFromFile("Images/bird-02.png"))
		std::cout << "Problem loading bird-02" << std::endl;
	if (!m_flapUp.loadFromFile("Images/bird-01.png"))
		std::cout << "Problem loading bird-01" << std::endl;
	if (!m_flapDown.loadFromFile("Images/bird-03.png"))
		std::cout << "Problem loading bird-03" << std::endl;

	m_bird.setTexture(m_normalState);
	m_bird.setOrigin(17, 12);
}

void Bird::defaultPosition()
{
	m_bird.setOrigin(17, 12);
	m_x = 45;
	m_y = 200;
	m_bird.setTexture(m_normalState);
	m_bird.setRotation(0);
}

void Bird::birdUp(double speed, int angle)
{
	m_speed = speed;
	m_angle = angle;
	m_y = m_y - speed;
	m_bird.setRotation(m_angle);

	if (m_y > 315)
		m_y = 315;
	m_bird.move(0, m_y);


}
void Bird::birdDown(double speed, int angle)
{
	m_speed = speed;
	m_angle = angle;
	m_y = m_y + m_speed;
	m_bird.setRotation(m_angle);
	//std::cout << m_y << std::endl;

	// bird cant go below ground lvl
	if (m_y  > (315 - 17)) // 17 is to move from the orgin point in the middle of bird
		m_y = 315 - 17;
	m_bird.move(0, m_y);
}
void Bird::birdNormalRot()
{
	m_angle = 0;
	m_bird.setRotation(m_angle);
}
void Bird::birdFlapUp()
{
	m_bird.setTexture(m_flapUp);
}

void Bird::birdFlapDown()
{
	m_bird.setTexture(m_flapDown);
}
void Bird::birdFlapNorm()
{
	m_bird.setTexture(m_normalState);
}

void Bird::birdSetPosition()
{
	m_bird.setPosition(m_x, m_y);
}

sf::FloatRect Bird::getBounds()
{
	return m_bird.getGlobalBounds();
}
double Bird::getX()
{
	return m_x;
}
double Bird::getY()
{
	return m_y;
}

void Bird::drawBird(sf::RenderWindow & window)
{
	window.draw(m_bird);
}
bool Bird::collision(Pipes pipes)
{
	if (((m_x + 17) >= pipes.getX())  && ((m_x - 17) <= (pipes.getX() + 30))) // width of pipes = 30
	{
	
		if (((pipes.getDownY() + 160 + 12) < m_y) && ((pipes.getUpY() - 12) > m_y)) // height of pipes = 160
			return false;
		else
			return true;
	}
	else
		return false;

}