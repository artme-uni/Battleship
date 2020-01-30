#ifndef BATTLESHIP_BOT_ARRANGE_H
#define BATTLESHIP_BOT_ARRANGE_H

#include "../Field/Field.h"
#include <random>
#include <limits>
#include <algorithm>

class Bot_Arrange
{
private:
    Field personal;

    std::vector<std::pair<int, int>> available_corns;

    void add_corn(std::pair<int, int> corn);
    void update_corns(Ship temp);

public:

    Bot_Arrange()
    {
        available_corns.emplace_back(std::make_pair(0, 0));
        available_corns.emplace_back(std::make_pair(0, 9));
        available_corns.emplace_back(std::make_pair(9, 9));
        available_corns.emplace_back(std::make_pair(9, 0));
    }

    void arrange();

    void arrange_single();

    void print_personal(std::ostream &out);

};


#endif //BATTLESHIP_BOT_ARRANGE_H
