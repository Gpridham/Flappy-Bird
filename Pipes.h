//#pragma once

#ifndef PIPES_H
#define PIPES_H


class Pipes
{
	sf::Texture m_pipeUp;
	sf::Texture m_pipeDown;

	sf::Sprite m_pipeUpSprite;
	sf::Sprite m_pipeDownSprite;

	const std::string m_filenameUp;
	const std::string m_fileDown;

	double m_x;
	double m_upY;
	double m_downY;



public:


	Pipes(const std::string filenameUp = "Images/pipeUp.png" , const std::string fileDown = "Images/pipeDown.png");

	void initPipesDefault(double x = 288, double upY = 202, double downY = -48);

	// Min and Max values of the up pipes
	void randomPipeHeights(int min, int max);

	void resetPipes(int min, int max);

	void swapPositions(double x, double upY, double downY);

	void setX(double x);

	void setPipePosition();

	double getX();

	double getUpY();

	double getDownY();

	void drawPipes(sf::RenderWindow & window);

	void pipeMove(double speed);

	sf::FloatRect getUpBounds();

	sf::FloatRect getDownBounds();


};

#endif
