#include "Ship.h"

orientation int_to_orient(int cur)
{
    switch (cur)
    {
        case 0 :
            return orientation::up;
        case 1 :
            return orientation::right;
        case 2 :
            return orientation::down;
        case 3 :
            return orientation::left;
        default:
            return orientation::right;
    }
}

void Ship::make_ship()
{
    int x = start.first;
    int y = start.second;

    for (int i = 0; i < size; i++)
    {
        std::pair<int, int> temp = std::make_pair(x, y);
        ship.emplace_back(temp);

        switch (orient)
        {
            case orientation::right :
                x++;
                break;
            case orientation::left :
                x--;
                break;
            case orientation::up :
                y--;
                break;
            case orientation::down :
                y++;
                break;
        }

        end = ship[ship.size() - 1];
    }
}

void Ship::add_surrounding(std::pair<int, int> temp)
{
    surrounding.emplace_back(temp);
}

std::vector<std::pair<int, int>> Ship::get_ship()
{
    return ship;
}

int Ship::get_size()
{
    return size;
}

std::pair<int, int> Ship::get_start()
{
    return start;
}

bool Ship::is_newSurrounding(std::pair<int, int> temp)
{
    for (const auto &p : surrounding)
    {
        if (temp == p)
            return false;
    }

    return true;
}

int Ship::size_ofSurrounding()
{
    return surrounding.size();
}

orientation Ship::get_orient()
{
    return orient;
}

std::pair<int, int> Ship::get_end()
{
    return end;
}
