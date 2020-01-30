#ifndef BATTLESHIP_SHIP_H
#define BATTLESHIP_SHIP_H

#include <iostream>
#include <utility>
#include <vector>

enum class orientation
{
    up, down, right, left
};

orientation int_to_orient(int cur);

class Ship
{
private:
    std::pair<int, int> start;
    std::pair<int, int> end;
    int size;

    orientation orient;

    std::vector<std::pair<int, int>> ship;
    std::vector<std::pair<int, int>> surrounding;

    void make_ship();

public:
    Ship(std::pair<int, int> start, int size, orientation orient) : start(std::move(start)), size(size), orient(orient)
    {
        make_ship();
    }

    std::vector<std::pair<int, int>> get_ship();
    int get_size();
    orientation get_orient();
    std::pair<int,int> get_start();
    std::pair<int,int> get_end();

    void add_surrounding(std::pair<int, int> temp);
    int size_ofSurrounding();
    bool is_newSurrounding(std::pair<int, int> temp);
};


#endif //BATTLESHIP_SHIP_H