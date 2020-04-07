/*
** EPITECH PROJECT, 2020
** CNA_groundhog_2019
** File description:
** Data
*/

#ifndef DATA_HPP_
#define DATA_HPP_

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <ctype.h>
#include <cmath>

class Data {
    public:
        Data(char *);
        ~Data();
        void loop();
        void print_data();
        bool isDigit(std::string);
        void c_teamperature_inc_average();
        void c_relative_evolution();
        void c_standard_deviation();
        void weirdest_value();
        float average(int size, int dec);


    protected:
    private:
    std::vector<float> _data;
    std::vector<float> _s_deviation;
    std::vector<std::pair<float, float>> _weirdest;
    int _period;
    bool _state;
    bool _result;
    bool _first;
    int _switch;
};

#endif /* !DATA_HPP_ */
