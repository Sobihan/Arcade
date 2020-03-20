/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Pacman
*/

#include "Pacman.hpp"

Pacman::Pacman()
{
    this->gameOver = false;
    this->map = pac_map;
    this->player.x = 13;
    this->player.y = 15;
    this->map[this->player.y][this->player.x] = 'P';
    this->player.eatgum = false;
    this->player.duration = 0.0;
    this->score = 0;

    this->ghost.x = this->player.x;
    this->ghost.y = this->player.y - 2;
    this->map[this->ghost.y][this->ghost.x] = 'G';
    this->ghost.prev = ' ';
    this->ghost.step = 0;
    this->ghost.iseat = false;
    
    this->ghosts2.x = this->player.x;
    this->ghosts2.y = this->player.y - 3;
    this->map[this->ghosts2.y][this->ghosts2.x] = 'G';
    this->ghosts2.prev = ' ';
    this->ghosts2.step = 0;
    this->ghosts2.iseat = false;

    this->duration = 0.0;
    this->start = std::clock();
}

Pacman::~Pacman()
{
}

bool Pacman::isGameOver() const
{
    return (this->gameOver);
}

void Pacman::goUp()
{
    if (this->player.y - 1 >= 0 && this->map[this->player.y - 1][this->player.x] != '#') {
            map[this->player.y][this->player.x] = ' ';
            this->player.y = this->player.y - 1;
            if (map[this->player.y][this->player.x] == 'o') {
                this->player.eatgum = true;
                this->score = this->score + 5;
            } else if (map[this->player.y][this->player.x] == '.')
                this->score = this->score + 1;
            this->map[this->player.y][this->player.x] = 'P';
    }
}


void Pacman::goDown()
{
    if (this->player.y + 1 < this->map.size() && this->map[this->player.y + 1][this->player.x] != '#') {
            this->map[this->player.y][this->player.x] = ' ';
            this->player.y = this->player.y + 1;
            if (map[this->player.y][this->player.x] == 'o') {
                this->player.eatgum = true;
                this->score = this->score + 5;
            } else if (map[this->player.y][this->player.x] == '.')
                this->score = this->score + 1;
            this->map[this->player.y][this->player.x] = 'P';
    }
}

void Pacman::goRight()
{
    if (this->player.x + 1 < this->map[this->player.y].size() && this->map[this->player.y][this->player.x + 1] != '#') {
            if (this->map[this->player.y][this->player.x + 1] == '>') {
                this->map[this->player.y][this->player.x] = ' ';    
                this->player.x = 4;
                this->map[this->player.y][this->player.x] = 'P';
            } else {
                this->map[this->player.y][this->player.x] = ' ';
                this->player.x = this->player.x + 1;
                if (map[this->player.y][this->player.x] == 'o') {
                    this->score = this->score + 5;
                    this->player.eatgum = true;
                }else if (map[this->player.y][this->player.x] == '.')
                    this->score = this->score + 1;
                this->map[this->player.y][this->player.x] = 'P';
            }
        }
}

void Pacman::goLeft()
{
    if (this->player.x - 1 >= 0 && this->map[this->player.y][this->player.x - 1] != '#') {
            if (this->map[this->player.y][this->player.x - 1] == '<') {
                this->map[this->player.y][this->player.x] = ' ';
                this->player.x = this->map[this->player.x].size() - 5;
                this->map[this->player.y][this->player.x] = 'P';
            } else {
                this->map[this->player.y][this->player.x] = ' ';
                this->player.x = this->player.x - 1;
                if (map[this->player.y][this->player.x] == 'o') {
                    this->score = this->score + 5;
                    this->player.eatgum = true;
                }else if (map[this->player.y][this->player.x] == '.')
                    this->score = this->score + 1;
                this->map[this->player.y][this->player.x] = 'P';
            }
    }
}

void Pacman::change_dir(Direction dir)
{
    switch (dir)
    {
        case UP:
            goUp();
            break;
        case DOWN:
            goDown();
            break;
        case RIGHT:
            goRight();
            break;
        case LEFT:
            goLeft();
            break;
        default:
            break;
    }

    if (this->player.x == this->ghosts2.x && this->player.y == this->ghosts2.y)
        this->ghosts2.iseat = true;
    if (this->player.x == this->ghost.x && this->player.y == this->ghost.y)
        this->ghost.iseat = true;
    if (this->score == 208)
        this->gameOver = true;
}

