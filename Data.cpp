/*
** EPITECH PROJECT, 2020
** CNA_groundhog_2019
** File description:
** Data
*/

#include "Data.hpp"

bool Data::isDigit(std::string data)
{
    for (int i = 0; i < data.size(); i++) {
        if (data[i] == '.') {
            continue;
        }
        if (!isdigit(data[i])) {
            return (false);
        }
    }
    return (true);
}

void Data::print_data()
{
    std::vector<float>::iterator it;
    int days = 1;

    for (it = this->_data.begin(); it != this->_data.end(); it++) {
        std::cout << "Days number: " << days << " | ";
        std::cout << "Temperature is: " << *it << std::endl;
        days++;
    }
}

void Data::c_teamperature_inc_average()
{
    float result = 0;
    size_t nb = 0;

    if (this->_data.size() <= this->_period) {
        std::cout << "g=nan      ";
        return;
    }
    for (int idx = this->_data.size() - 1; nb < this->_period; nb++, idx--) {
        if (this->_data[idx] - this->_data[idx - 1] >= 0) {
            result += this->_data[idx] - this->_data[idx - 1];
        }
    }
    if (this->_period != 0) {
        result /= this->_period;
    } else {
        result = 0;
    }
    std::cout << "g=" << std::setprecision(2) << std::fixed << result << "      ";
}

void Data::c_relative_evolution()
{
    float result = 0;

    if (this->_data.size() <= this->_period) {
        std::cout << "r=nan%      ";
        return;
    }
    if (this->_data[this->_data.size() - this->_period - 1] * 100 != 0) {
        result = (this->_data[this->_data.size() - 1] - this->_data[this->_data.size() - this->_period - 1]) / this->_data[this->_data.size() - this->_period - 1] * 100;
    } else {
        result = 0;
    }
    if (result >= 0) {
        this->_result = true;
        if (this->_first == false) {
            this->_state = true;
            this->_first = true;
        }
    } else {
        this->_result = false;
        if (this->_first == false) {
            this->_state = false;
            this->_first = true;
        }
    }
    std::cout << "r=" << std::setprecision(0) << std::fixed << result << "%      ";
}

void Data::c_standard_deviation()
{
    float result = 0;
    float average = 0;
    size_t nb = 0;

    if (this->_data.size() < this->_period) {
        std::cout << "s=nan";
        this->_s_deviation.push_back(-1);
        return;
    }
    average = this->average(this->_period, 0);

    for (int idx = this->_data.size() - 1; nb < this->_period; nb++, idx--) { 
        result += (std::pow((std::fabs(this->_data[idx] - average)), 2));
    }
    if (this->_period != 0) {
        result /= this->_period;
    } else {
        result = 0;
    }
    result = std::sqrt(result);
    this->_s_deviation.push_back(result);
    std::cout << "s=" << std::setprecision(2) << std::fixed << result;
}

float Data::average(int size, int dec)
{
    size_t nb = 0;
    float result = 0;

    for (int idx = this->_data.size() - dec - 1; nb < size; nb++, idx--) {
        result += this->_data[idx];
    }
    if (size != 0) {
        return result / size;
    } else {
        return 0;
    }
}

struct less_than_score
{
    inline bool operator() (const std::pair<float, float> &score1, const std::pair<float, float> &score2)
    {
        return score1.second > score2.second;
    }
};

void Data::weirdest_value()
{
    int average = 0;
    int nb = 0;

    for (int i = 0; i < this->_s_deviation.size(); i++) {
        average = 0;
        nb = 0;
        if (this->_s_deviation[i] != -1) {
            for (int idx = i; nb < this->_period; idx--, nb++) {
                average += this->_data[idx];
            }
            if (this->_period != 0) {
                average /= this->_period;
            } else {
                return;
            }
            if (this->_data[i] > (average + this->_s_deviation[i] * 2)) {
                this->_weirdest.push_back({this->_data[i], (this->_data[i] - (average + this->_s_deviation[i] * 2))});
            } else if (this->_data[i] < (average - this->_s_deviation[i] * 2)) {
                this->_weirdest.push_back({this->_data[i], ((average - this->_s_deviation[i] * 2) - this->_data[i])});
            }
        }
    }
    std::sort(this->_weirdest.begin(), this->_weirdest.end(), less_than_score());
    if (this->_weirdest.size() > 5) {
        std::cout << "5 weirdest values are [";
    } else if (!this->_weirdest.empty()) {
        std::cout << this->_weirdest.size() << " weirdest values are [";
    } else {
        std::cout << "no weirdest values" << std::endl;
        return;
    }
    for (int idx = 0; idx < this->_weirdest.size() && idx < 5; idx++) {
        std::cout << this->_weirdest[idx].first;
        if (idx < 4 && idx < this->_weirdest.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

void Data::loop()
{
    std::string input;

    while (input.compare("STOP")) {
        std::getline(std::cin, input);
        if (input.compare("") == 0) {
            continue;
        }
        if (input.compare("DATA") == 0) {
            this->print_data();
            continue;
        }
        if (this->isDigit(input) == true) {
            this->_data.push_back(std::stof(input));
            this->c_teamperature_inc_average();
            this->c_relative_evolution();
            this->c_standard_deviation();
            if (this->_result != this->_state) {
                this->_state = this->_result;
                std::cout << "      a switch occurs" << std::endl;
                this->_switch++;
            } else {
                std::cout << std::endl;
            }
        }
    }
    if (this->_switch != 0) {
        std::cout << "Global tendency switched " << this->_switch << " times" << std::endl;
    } else {
        std::cout << "Global tendency don't switched" << std::endl;
    }
    this->weirdest_value();
}

Data::Data(char *av)
{
    std::string input(av);

    this->_first = false;
    this->_period = std::stoi(input);
    this->_switch = 0;
}

Data::~Data()
{
}
