#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <vector>
#include <ctime>

sf::RenderWindow window(sf::VideoMode(1280, 720), "Quick sort", sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close);

void show(std::vector<sf::RectangleShape> rects)
{
	float pos = 0.f;

	for (size_t k = 0; k < rects.size(); k++)
	{
		rects[k].setPosition(0.f + pos, window.getSize().y - rects[k].getSize().y);
		pos += rects[k].getSize().x;
	}

	window.clear();

	for (size_t k = 0; k < rects.size(); k++)
	{
		window.draw(rects[k]);
	}

	window.display();
}

void quickSort(std::vector<sf::RectangleShape>& rects, int p, int k)
{
	int i, j;
	sf::RectangleShape m;
	sf::RectangleShape pom;
	while (p < k)
	{
		i = p;
		j = k;
		m.setSize(sf::Vector2f(rects[(p + k) / 2].getSize()));

		while (i <= j)
		{
			while (rects[i].getSize().y < m.getSize().y)
				i++;
			while (rects[j].getSize().y > m.getSize().y)
				j--;

			if (i <= j)
			{
				pom.setSize(sf::Vector2f(rects[i].getSize()));
				rects[i].setSize(sf::Vector2f(rects[j].getSize()));
				rects[j].setSize(sf::Vector2f(pom.getSize()));
				i++;
				j--;

				show(rects);
			}
		}

		if (j - p < k - i)
		{
			quickSort(rects, p, j);
			p = i;
		}
		else
		{
			quickSort(rects, i, k);
			k = j;
		}
	}
}

int main()
{
	srand(time(NULL));
	window.setFramerateLimit(144);

	int bars = 640;
	// Initialize rectangles
	sf::RectangleShape rect;
	std::vector<sf::RectangleShape> rects;
	float pos = 0.f;

	for (size_t i = 0; i < bars; i++)
	{
		rect.setSize(sf::Vector2f(float(window.getSize().x / bars), rand() % window.getSize().y));
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

		// Quick sort
		quickSort(rects, 0, bars - 1);

		window.clear();

		for (size_t k = 0; k < rects.size(); k++)
		{
			window.draw(rects[k]);
		}

		window.display();
	}

	return 0;
}