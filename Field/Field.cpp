#include "Field.h"

int square_to_int(square s)
{
    switch (s)
    {
        case square::free:
            return 0;
        case square::filled:
            return 1;
        case square::reserved:
            return 2;
    }
}

char square_to_char(square s)
{
    switch (s)
    {
        case square::free:
            return 'o';
        case square::filled:
            return 'x';
        case square::reserved:
            return '-';
    }
}

void Field::rotate_field()
{
    std::array<std::array<square, 10>, 10> temp_field;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            temp_field[j][9 - i] = field[i][j];
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            field[i][j] = temp_field[i][j];
        }
    }
}

void Field::print_field(std::ostream &out)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int temp = square_to_int(field[j][i]);
            if (temp == 2)
                temp = 0;
            out << temp;
        }
        out << std::endl;
    }
}

void Field::show_field(std::ostream &out)
{
    out << "   A B C D E F G H I J" << std::endl;

    for (int i = 0; i < 10; i++)
    {
        out << std::setw(2) << i << " ";
        for (int j = 0; j < 10; j++)
        {
            out << square_to_char(field[i][j]) << " ";
        }
        out << std::endl;
    }
}



void Field::add_area(Ship &cur, int x, int y)
{
    std::pair<int, int> temp = std::make_pair(x, y);
    if (is_in_field(temp) && is_free(temp) && cur.is_newSurrounding(temp))
        cur.add_surrounding(temp);
}

void Field::set_area(Ship &cur)
{
    for (const auto &p : cur.get_ship())
    {
        int x = p.first;
        int y = p.second;

        for (int i = -1; i < 2; i++)
        {
            add_area(cur, x + i, y - 1);
            add_area(cur, x + i, y + 1);
        }

        add_area(cur, x - 1, y);
        add_area(cur, x + 1, y);
    }
}


void Field::set_filled(const std::pair<int, int> &cur)
{
    if (is_in_field(cur) && !is_filled(cur))
        field[cur.first][cur.second] = square::filled;
}

void Field::set_reserved(const std::pair<int, int> &cur)
{
    if (is_in_field(cur) && is_free(cur))
        field[cur.first][cur.second] = square::reserved;
}

bool Field::is_filled(const std::pair<int, int> &cur)
{
    return field[cur.first][cur.second] == square::filled;
}

bool Field::is_free(const std::pair<int, int> &cur)
{
    if(is_in_field(cur))
    return field[cur.first][cur.second] == square::free;
    else
        return false;
}

bool Field::is_reserved(const std::pair<int, int> &cur)
{
    return field[cur.first][cur.second] == square::reserved;
}

bool Field::is_in_field(const std::pair<int, int> &cur)
{
    return (cur.first < 10 && cur.second < 10 && cur.first >= 0 && cur.second >= 0);
}

bool Field::is_possible(Ship &cur)
{
    for (const auto &i : cur.get_ship())
    {
        if (!is_in_field(i) || !is_free(i))
            return false;
    }
    return true;
}

void Field::update_count(int count)
{
    switch (count)
    {
        case 1:
            count_single++;
            break;
        case 2:
            count_double++;
            break;
        case 3:
            count_triple++;
            break;
        case 4:
            count_quadruple++;
            break;
    }
}


void Field::set_ship(Ship &cur)
{
    update_count(cur.get_size());

    if (is_possible(cur))
    {
        set_squares(cur.get_ship());
        set_area(cur);
        set_surrounding(cur.get_ship());

    } else
    {
        throw std::logic_error("Пересечение с кораблями или выход за зону \n");
    }
}

void Field::set_squares(const std::vector<std::pair<int, int>> &squares)
{
    for (const auto &i : squares)
    {
        set_filled(i);
    }
}


void Field::set_surrounding(const std::vector<std::pair<int, int>> &squares)
{
    for (const auto &i : squares)
    {

        int x = i.first;
        int y = i.second;

        for (int i = -1; i < 2; i++)
        {
            set_reserved(std::make_pair(x + i, y - 1));
            set_reserved(std::make_pair(x + i, y + 1));
        }

        set_reserved(std::make_pair(x - 1, y));
        set_reserved(std::make_pair(x + 1, y));
    }
}

bool Field::is_almostFull()
{
    return (count_quadruple == 1 && count_triple == 2 && count_double == 3);
}

bool Field::is_full()
{
    return is_almostFull() && count_single == 4;
}

bool Field::check_quadruple()
{
    return count_quadruple == 1;
}

bool Field::check_single()
{
    return count_single == 4;
}

bool Field::check_triple()
{
    return count_triple == 2;
}

bool Field::check_double()
{
    return count_double == 3;
}


bool Field::is_full_of(int cur)
{
    switch(cur)
    {
        case 1:
            return count_single == 4;
        case 2:
            return count_double == 3;
        case 3:
            return count_triple == 2;
        case 4:
            return count_quadruple == 1;
        default:
            throw std::logic_error("bad args in is_full_of");

    }
}