/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman_Graph
*/

#include "Pacman.hpp"
#include <SFML/Graphics.hpp>


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
    return (move);
}
sf::RectangleShape new_Rect(int x, int y, sf::Color color)
{
    sf::RectangleShape rect;

    rect.setFillColor(color);
    rect.setSize(sf::Vector2f(20, 20));
    rect.setPosition(x, y);
    return (rect);
}

std::vector <sf::Color> putcolor()
{
    std::vector<sf::Color> colors;

    colors.push_back(sf::Color(192,192,192));
    colors.push_back(sf::Color(255, 255, 0));
    colors.push_back(sf::Color(176, 242, 182));
    colors.push_back(sf::Color(255 , 9, 33));
    colors.push_back(sf::Color(0, 255, 255));
    return (colors);
}

std::vector<sf::RectangleShape> generate_rect(std::vector <std::string> map, std::vector<sf::RectangleShape> &old, int index)
{
    int size = map.size();
    int lenght = 0;
    std::vector<sf::RectangleShape> rect;
    std::vector<sf::Color> colors = putcolor();

    old.clear();
   // for (int i = 0; old.size() != 2; i = i + 1) {
     //   delete &old[0];
    //}
    for (int y = 0; y != size; y = y + 1) {
        lenght = map[y].size();
        for (int x = 0; x != lenght; x = x + 1) {
            if (map[y][x] == '#')
                rect.push_back(new_Rect((x * 20) + 20, (y * 20) + 20, colors[0]));
            else if (map[y][x] == 'o')
                rect.push_back(new_Rect((x * 20) + 20, (y * 20) + 20, colors[3]));
            else if (map[y][x] == '.')
                rect.push_back(new_Rect((x * 20) + 20, (y * 20) + 20, colors[2]));
            else if (map[y][x] == 'P')
                rect.push_back(new_Rect((x * 20) + 20, (y * 20) + 20, colors[1]));
            else if (map[y][x] == 'G')
                rect.push_back(new_Rect((x * 20) + 20, (y * 20) + 20, colors[4]));
        }
    }
    return (rect);
}

#include <unistd.h>

Pacman display_graph(Pacman pac)
{
    sf::RenderWindow window(sf::VideoMode(1200, 1080), "Pacman");
    window.setPosition(sf::Vector2i(0, 0));
    Direction move;
    std::vector <std::string> map;
    sf::Event event;
    sf::Text text;
    std::vector<sf::RectangleShape> rectangles;
    sf::Font font;
    int index = 0;

    window.setFramerateLimit(60);
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                exit(0);
            }
        }
            if ( ! pac.isGameOver()) {
                move = get_direction(move);
                pac.change_dir(move);
                map = pac.getMap();
                rectangles = generate_rect(map, rectangles, index);
                index = index + 1;
                int size = rectangles.size();
                for (int i = 0; i != size; i = i + 1)
                    window.draw(rectangles[i]);
                text.setString("Score: " + std::to_string(pac.getScore()));
                pac.choose_move(pac.get_duration());
                window.display();
                window.clear();
                window.draw(text);
                for (double x = 0; x < 29998999; x += 1);
            }
        
    }
    return (pac);
}

// int main()
// {
//     while (1) {
//         Pacman pac;

//         display_graph(pac);
//     }

// }