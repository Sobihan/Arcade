/*
** EPITECH PROJECT, 2020
** parse_main_args
** File description:
** Parse the arguments given to the executable, and handle errors.
*/

#include <dlfcn.h>
#include <iostream>
#include "core.hpp"

int parse_main_args(int argc, char **argv, char **envp)
{
    if (argc != 2) {
        std::cerr << argv[0] << ": bad arguments: " << (argc - 1) << " arguments given but 1 is required (the path to the graphical library to use)." << std::endl;
        return (RETURN_FAILURE);
    }

    void *starter_lib = dlopen(argv[1], RTLD_NOW);
    if (starter_lib == nullptr) { // Il faudra aussi check dans ce if que la lib est "compatible" (contient des trucs nécessaires à l'utilisation de l'arcade)
        std::cerr << argv[0] << ": cannot open the graphical library at " << argv[1] << "." << std::endl;
        return (RETURN_FAILURE);
    }

    std::cout << "Hello world!" << std::endl;
    return (0);
}
