#ifndef BATTLESHIP_FIELD_H
#define BATTLESHIP_FIELD_H

#include <iostream>
#include <array>
#include<iomanip>
#include <vector>

#include "Ship.h"

enum class square
{
    free, filled, reserved
};

int square_to_int(square s);

char square_to_char(square s);

class Field
{
private:
    std::array<std::array<square, 10>, 10> field;

    void add_area(Ship &cur, int x, int y);

    unsigned int count_single = 0;
    unsigned int count_double = 0;
    unsigned int count_triple = 0;
    unsigned int count_quadruple = 0;

public:


    Field()
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                field[i][j] = square::free;
                field[i][j] = square::free;
            }
        }

        count_single = 0;
        count_double = 0;
        count_triple = 0;
        count_quadruple = 0;
    }

    void set_filled(const std::pair<int, int> &cur);

    void update_count(int count);

    void set_surrounding(const std::vector<std::pair<int, int>> &squares);

    void set_squares(const std::vector<std::pair<int, int>> &squares);

    void set_reserved(const std::pair<int, int> &cur);

    bool is_in_field(const std::pair<int, int> &cur);

    bool is_filled(const std::pair<int, int> &cur);

    bool is_free(const std::pair<int, int> &cur);

    bool is_reserved(const std::pair<int, int> &cur);

    void show_field(std::ostream &out);

    void print_field(std::ostream &out);

    void rotate_field();

    void set_ship(Ship &cur);

    bool is_possible(Ship &cur);

    void set_area(Ship &cur);

    bool is_almostFull();

    bool is_full();

    bool is_full_of(int cur);

    bool check_quadruple();

    bool check_single();

    bool check_triple();

    bool check_double();
};


#endif //BATTLESHIP_FIELD_H
