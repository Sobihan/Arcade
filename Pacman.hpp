/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include <vector>
#include <string>
#include <iostream>

enum Direction
{
    STOP,
    LEFT,
    RIGHT,
    UP,
    DOWN    
};

static std::vector<std::string> pac_map = {
	"   #####################   ",
	"   #.........#.........#   ",
	"   #.###.###.#.###.###.#   ",
	"   #o# #.# #.#.# #.# #o#   ",
	"   #.###.###.#.###.###.#   ",
	"   #...................#   ",
	"   #.###.#.#####.#.###.#   ",
	"   #.###.#.#####.#.###.#   ",
	"   #.....#...#...#.....#   ",
	"   #####.### # ###.#####   ",
	"       #.#       #.#       ",
	"       #.# ## ## #.#       ",
	"   #####.# #   # #.#####   ",
	"   <    .  #   #  .    >   ",
	"   #####.# ##### #.#####   ",
	"       #.#       #.#       ",
	"       #.# ##### #.#       ",
	"   #####.# ##### #.#####   ",
	"   #.........#.........#   ",
	"   #.###.###.#.###.###.#   ",
	"   #o..#..... .....#..o#   ",
	"   ###.#.#.#####.#.#.###   ",
	"   ###.#.#.#####.#.#.###   ",
	"   #.....#...#...#.....#   ",
	"   #.#######.#.#######.#   ",
	"   #...................#   ",
	"   #####################   "
};
#include <ctime>

typedef struct player_s
{
	int x;
	int y;
	bool eatgum;
	double duration;
	std::clock_t start;
} players;

typedef struct ghost_s
{
	int x;
	int y;
	char prev;
	Direction dir;
	int step;
	bool istouch;
	bool iseat;
} ghosts;

class Pacman {
    public:
        Pacman();
        ~Pacman();
		bool isGameOver() const;
		void change_dir(Direction dir);
		void goUp();
		void goDown();
		void goRight();
		void goLeft();
		ghosts Ghost_dir(ghosts g);
		std::vector <std::string> getMap() const;
		ghosts goUpG(ghosts g);
		ghosts goDownG(ghosts g);
		ghosts goRightG(ghosts g);
		ghosts goLeftG(ghosts g);
		ghosts movement(ghosts g);
		ghosts ghost_move(ghosts g);
		int getScore() const;
		void choose_move(double duration);
		double get_duration();
    protected:
        std::vector <std::string> map;
		bool gameOver;
		players player;
		ghosts ghost;
		ghosts ghosts2;
		int random;
		double duration;
		std::clock_t start;
		int score;

    private:
};

#endif /* !PACMAN_HPP_ */
