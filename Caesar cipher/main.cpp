#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Caesar cipher", sf::Style::Default);

    // Enter the values
    std::string word;
    std::cout << "Enter a word: ";
    std::cin >> word;

    int key;
    std::cout << "Enter a key: ";
    std::cin >> key;

    // Initialize text
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

    // Initialize rectangles
    sf::RectangleShape shape(sf::Vector2f(50.f, 50.f));
    std::vector<sf::RectangleShape> shapes;
    shape.setFillColor(sf::Color(50, 50, 50));
    shape.setOutlineColor(sf::Color(200, 200, 200));
    shape.setOutlineThickness(5.f);

    int position = 0.f;

    // Set text and rectangles
    for (size_t i = 0; i < word.size(); i++)
    {
        shape.setPosition(sf::Vector2f(100.f + position, 100.f));
        texts[i].setPosition(shape.getPosition().x + 15.f, shape.getPosition().y + 7.f);

        shapes.push_back(shape);
        position += shape.getSize().x + shape.getOutlineThickness();
    }

    // "Key" text
    std::stringstream ss;
    ss << "Key: " << key;
    sf::Text keyText;
    keyText.setFont(font);
    keyText.setCharacterSize(32);
    keyText.setPosition(sf::Vector2f(100.f, 200.f));
    keyText.setString(ss.str());

    // Caesar cipher algorithm
    std::string cryptogram="";
    int code;
    for (size_t i = 0; i < word.size(); i++)
    {
        code = word[i] + key;
        if (code > 'Z')
            code -= 26;
        cryptogram += char(code);
    }

    sf::Text textCryptogram;
    std::vector<sf::Text> textsCryptogram;
    textCryptogram.setFont(font);

    for (size_t i = 0; i < cryptogram.size(); i++)
    {
        textCryptogram.setString(cryptogram[i]);
        textsCryptogram.push_back(textCryptogram);
    }

    // Initialize cryptogram rectangles
    sf::RectangleShape rect(sf::Vector2f(50.f, 50.f));
    std::vector<sf::RectangleShape> rects;
    rect.setFillColor(sf::Color(50, 50, 50));
    rect.setOutlineColor(sf::Color(200, 200, 200));
    rect.setOutlineThickness(5.f);

    position = 0.f;

    // Set cryptogram text and cryptogram rectangles
    for (size_t i = 0; i < cryptogram.size(); i++)
    {
        rect.setPosition(sf::Vector2f(100.f + position, 300.f));
        textsCryptogram[i].setPosition(rect.getPosition().x + 15.f, rect.getPosition().y + 7.f);

        rects.push_back(rect);
        position += rect.getSize().x + rect.getOutlineThickness();
    }

    // Graphic loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Draw all objects
        for (size_t i = 0; i < shapes.size(); i++)
        {
            window.draw(shapes[i]);
        }

        for (size_t i = 0; i < texts.size(); i++)
        {
            window.draw(texts[i]);
        }

        window.draw(keyText);

        for (size_t i = 0; i < rects.size(); i++)
        {
            window.draw(rects[i]);
        }

        for (size_t i = 0; i < textsCryptogram.size(); i++)
        {
            window.draw(textsCryptogram[i]);
        }

        // Display frame
        window.display();
    }

    return 0;
}