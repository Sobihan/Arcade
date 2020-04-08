/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** main
*/

#include "Pacman.hpp"

#include <unistd.h>
#include <cstring>
#include <curses.h>


Pacman input(Pacman pac);
Pacman display_graph(Pacman pac);
int mainc(void);

// int main(void)
// {
//     mainc();
//     return (0);
// }



int main()
{
    bool is_graph = false;
    Pacman pac;

    
    while (1) {


        if (is_graph == false) {
            is_graph = true;

            mainc();
            
        } else {
            is_graph = false;

            pac = display_graph(pac);
        }
        for (double x = 0; x < 29998999; x += 1);
    }
}
