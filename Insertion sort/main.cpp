#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <vector>
#include <ctime>

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Insertion sort", sf::Style::Default);
	window.setFramerateLimit(144);

	int bars = 320;
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

		// Insertion sort
		int j;
		sf::RectangleShape temp;
		for (int i = 1; i < rects.size(); i++)
		{
			temp.setSize(sf::Vector2f(rects[i].getSize()));
			j = i - 1;

			while (temp.getSize().y <= rects[j].getSize().y && j > 0)
			{
				rects[j + 1].setSize(sf::Vector2f(rects[j].getSize()));
				j--;
			}
			rects[j + 1].setSize(sf::Vector2f(temp.getSize()));

			for (size_t k = 0; k < rects.size(); k++)
			{
				rects[k].setPosition(0.f + pos, window.getSize().y - rects[k].getSize().y);
				pos += rects[k].getSize().x;
			}
			pos = 0.f;

			sf::sleep(sf::milliseconds(10));
			window.clear();

			for (size_t k = 0; k < rects.size(); k++)
			{
				window.draw(rects[k]);
			}

			window.display();
		}
	}

	return 0;
}