std::vector <std::string> Pacman::getMap() const
{
    return (this->map);
}

ghosts Pacman::goUpG(ghosts g)
{
    if (g.y - 1 >= 0 && this->map[g.y - 1][g.x] != '#') {
            this->map[g.y][g.x] = g.prev;
            g.y = g.y - 1;
            g.prev = this->map[g.y][g.x];
            this->map[g.y][g.x] = 'G';
        } else
            g.istouch = true;
    return (g);
}

ghosts Pacman::goDownG(ghosts g)
{
    if (g.y + 1 < this->map.size() && this->map[g.y + 1][g.x] != '#') {
            this->map[g.y][g.x] = g.prev;
            g.y = g.y + 1;
            g.prev = this->map[g.y][g.x];
            this->map[g.y][g.x] = 'G';
        } else
            g.istouch = true;
    return (g);
}

ghosts Pacman::goRightG(ghosts g)
{
    if (g.x + 1 < this->map[g.y].size() && this->map[g.y][g.x + 1] != '#') {
            this->map[g.y][g.x] = g.prev;
            if (this->map[g.y][g.x + 1] == '>') {
                g.x = 4;
                g.prev = this->map[g.y][g.x];
                this->map[g.y][g.x] = 'G';
            } else {
                g.x = g.x + 1;
                g.prev = this->map[g.y][g.x];
                this->map[g.y][g.x] = 'G';
            }
        } else
            g.istouch = true;
    return(g);
}

ghosts Pacman::goLeftG(ghosts g)
{
    if (g.x - 1 >= 0 && this->map[g.y][g.x - 1] != '#') {
            this->map[g.y][g.x] = g.prev;
            if (this->map[g.y][g.x] == '<') {
                g.x = this->map[g.x].size() - 5;
                g.prev = this->map[g.y][g.x];
                this->map[g.y][g.x] = 'G';
            } else {
                g.x = g.x - 1;
                g.prev = this->map[g.y][g.x];
                this->map[g.y][g.x] = 'G';
            }
        } else
            g.istouch = true;

    return (g);
}

ghosts Pacman::movement(ghosts g)
{
    std::vector<Direction> mov;

    if (this->map[g.y - 1][g.x] != '#')
        mov.push_back(UP);
    if (this->map[g.y + 1][g.x] != '#' || g.y != 10 && g.x != 13 && g.step <= 2)
        mov.push_back(DOWN);
    if (this->map[g.y][g.x + 1] != '#')
        mov.push_back(RIGHT);
    if (this->map[g.y][g.x - 1] != '#')
        mov.push_back(LEFT);
    this->random = rand() % mov.size();
    g.dir = mov[this->random];
    g.step = g.step + 1;
    return (g);
}

ghosts Pacman::Ghost_dir(ghosts g)
{
    //if (g.step % 4 != 0) {
      //  g.step += 1;
        //return (g);
    //}
    switch (g.dir)
    {
        case UP:
            g = goUpG(g);
            break;
        case DOWN:
            g = goDownG(g);
            break;
        case RIGHT:
            //mvprintw(50,50, "COUCOU");
            g = goRightG(g);
            break;
        case LEFT:
            g = goLeftG(g);
            break;
        default:
            break;
    }
    if (g.istouch == true) {
        g.istouch = false;
        g = movement(g);
    }
    return (g);
}

ghosts Pacman::ghost_move(ghosts g)
{
    if (g.step <= 2) {
        g.dir = UP;
        g.step = g.step + 1;
    }
    if (g.prev == 'G')
        g.prev = ' ';
    g = Ghost_dir(g);
    return (g);
}

void Pacman::choose_move(double duration)
{
    if (duration >= 0.05 && !this->ghosts2.iseat)
        this->ghosts2 = ghost_move(this->ghosts2);
    if (duration >= 0.1 && !this->ghost.iseat)
        this->ghost = ghost_move(this->ghost);
}

double Pacman::get_duration()
{
    this->duration = (std::clock() - this->start) / (double) CLOCKS_PER_SEC;
    return (this->duration);
}
/*FRONT A SUPPR*/

int Pacman::getScore() const
{
    return (this->score);
}