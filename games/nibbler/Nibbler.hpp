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
    int pe;
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
        std::vector <std::string> getMap() const;
        void change_dir(Direction move);
        void setdir(Direction move);
        bool isGameOver() const;
        void tailmove();
        std::string get_Game() const;
        int getscore() const;
    protected:
        bool GameOver;

    private:
        screens limit;
        fruits fruit;
        snakes snake;
        int firstmove;
        Direction dir;
        std::vector <std::string> map;
        int score;
};

#endif /* !NIBBLER_HPP_ */
