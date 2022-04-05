#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Caesar cipher", sf::Style::Default);

    std::string word;
    std::cout << "Enter a word: ";
    std::cin >> word;

    sf::Font font;
    font.loadFromFile("Font/font.ttf");

    sf::Text text;
    std::vector<sf::Text> texts;
    text.setFont(font);

    for (size_t i = 0; i < word.size(); i++)
    {
        text.setString(word[i]);
        texts.push_back(text);
    }

    sf::RectangleShape shape(sf::Vector2f(50.f, 50.f));
    std::vector<sf::RectangleShape> shapes;
    shape.setFillColor(sf::Color(50, 50, 50));
    shape.setOutlineColor(sf::Color(200, 200, 200));
    shape.setOutlineThickness(5.f);

    int position = 0.f;

    for (size_t i = 0; i < word.size(); i++)
    {
        shape.setPosition(sf::Vector2f(100.f + position, 100.f));
        texts[i].setPosition(shape.getPosition().x + 15.f, shape.getPosition().y + 7.f);

        shapes.push_back(shape);
        position += shape.getSize().x + shape.getOutlineThickness();
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (size_t i = 0; i < shapes.size(); i++)
        {
            window.draw(shapes[i]);
        }

        for (size_t i = 0; i < texts.size(); i++)
        {
            window.draw(texts[i]);
        }

        window.display();
    }

    return 0;
}