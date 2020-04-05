/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler_Term
*/

#include "Nibbler.hpp"
#include <curses.h>
#include <cstring>

bool key_was_pressed(void)
{
    int key = getch();

    if (key != ERR) {
        ungetch(key);
        return (true);
    }
    return (false);
}

void prepare_term()
{
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    
}

bool is_term = true;
int pe = 0;

Direction get_key(Direction move)
{
    if (key_was_pressed()) {
        int key = getch();
        
        if (key == KEY_DOWN)
            move = DOWN;
        else if (key == KEY_UP)
            move = UP;
        else if (key == KEY_LEFT)
            move = LEFT;
        else if (key == KEY_RIGHT)
            move = RIGHT;
        if (key == KEY_BACKSPACE) {
            is_term = FALSE;
            pe = 1;
            

        }
    }
    return (move);
}

void parse_data(std::vector <std::string> map)
{
    int size = map.size();
    int lenght = 0;

    for (int i = 0; i != size; i = i + 1) {
        lenght = map[i].size();
        for (int j = 0; j != lenght; j = j + 1) {
            char tmp = map[i][j];
            if (tmp == '#')
                mvprintw(i, j, "#");
            else if (tmp == ' ')
                mvprintw(i, j, " ");
            else if (tmp == 'F')
                mvprintw(i, j, "F");
            else if (tmp == 'O')
                mvprintw(i, j, "O");
            else if (tmp == 'o')
                mvprintw(i, j, "o");
        }
    }
}

char *get_Cstr(std::string name, std::string src)
{
    src = name + src;
    char *cstrs = strdup(src.c_str());
    return (cstrs);
}

Nibbler display_term(Nibbler nib)
{
    Direction move;
  
    std::vector <std::string> map;
    int key = getch();
    is_term = true;
    prepare_term();

    while (is_term == true) {
        if (! nib.isGameOver()) {
            move = get_key(move);
            nib.change_dir(move);
            map = nib.getMap();
            parse_data(map);

           
        } if (nib.isGameOver()) {
            erase();
            mvprintw(0,0, "Game Over");

        }
        if (pe == 1) {
            pe = -1;
            is_term = false;
        }
        mvprintw(0, 200, get_Cstr("Score:", std::to_string(nib.getscore())));
        refresh();
        for (double x = 0; x < 29998999; x += 1);
    }
    endwin();
    return (nib);
}

