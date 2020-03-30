/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

Nibbler::Nibbler()
{
    this->limit.height = 20;
    this->limit.width = 20;
    srand(time(NULL));
    this->fruit.x = rand() % this->limit.width;
    this->fruit.y = rand() % this->limit.height;
    this->snake.x = this->limit.width / 2;
    this->snake.y = this->limit.height / 2;
    this->snake.ntail = 0;
    this->firstmove = 0;
    this->score = 0;
    this->GameOver = false;
}

Nibbler::~Nibbler()
{
}

screens Nibbler::getlimit() const
{
    return (this->limit);
}

fruits Nibbler::getfruit() const
{
    return (this->fruit);
}

snakes Nibbler::getsnake() const
{
    return (this->snake);
}

std::vector <std::string> get_first_last_line(std::vector <std::string> map, int width)
{
    std::string line;

    for (int i = 0; i < width + 1; i = i + 1)
        line += '#';
    line += '\n';
    map.push_back(line);
    line.clear();
    return (map);
}

void Nibbler:: hitbox()
{
    if (this->snake.y == this->fruit.y && this->snake.x == this->fruit.x) {
        this->fruit.x = this->snake.prevtailX;
        this->fruit.y = this->snake.prevtailY;
        this->snake.ntail += 1;
        this->score += 1;
    }
    if (this->snake.y >= this->limit.height || this->snake.y <= 0)
        this->GameOver = true;
    if (this->snake.x >= this->limit.width || this->snake.x <= 0)
        this->GameOver = true;
    for (int i = 0; i < this->snake.ntail; i = i + 1)
        if (this->snake.tailX[i] == this->snake.x && this->snake.tailY[i] == this->snake.y) {
            this->GameOver = true;
            break;
        }

}

int Nibbler::getscore() const
{
    return (this->score);
}

std::string Nibbler::get_line (int j, int i, std::string line)
{
    if (j == 0 || j == this->limit.width -1)
        line += '#';
    if (i == this->fruit.y && j == this->fruit.x)
        line += 'F';
    else if (i == this->snake.y && j == this->snake.x)
        line += 'O';
    else {
        bool isPut = false;
        for (int k = 0; k < this->snake.ntail; k = k + 1) {
            if (this->snake.tailX[k] == j && this->snake.tailY[k] == i) {
                line += 'o';
                isPut = true;
                this->snake.prevtailX = j;
                this->snake.prevtailY = i;
            }
        }
        if (! isPut)
            line += ' ';
    }
    hitbox();
    return (line);
}
// i = y j = x
void Nibbler::update()
{
    std::vector <std::string> map;
    std::string line;

    map = get_first_last_line(map, this->limit.width);
    for (int i = 0; i < this->limit.height; i = i + 1) {
        for (int j = 0; j < this->limit.height; j = j + 1)
            line = get_line(j, i, line);
        line += '\n';
        map.push_back(line);
        line.clear();
    }
    map = get_first_last_line(map, this->limit.width);
    this->map = map;
}

std::vector <std::string> Nibbler::getmap() const
{
    return (this->map);
}

void Nibbler::tailmove()
{
    int prevX = this->snake.tailX[0];
    int prevY = this->snake.tailY[0];
    int prev2X = 0;
    int prev2Y = 0;

    this->snake.tailX[0] = this->snake.x;
    this->snake.tailY[0] = this->snake.y;
    for (int i = 1; i < this->snake.ntail; i = i + 1) {
        prev2X = this->snake.tailX[i];
        prev2Y = this->snake.tailY[i];
        this->snake.tailX[i] = prevX;
        this->snake.tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;

    }
}

void Nibbler::change_dir(Direction move)
{
    setdir(move);
    if (this->dir != STOP && this->firstmove < 4) {
        this->firstmove += 1;
        this->snake.ntail += 1;
    }
    tailmove();
    switch (dir)
    {
    case LEFT:
        this->snake.x = this->snake.x - 1;
        break;
    case UP:
        this->snake.y = this->snake.y - 1;
        break;
    case RIGHT:
        this->snake.x = this->snake.x + 1;
        break;
    case DOWN:
        this->snake.y = this->snake.y + 1;
    default:
        break;
    }
    update();
}

void Nibbler::setdir(Direction move)
{
    if (move == UP && this->dir == DOWN)
        return;
    else if (move == DOWN && this->dir == UP)
        return;
    else if (move == LEFT && this->dir == RIGHT)
        return;
    else if (move == RIGHT && this->dir == LEFT)
        return;
    this->dir = move;
}

bool Nibbler::isGameOver() const
{
    return (this->GameOver);
}

/* FRONT A SUPPR*/
// #include <curses.h>



// bool key_was_pressed(void)
// {
//     int key = getch();

//     if (key != ERR) {
//         ungetch(key);
//         return (true);
//     }
//     return (false);
// }

// void input(Nibbler nib)
// {
//     Direction move;
//     initscr();
//     cbreak();
//     noecho();
//     nodelay(stdscr, TRUE);
//     curs_set(FALSE);
//     keypad(stdscr, TRUE);
    
//     std::vector <std::string> map;
    
//     while (! nib.isGameOver()) {
//          if (key_was_pressed()) {
//             int key = getch();
            
//             if (key == KEY_DOWN)
//                 move = DOWN;
//             else if (key == KEY_UP)
//                 move = UP;
//             else if (key == KEY_LEFT)
//                 move = LEFT;
//             else if (key == KEY_RIGHT)
//                 move = RIGHT;
//         }
//         erase();
//         nib.setdir(move);
//         nib.change_dir();
//         nib.update();
//         map = nib.getmap();
//         int size = map.size();
//         for (int i = 0; i != size; i = i + 1)
//             for (int j = 0; j != map[i].size(); j = j + 1) {
//                 char tmp = map[i][j];
//                 if (tmp == '#')
//                     mvprintw(i, j, "#");
//                 else if (tmp == ' ')
//                     mvprintw(i, j, " ");
//                 else if (tmp == 'F')
//                     mvprintw(i, j, "F");
//                 else if (tmp == 'O')
//                     mvprintw(i, j, "O");
//                 else if (tmp == 'o')
//                     mvprintw(i, j, "o");
//             }
//         for (double x = 0; x < 29998999; x += 1);
//     }
//     endwin();
// }

/* FRONT A SUPPR*/
// int main()
// {
//     Nibbler nib;
//     input(nib);
// }