/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** main
*/

#include "Nibbler.hpp"

Nibbler display_term(Nibbler nib);
Nibbler display_graph(Nibbler nib);

int main()
{
    bool is_graph = false;
    Nibbler nib;

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