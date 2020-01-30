#ifndef BATTLESHIP_BOT_ATTACK_H
#define BATTLESHIP_BOT_ATTACK_H

#include <random>
#include "../Field/Field.h"

char toLetter(int a);

class Bot_Attack
{
private:
    Field opponent;
    bool in_process = false;

    std::pair<int, int> previous = {0, 0};
    std::pair<int, int> planned = {-1, 0};

    std::vector<std::pair<int, int>> current_ship;
    std::vector<std::pair<int, int>> alleged_part;

    void search_4();

    void search_2_3();

    void search_1();

    void add_alleged_part(std::pair<int, int> cur);

public:

    void show(std::ostream &out);

    void shot(std::ostream &out);

    void shoot(std::ostream &out);

    void finish(std::ostream &out);

    void miss(std::ostream &out);

    void hit(std::ostream &out);

    void change_planned(int size);

    void kill(std::ostream &out);

};

#endif //BATTLESHIP_BOT_ATTACK_H
