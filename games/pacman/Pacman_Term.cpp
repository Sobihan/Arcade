/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman_Term
*/

#include "Pacman.hpp"

#include <unistd.h>
#include <cstring>
#include <curses.h>

bool is_term = 0;
int pe = 0;

bool keyy_was_pressed(void)
{
    int key = getch();

    if (key != ERR) {
        ungetch(key);
        return (true);
    }
    return (false);
}

void init_term()
{
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    keypad(stdscr, TRUE);
}

Direction get_key(Direction move)
{
    if (keyy_was_pressed()) {
        int key = getch();
        if (key == KEY_RIGHT)
            move = RIGHT;
        else if (key == KEY_UP)
            move = UP;
        else if (key == KEY_DOWN)
            move = DOWN;
        else if (key == KEY_LEFT)
            move = LEFT;
        if (key == KEY_BACKSPACE) {
            is_term = FALSE;
            pe = 1;   
        }
    }
    return (move);
}

void print_data(char tmp, int i, int j)
{
    if (tmp == '#')
        mvprintw(i, j, "#");
    else if (tmp == ' ')
        mvprintw(i, j, " ");
    else if (tmp == '.')
        mvprintw(i, j, ".");
    else if (tmp == 'P')
        mvprintw(i, j, "P");
    else if (tmp == 'M')
        mvprintw(i, j, "M");
    else if (tmp == 'o')
        mvprintw(i, j, "o");
    else if (tmp == '<')
        mvprintw(i, j, "<");
    else if (tmp == '>')
        mvprintw(i, j, ">");
    else if (tmp == 'G')
        mvprintw(i, j, "G");
}
void parse_data(std::vector <std::string> map)
{
    int size = map.size();
    int lenght = 0;
    char tmp = 0;

    for (int i = 0; i != size; i = i + 1) {
        lenght = map[i].size();
        for (int j = 0; j != lenght; j = j + 1) {
            tmp = map[i][j];
            print_data(tmp, i, j);
        }
    }
}

char *get_Cstr(std::string name, std::string src)
{
    src = name + src;
    char *cstrs = strdup(src.c_str());
    return (cstrs);
}

Pacman input(Pacman pac)
{
    Direction move;
    is_term = true;
    init_term();
    std::vector <std::string> map;

    while (is_term == true) {
            if (! pac.isGameOver()) {
            move = get_key(move);
            pac.change_dir(move);
            map = pac.getMap();
            parse_data(map);
         } if (pac.isGameOver()) {
            erase();
            mvprintw(0,0, "Game Over");
         }
        if (pe == 1) {
            pe = -1;
            is_term = false;
        }
        mvprintw(0, 200, get_Cstr("Score:", std::to_string(pac.getScore())));
        refresh();
    }
    endwin();
    return (pac);
}

int mainc(void)
{
    Pacman pac;
    input(pac);
    return (0);
}