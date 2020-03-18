#include <vector>
#include <string>
#include <iostream>

bool isGameOver = false;
int playerX = 13;
int playerY = 15;
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
        }
        break;
    case DOWN:
        if (playerY + 1 < map.size() && map[playerY + 1][playerX] != '#') {
            map[playerY][playerX] = ' ';
            playerY = playerY + 1;
        }
        break;
    case RIGHT:
        if (playerX + 1 < map[playerY].size() && map[playerY][playerX + 1] != '#') {
            map[playerY][playerX] = ' ';
            playerX = playerX + 1;
        }
        break;
    case LEFT:
        if (playerX - 1 >= 0 && map[playerY][playerX - 1] != '#') {
            map[playerY][playerX] = ' ';
            playerX = playerX - 1;
        }
        break;
    default:
        break;
    }
}
#include <unistd.h>
void input()
{
    
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    Direction dir;
    //mvprintw(0, 0, "Coucou");
    while (! isGameOver) {
        map[playerY][playerX] = 'P';
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
            }
            usleep(80000);
        //for (double x = 0; x < 29998999; x += 1);
    }
    endwin();
}
int main()
{
    
   input();
}