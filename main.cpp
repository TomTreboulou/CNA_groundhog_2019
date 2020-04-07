/*
** EPITECH PROJECT, 2020
** CNA_groundhog_2019
** File description:
** main
*/

#include "Data.hpp"

void usage()
{
    std::cout << "SYNOPSIS" << std::endl;
    std::cout << "\t./groundhog period" << std:: endl << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tperiod\t the number of days defining a period" << std::endl;
    exit(0); 
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cout << "Bad input" << std::endl;
        exit(84);
    }
    if (av[1] == "-h") {
        usage();
    }
    Data data(av[1]);
    data.loop();
    return (0);
}