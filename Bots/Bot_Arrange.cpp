#include "Bot_Arrange.h"

void Bot_Arrange::arrange_single()
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> dist(0, 9);

    for (int i = 0; i < 4; i++)
    {
        int x = dist(generator);
        int y = dist(generator);

        while (!personal.is_free(std::make_pair(x, y)))
        {
            x = dist(generator);
            y = dist(generator);
        }

        Ship sh(std::make_pair(x, y), 1, orientation::up);
        personal.set_ship(sh);
    }
}

void Bot_Arrange::arrange()
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> dist_size(2, 4);

    while (!personal.is_almostFull())
    {
        int min_area = INT8_MAX;
        int size_ship = dist_size(generator);
        while (personal.is_full_of(size_ship))
            size_ship = dist_size(generator);

        std::vector<Ship> available_ships;

        for (const auto &corn : available_corns)
        {
            for (int i = 0; i < 4; i++)
            {
                Ship temp_ship(corn, size_ship, int_to_orient(i));
                if (personal.is_possible(temp_ship))
                {
                    personal.set_area(temp_ship);
                    int cur_size = temp_ship.size_ofSurrounding();

                    if (min_area > cur_size)
                    {
                        available_ships.clear();
                        available_ships.emplace_back(temp_ship);
                        min_area = cur_size;
                    } else if (min_area == cur_size)
                        available_ships.emplace_back(temp_ship);
                }
            }
        }

        std::uniform_int_distribution<int> dist_available_ships(0, available_ships.size() - 1);
        int cur_ship = dist_available_ships(generator);

        personal.set_ship(available_ships.at(cur_ship));
        update_corns(available_ships.at(cur_ship));
    }

    arrange_single();
}

void Bot_Arrange::update_corns(Ship temp)
{
    auto start = std::find(available_corns.begin(), available_corns.end(), temp.get_start());
    available_corns.erase(start);

    if (temp.get_orient() == orientation::right || temp.get_orient() == orientation::left)
    {
        add_corn(std::make_pair(temp.get_start().first, temp.get_start().first + 2));
        add_corn(std::make_pair(temp.get_start().first, temp.get_start().first - 2));
        add_corn(std::make_pair(temp.get_end().first + 2, temp.get_end().first));
        add_corn(std::make_pair(temp.get_end().first - 2, temp.get_end().first));
    } else
    {
        add_corn(std::make_pair(temp.get_start().first + 2, temp.get_start().first));
        add_corn(std::make_pair(temp.get_start().first - 2, temp.get_start().first));
        add_corn(std::make_pair(temp.get_end().first, temp.get_end().first + 2));
        add_corn(std::make_pair(temp.get_end().first, temp.get_end().first - 2));
    }
}

void Bot_Arrange::add_corn(std::pair<int, int> corn)
{
    if (personal.is_in_field(corn))
        available_corns.emplace_back(corn);
}

void Bot_Arrange::print_personal(std::ostream &out)
{
    personal.print_field(out);
}
