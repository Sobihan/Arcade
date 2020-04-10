/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler_graph
*/

#include "Nibbler.hpp"

#include <SFML/Graphics.hpp>


sf::RectangleShape new_Rect(int x, int y, sf::Color color)
{
    sf::RectangleShape rect;

    rect.setFillColor(color);
    rect.setSize(sf::Vector2f(40, 40));
    rect.setPosition(x, y);
    return (rect);
}

std::vector <sf::Color> putcolor()
{
    std::vector<sf::Color> colors;

    colors.push_back(sf::Color(192,192,192));
    colors.push_back(sf::Color(0, 255, 0));
    colors.push_back(sf::Color(176, 242, 182));
    colors.push_back(sf::Color(255 , 9, 33));
    return (colors);
}

std::vector<sf::RectangleShape> generate_rect(std::vector <std::string> map)
{
    int size = map.size();
    int lenght = 0;
    std::vector<sf::RectangleShape> rect;
    std::vector<sf::Color> colors = putcolor();

    for (int y = 0; y != size; y = y + 1) {
        lenght = map[y].size();
        for (int x = 0; x != lenght; x = x + 1) {
            if (map[y][x] == '#')
                rect.push_back(new_Rect((x * 40) + 40, (y * 40) + 40, colors[0]));
            else if (map[y][x] == 'O')
                rect.push_back(new_Rect((x * 40) + 40, (y * 40) + 40, colors[1]));
            else if (map[y][x] == 'o')
                rect.push_back(new_Rect((x * 40) + 40, (y * 40) + 40, colors[2]));
            else if (map[y][x] == 'F')
                rect.push_back(new_Rect((x * 40) + 40, (y * 40) + 40, colors[3]));
        }
    }
    return (rect);
}


bool is_graph = true;
Direction get_direction(Direction move)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        move = UP;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        move = RIGHT;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        move = DOWN;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        move = LEFT;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
        is_graph = false;
    return (move);
}

Nibbler display_graph(Nibbler nib)
{
    is_graph = true;
    sf::RenderWindow window(sf::VideoMode(1200, 1080), "Nibbler");
    window.setPosition(sf::Vector2i(0, 0));
    Direction move;
    std::vector <std::string> map;
    sf::Event event;
    sf::Text text;
    std::vector<sf::RectangleShape> rectangles;
    sf::Font font;
    sf::Texture gameover;
    sf::Sprite gameoverr;

    text.setFont(font);
    text.setString("Game Over");
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setCharacterSize(24);

    gameover.loadFromFile("fin.jpg");
    gameoverr.setTexture(gameover);

    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "ERror";
        exit(84);
    }
   
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setCharacterSize(24);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                exit(0);
            }
        }
        if (! nib.isGameOver()) {
            move = get_direction(move);
            nib.change_dir(move);
            nib.update();

            map = nib.getMap();
            rectangles = generate_rect(map);
            int size = rectangles.size();
            for (int i = 0; i != size; i = i + 1)
                window.draw(rectangles[i]);
            text.setString("Score: " + std::to_string(nib.getscore()));
            window.display();
            window.clear();
            window.draw(text);

            //for (double x = 0; x < 29998999; x += 1);
        }
        else {
            window.clear();
            window.draw(gameoverr);
            window.display();
        }
        if (is_graph == false) {
                window.close();
                break;
        }
    }
    return (nib);
}
