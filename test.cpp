/*
** EPITECH PROJECT, 2020
** test
** File description:
** test
*/

#include <vector>
#include <string>
#include <iostream>

int width = 20;
int height = 20;
int fruitX  = rand() % width;
int fruitY = rand() % height;
int snakeX = width / 2;
int snakeY = height / 2;
int tailX[100], tailY[100];
int nTail;
int firstmove = 0;

bool isGameOver = false;

enum Direction
{
    STOP,
    LEFT,
    RIGHT,
    UP,
    DOWN    
};

class snake
{
private:
    /* data */
public:
    snake(/* args */);
    ~snake();
};

snake::snake(/* args */)
{
}

snake::~snake()
{
}

std::vector <std::string> get_first_last_line(std::vector <std::string> map)
{
    std::string line;

    for (int i = 0; i < width + 1; i = i + 1)
        line += '#';
    line += '\n';
    map.push_back(line);
    line.clear();
    return (map);
}

void hitbox()
{
    if (snakeY == fruitY && snakeX == fruitX) {
        fruitX  = rand() % width;
        fruitY = rand() % height;
        nTail += 1;
    }
    if (snakeY >= height || snakeY <= 0)
        isGameOver = true;
    if (snakeX >= width || snakeX <= 0)
        isGameOver = true;
    for (int i = 0; i < nTail; i = i + 1)
        if (tailX[i] == snakeX && tailY[i] == snakeY) {
            isGameOver = true;
            break;
        }

}
#include <curses.h>
std::string get_line (int j, int i, std::string line)
{
    if (j == 0 || j == width -1)
        line += '#';
    if (i == fruitY && j == fruitX)
        line += 'F';
    else if (i == snakeY && j == snakeX)
        line += 'O';
    else {
        bool isPut = false;
        for (int k = 0; k < nTail; k = k + 1) {
            if (tailX[k] == j && tailY[k] == i) {
                line += 'o';
                isPut = true;
            }
        }
        if (! isPut)
            line += ' ';
    }
    hitbox();
    return (line);
}

std::vector <std::string> generate_map()
{
    std::vector <std::string> map;
    std::string line;

    map = get_first_last_line(map);
    for (int i = 0; i < height; i = i + 1) {
        for (int j = 0; j < height; j = j + 1)
            line = get_line(j, i, line);
        line += '\n';
        map.push_back(line);
        line.clear();
    }
    map = get_first_last_line(map);
    return (map);
}

void change_dir(Direction dir)
{
    if (dir != STOP && firstmove < 4) {
        firstmove += 1;
        nTail += 1;
    }
    int prevX = tailX[0];
    int prevY = tailY[0];

    int prev2X, prev2Y;
    tailX[0] = snakeX;
    tailY[0] = snakeY;
    for (int i = 1; i < nTail; i = i + 1) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;

    }
    switch (dir)
    {
    case LEFT:
        snakeX = snakeX - 1;
        break;
    case UP:
        snakeY = snakeY - 1;
        break;
    case RIGHT:
        snakeX = snakeX + 1;
        break;
    case DOWN:
        snakeY = snakeY + 1;
    default:
        break;
    }
}


void display(std::vector <std::string> map)
{
    int size = map.size();

    //system("clear");
    for (int i = 0; i != size; i = i + 1)
        for (int j = 0; j != map[i].size(); j = j + 1)
            std::cout << map[i][j];
    
}



void toggle_bool(bool &value)
{
    if (value)
        value = false;
    else
        value = true;
}


bool key_was_pressed(void)
{
    int key = getch();

    if (key != ERR) {
        ungetch(key);
        return (true);
    }
    return (false);
}

void input()
{
    Direction dir;
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    std::vector <std::string> map;

    while (! isGameOver) {
        if (key_was_pressed()) {
            int key = getch();
            
            if (key == KEY_DOWN && dir != UP)
                dir = DOWN;
            else if (key == KEY_UP && dir != DOWN)
                dir = UP;
            else if (key == KEY_LEFT && dir != RIGHT)
                dir = LEFT;
            else if (key == KEY_RIGHT && dir != LEFT)
                dir = RIGHT;
        }
        erase();
        change_dir(dir);
        map = generate_map();
        int size = map.size();
        for (int i = 0; i != size; i = i + 1)
            for (int j = 0; j != map[i].size(); j = j + 1) {
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
        for (double x = 0; x < 29998999; x += 1);
    }
    endwin();
}

int main()
{
    Direction dir;
    std::vector <std::string> map;

    input();
   // while (! isGameOver) {
     //   map = generate_map();
       // display(map);
    //}
    //dir = LEFT;
    //change_dir(dir);
    //map = generate_map();
}