/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** main
*/

#include "Pacman.hpp"


Pacman display_term(Pacman nib);
Pacman display_graph(Pacman nib);

int main()
{  bool is_graph = false;
    Pacman nib;

    while (1) {
        if (is_graph == false) {
            nib = display_graph(nib);
            if (is_graph == true)
            continue;
        } else {
            nib = display_graph(nib);
            if (is_graph == false)
            continue;
        }
        for (double x = 0; x < 29998999; x += 1);
    }
}