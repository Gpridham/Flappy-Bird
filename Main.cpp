#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<cstdlib>

#include "Menu.h"
#include "Bird.h"
#include "Pipes.h"
//#include<algorithm> // for std::swap

/*
	BACKGROUND INFO:
	Pipe Dimensions  = 30 X 160
	Gap height   = 90
	Gap Width = 120

	Min height from bottom = 250
	Max height from bottom = 155 

	Min height from top = -95
	Max height from top = 0 
*/


void initPipes(Pipes pipesArray[], int elements)
{
	for (int index = 0; index < elements; index++)
	{
		pipesArray[index].initPipesDefault();
		pipesArray[index].randomPipeHeights(250, 155); // 250 is min from bot. 155 is max from bot
		pipesArray[index].setPipePosition();
	}
}

void swap(Pipes& first, Pipes& second)
{
	
	first.swapPositions(second.getX(), second.getUpY(), second.getDownY());

	return;
}

// not in use.. need to figure out
bool colliding(Bird& bird, sf::Sprite& ground)
{

		return bird.getBounds().intersects(ground.getGlobalBounds());
}

// not in use..
bool colliding(Bird& bird, Pipes& point)
{
	if ((bird.getBounds().intersects(point.getUpBounds()))) 
		//|| (bird.getBounds().intersects(point.getDownBounds())))
	{
		return true;
	}
	else
		return false;
	
}




int main()
{
	static const int SCREEN_WIDTH = 288;
	static const int SCREEN_HEIGHT = 400;
	static const int GAP_HEIGHT = 90;
	static const int GAP_WIDTH = 96;

	

	srand(static_cast<unsigned int>(time(0))); // set initial seed value to system clock
	rand();

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird");
	window.setFramerateLimit(60);


	// beginning of setting background
	sf::Texture land;
	sf::Texture sky;

	if (!land.loadFromFile("Images/land.png"))
		return EXIT_FAILURE;
	if (!sky.loadFromFile("Images/background.png"))
		return EXIT_FAILURE;

	sf::Sprite landSprite[2];
	sf::Sprite skySprite;

	
	landSprite[0].setTexture(land);
	landSprite[1].setTexture(land);
	skySprite.setTexture(sky);

	landSprite[0].setPosition(0, 315);
	landSprite[1].setPosition(336, 315); // 336 is the width of land texture

	skySprite.setPosition(0, -20);
	// end of background setup


	Pipes pipesArray[3];
	Bird bird;

	// initializes the first 3 pipes
	initPipes(pipesArray, 3);
	
	// for the wing flapping
	double count = 0; 

	// for bird movement
	bool keyPressed = false;
	int framesPassed = 0; 
	double downSpeed = 2;
	int angleDown = 1;
	int angleUp = -5;

	// Start Menu
	Menu menu;
	bool play = false;
	bool collision = false;
	
	while (window.isOpen())
	{


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// Make it .. If left click in bounds of play button.. play is true
			// if global bounds of play containts point of left click

			if (menu.getBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) 
			{
				play = true;
				collision = false;
				initPipes(pipesArray, 3);
				angleDown = 1;
				bird.defaultPosition();
			}
			// Check If Space key is pressed and resets the default speed of bird

			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
			{
				keyPressed = true;
				downSpeed = 2;

			}


		}

		// Start of Drawing
		window.clear();
		window.draw(skySprite);

		double speed = 1.5; // speed of ground and pipes

		if (play && !collision)
		{

			// Wings flapping
			if (count >= 3 && count <= 5)
			{
				bird.birdFlapUp();
			}
			else if (count >= 6 && count <= 8)
			{
				bird.birdFlapDown();
				if (count == 8)
					count = 0;
			}
			else
				bird.birdFlapNorm();


			// bird movement and angle of bird
			if (keyPressed)
			{
				angleDown = 0;
				framesPassed++;
				bird.birdUp(4, angleUp);
				//std::cout << framesPassed << std::endl;

				if (framesPassed > 10)
				{
					angleUp--;
					keyPressed = false;
					framesPassed = 0;
				}
			}
			else
			{

				if (angleDown < 90)
				{
					angleDown = angleDown + 2;
				}
				else
					bird.birdFlapNorm();

				angleUp = -5;
				bird.birdDown(downSpeed, angleDown);

				downSpeed = downSpeed + 0.01;

			}



			// Keeps the pipes moving
			pipesArray[0].pipeMove(speed);
			if (pipesArray[0].getX() <= SCREEN_WIDTH - GAP_WIDTH - 30)
				pipesArray[1].pipeMove(speed);

			if (pipesArray[1].getX() <= SCREEN_WIDTH - GAP_WIDTH - 30)
				pipesArray[2].pipeMove(speed);




			// Resets pipes if when they move off screen

			if (pipesArray[0].getX() <= -30) // if out of bounds
			{
				swap(pipesArray[0], pipesArray[1]);
				swap(pipesArray[1], pipesArray[2]);
				pipesArray[2].resetPipes(250, 155);
			}

			// updates all the pipes positions
			for (int index = 0; index < 3; index++)
			{
				pipesArray[index].setPipePosition();
				pipesArray[index].drawPipes(window);
			}

			
			if (bird.collision(pipesArray[0]))
			{
				collision = true;
			}
		
			if (bird.getY() == 298) // 298 represents number when bird beak touchs ground
			{
				//std::cout << "Collison with ground" << std::endl;
				collision = true;
			}
			else
				//std::cout << "No Collision with ground" << std::endl;
				
			bird.birdSetPosition();
			bird.drawBird(window);
			count = count + 0.5; // for Flapping wings

		}
		// if play hasnt been clicked.. continue to display button
		else
			menu.startMenu(window);


		// land movement
		for (int index = 0; index < 2; index++)
		{
			landSprite[index].move(-speed, 0);
			if (landSprite[index].getPosition().x <= -336) // if image becomes fully out of scope
				landSprite[index].setPosition(336, 315); // resets the position to beginning

			window.draw(landSprite[index]);

		}
		

		window.display();
		


	}

	return 0;
}

