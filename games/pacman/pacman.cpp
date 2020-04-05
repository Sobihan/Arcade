#include <vector>
#include <string>
#include <iostream>

bool isGameOver = false;
int playerX = 13;
int playerY = 15;
int Ghost1X = playerX;
int Ghost1Y = playerY - 2;

enum Direction
{
    STOP,
    LEFT,
    RIGHT,
    UP,
    DOWN    
};


static std::vector<std::string> map = {
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

#include <curses.h>

#include <unistd.h>

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

void change_dir(Direction dir)
{
    switch (dir)
    {
    case UP:
        if (playerY - 1 >= 0 && map[playerY - 1][playerX] != '#') {
            map[playerY][playerX] = ' ';
            playerY = playerY - 1;
            map[playerY][playerX] = 'P';
        }
        break;
    case DOWN:
        if (playerY + 1 < map.size() && map[playerY + 1][playerX] != '#') {
            map[playerY][playerX] = ' ';
            playerY = playerY + 1;
            map[playerY][playerX] = 'P';
        }
        break;
    case RIGHT:
        if (playerX + 1 < map[playerY].size() && map[playerY][playerX + 1] != '#') {
            if (map[playerY][playerX + 1] == '>') {
                map[playerY][playerX] = ' ';    
                playerX = 4;
                map[playerY][playerX] = 'P';
            } else {
                map[playerY][playerX] = ' ';
                playerX = playerX + 1;
                map[playerY][playerX] = 'P';
            }
        }
        break;
    case LEFT:
        if (playerX - 1 >= 0 && map[playerY][playerX - 1] != '#') {
            if (map[playerY][playerX - 1] == '<') {
                map[playerY][playerX] = ' ';
                playerX = map[playerX].size() - 5;
                map[playerY][playerX] = 'P';
            } else {
                map[playerY][playerX] = ' ';
                playerX = playerX - 1;
                map[playerY][playerX] = 'P';
            }
        }
        break;
    default:
        break;
    }
}

#include <chrono>
#include <thread>

int step = 0;
bool istouch = false;
void movement();

char prev = ' ';

void changedir(Direction dir)
{
    if (step % 4 != 0) {
        step += 1;
        return;
    }
    switch (dir)
    {
    case UP:
        if (Ghost1Y - 1 >= 0 && map[Ghost1Y - 1][Ghost1X] != '#') {

            map[Ghost1Y][Ghost1X] = prev;
            Ghost1Y = Ghost1Y - 1;
            prev = map[Ghost1Y][Ghost1X];
            map[Ghost1Y][Ghost1X] = 'G';
        } else
            istouch = true;
        break;
    case DOWN:
        if (Ghost1Y + 1 < map.size() && map[Ghost1Y + 1][Ghost1X] != '#') {
            map[Ghost1Y][Ghost1X] = prev;
            Ghost1Y = Ghost1Y + 1;
            prev = map[Ghost1Y][Ghost1X];
            map[Ghost1Y][Ghost1X] = 'G';
        } else
            istouch = true;
        break;
    case RIGHT:
        if (Ghost1X + 1 < map[Ghost1Y].size() && map[Ghost1Y][Ghost1X + 1] != '#') {
            map[Ghost1Y][Ghost1X] = prev;
            if (map[Ghost1Y][Ghost1X + 1] == '>') {
                Ghost1X = 4;
                prev = map[Ghost1Y][Ghost1X];
                map[Ghost1Y][Ghost1X] = 'G';
            } else {
                Ghost1X = Ghost1X + 1;
                prev = map[Ghost1Y][Ghost1X];
                map[Ghost1Y][Ghost1X] = 'G';
            }
        } else
            istouch = true;
        break;
    case LEFT:
        if (Ghost1X - 1 >= 0 && map[Ghost1Y][Ghost1X - 1] != '#') {
            map[Ghost1Y][Ghost1X] = prev;
            Ghost1X = Ghost1X - 1;
            prev = map[Ghost1Y][Ghost1X];
            map[Ghost1Y][Ghost1X] = 'G';
        } else
            istouch = true;
        break;
    default:
        break;
    }
    if (istouch == true) {
        istouch = false;
        movement();
    }
}
Direction dir;
int r = 0;

void movement()
{
    std::vector<Direction> mov;

    if (map[Ghost1Y - 1][Ghost1X] != '#')
        mov.push_back(UP);
    if (map[Ghost1Y + 1][Ghost1X] != '#')
        mov.push_back(DOWN);
    if (map[Ghost1Y][Ghost1X + 1] != '#')
        mov.push_back(RIGHT);
    if (map[Ghost1Y][Ghost1X - 1] != '#')
        mov.push_back(LEFT);
    r = rand() % mov.size();
    dir = mov[r];
 
}

void ghost_move()
{
    if (step <= 2) {
        step = step + 1;
        dir = UP;
    //    map[Ghost1Y][Ghost1X] = ' ';
      //  Ghost1Y = Ghost1Y - 1;
        //map[Ghost1Y][Ghost1X] = 'G';
    //    changedir(dir);
        //return;
    }
    changedir(dir);
    if (Ghost1Y == playerY && Ghost1X == playerX)
        isGameOver = true;
  //  if (step == 3) {
    //     int move =  rand() % 2;
    //     if (move % 2 == 0) {
    //         dir = RIGHT;
    //         //map[Ghost1Y][Ghost1X] = ' ';
    //         //Ghost1X = Ghost1X + 1;
    //     } else {
    //         //map[Ghost1Y][Ghost1X] = ' ';
    //         //Ghost1X = Ghost1X - 1;
    //         dir = LEFT;
    //     }
    //     //map[Ghost1Y][Ghost1X] = 'G';
    //     changedir(dir);
    //     step += 1;
    //     return;       
    // }

   // changedir(dir);

    
}

#include <ctime>

void input()
{
    map[playerY][playerX] = 'P';
    map[Ghost1Y][Ghost1X] = 'G';
    
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    Direction dir;
    clock_t time_req = clock();
    //mvprintw(0, 0, "Coucou");
    while (! isGameOver) {
           if (playerX == Ghost1X && playerY == Ghost1Y) {
                printf("U lost \n");
                exit (84);
        }
        if (key_was_pressed()) {
            int key = getch();
            if (key == KEY_RIGHT)
                dir = RIGHT;
            else if (key == KEY_UP)
                dir = UP;
            else if (key == KEY_DOWN)
                dir = DOWN;
            else if (key == KEY_LEFT)
                dir = LEFT;
                
        

        }
        erase();
        change_dir(dir);
        int size = map.size();
        for (int i = 0; i != size; i = i + 1)
            for (int j = 0; j != map[i].size(); j = j + 1) {
                char tmp = map[i][j];
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
        //map[playerY][playerX] = 'P';
       // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        usleep(120500);
        if (clock() - time_req > 10.0)
            ghost_move();
        //for (double x = 0; x < 29998999; x += 1);
    }
    endwin();
}
// int main()
// {
    
//    input();
// }