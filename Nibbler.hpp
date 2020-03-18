/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include <vector>
#include <string>
#include <iostream>

typedef struct screen_s
{
    int width;
    int height;
} screens;

typedef struct snake_s
{
    int x;
    int y;
    int ntail;
    int tailX[100];
    int tailY[100];
    int prevtailX;
    int prevtailY;
} snakes;

typedef struct fruit_s
{
    int x;
    int y;
}fruits;

enum Direction
{
    STOP,
    LEFT,
    RIGHT,
    UP,
    DOWN    
};

class Nibbler {
    public:
        Nibbler();
        ~Nibbler();
        void update();
        screens getlimit() const;
        fruits getfruit() const;
        snakes getsnake() const;
        std::string get_line (int j, int i, std::string line);
        void hitbox();
        std::vector <std::string> getmap() const;
        void change_dir();
        void setdir(Direction move);
        bool isGameOver() const;
        void tailmove();
    protected:
    private:
        screens limit;
        fruits fruit;
        snakes snake;
        int firstmove;
        bool GameOver;
        Direction dir;
        std::vector <std::string> map;
};

#endif /* !NIBBLER_HPP_ */
