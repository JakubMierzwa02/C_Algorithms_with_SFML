#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Bubble sort", sf::Style::Default);
	window.setFramerateLimit(144);

	int bars = 128;
	// Initialize rectangles
	sf::RectangleShape rect;
	std::vector<sf::RectangleShape> rects;
	float pos = 0.f;
	
	for (size_t i = 0; i < bars; i++)
	{
		rect.setSize(sf::Vector2f(float(1280 / bars), rand() % window.getSize().y));
		rect.setPosition(0.f + pos, window.getSize().y - rect.getSize().y);

		rects.push_back(rect);
		pos += rect.getSize().x;
	}

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}

		// Bubble sort
		sf::RectangleShape pom;
		for (int i = 1; i < rects.size(); i++)
		{
			for (int j = 0; j < rects.size() - i; j++)
			{
				if (rects[j].getSize().y > rects[j + 1].getSize().y)
				{
					pom.setSize(rects[j].getSize());
					rects[j].setSize(rects[j + 1].getSize());
					rects[j + 1].setSize(pom.getSize());

					for (size_t k = 0; k < rects.size(); k++)
					{
						rects[k].setPosition(0.f + pos, window.getSize().y - rects[k].getSize().y);
						pos += rects[k].getSize().x;
					}
					pos = 0.f;

					//sf::sleep(sf::milliseconds(10));
					window.clear();
					
					for (size_t k = 0; k < rects.size(); k++)
					{
						window.draw(rects[k]);
					}

					window.display();
				}
			}
		}
	}

	return 0;
}