#include "Bot_Attack.h"

char toLetter(int a)
{
    char c;
    switch (a)
    {
        case 0:
            c = 'A';
            break;
        case 1:
            c = 'B';
            break;
        case 2:
            c = 'C';
            break;
        case 3:
            c = 'D';
            break;
        case 4:
            c = 'E';
            break;
        case 5:
            c = 'F';
            break;
        case 6:
            c = 'G';
            break;
        case 7:
            c = 'H';
            break;
        case 8:
            c = 'I';
            break;
        case 9:
            c = 'J';
            break;
        default:
            c = 'X';
    }

    return c;
}

void Bot_Attack::search_4()
{
    if (planned.first == 9)
    {
        planned.first = 0;
        planned.second++;
    } else
    {
        if ((planned.first + 4) > 9)
        {
            planned.second++;
            planned.first = (planned.first + 4) % 9;
        } else
        {
            planned.first = planned.first + 4;
        }
    }
}

void Bot_Attack::search_2_3()
{
    if (planned.first == 9)
    {
        planned.first = 0;
        planned.second++;
    } else
    {
        if ((planned.first + 2) > 9)
        {
            planned.second++;
            planned.first = (planned.first + 2) % 9;
        } else
        {
            planned.first = planned.first + 2;
        }
    }
}


void Bot_Attack::search_1()
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> dist(0, 9);

    int x = dist(generator);
    int y = dist(generator);

    while(!opponent.is_free(std::make_pair(x, y)))
    {
        x = dist(generator);
        y = dist(generator);
    }

    planned = {x, y};
}

void Bot_Attack::add_alleged_part(std::pair<int, int> cur)
{
    int x = cur.first;
    int y = cur.second;

    std::vector<std::pair<int, int>> temp;

    temp.emplace_back(std::make_pair(x + 1, y));
    temp.emplace_back(std::make_pair(x - 1, y));
    temp.emplace_back(std::make_pair(x, y + 1));
    temp.emplace_back(std::make_pair(x, y - 1));

    for (const auto &sq : temp)
    {
        if (opponent.is_in_field(sq) && opponent.is_free(sq))
            alleged_part.emplace_back(sq);
    }
}

void Bot_Attack::show(std::ostream &out)
{
    opponent.show_field(out);
}

void Bot_Attack::shot(std::ostream &out)
{
    while (!opponent.is_free(planned))
    {
        if (!opponent.check_quadruple())
            search_4();
        else if(!opponent.check_double())
            search_2_3();
        else if (!opponent.check_single())
            search_1();
    }

    out << toLetter(planned.second) << " " << planned.first << std::endl;
    previous = planned;
}

void Bot_Attack::shoot(std::ostream &out)
{
    if (!in_process)
        shot(std::cout);
    else
        finish(std::cout);
}

void Bot_Attack::finish(std::ostream &out)
{
    std::pair<int, int> temp = alleged_part.at(alleged_part.size() - 1);
    alleged_part.pop_back();

    std::cout << toLetter(temp.second) << " " << temp.first << std::endl;
    previous = temp;
}

void Bot_Attack::miss(std::ostream &out)
{
    opponent.set_reserved(previous);
}

void Bot_Attack::hit(std::ostream &out)
{
    in_process = true;

    opponent.set_filled(previous);
    current_ship.emplace_back(previous);
    add_alleged_part(previous);
    finish(out);
}

void Bot_Attack::change_planned(int size)
{
    if (size == 4)
    {
        planned = {-1, 0};
    }
}

void Bot_Attack::kill(std::ostream &out)
{
    in_process = false;

    opponent.set_filled(previous);
    current_ship.emplace_back(previous);
    opponent.set_surrounding(current_ship);

    opponent.update_count(current_ship.size());
    change_planned(current_ship.size());

    current_ship.clear();
    alleged_part.clear();

    shot(out);

}
