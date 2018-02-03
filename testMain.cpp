#include<SFML/Graphics.hpp>

int main()
{
	static const int SCREEN_WIDTH = 288;
	static const int SCREEN_HEIGHT = 400;
	static const int GAP_HEIGHT = 90;
	static const int GAP_WIDTH = 96;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
}