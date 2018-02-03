//#pragma once


#include "Pipes.h"
#ifndef BIRD_H
#define BIRD_H

class Bird
{
	sf::Texture m_normalState;
	sf::Texture m_flapUp;
	sf::Texture m_flapDown;
	sf::Sprite m_bird;

	double m_x;
	double m_y;
	double m_speed;
	int m_angle;

public:
	// Bird Default constructor loads textures
	Bird(double x = 45 , double y = 200 );

	void defaultPosition();

	void birdUp(double speed, int angle);

	void birdDown(double speed, int angle);

	void birdNormalRot();


	void birdFlapUp();


	void birdFlapDown();

	void birdFlapNorm();


	void birdSetPosition();

	sf::FloatRect getBounds();

	double getX();

	double getY();

	void drawBird(sf::RenderWindow & window);

	bool collision(Pipes pipes);

};

#endif
