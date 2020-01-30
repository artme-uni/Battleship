#include <iostream>
#include "Bots/Bot_Attack.h"
#include "Bots/Bot_Arrange.h"

#include "Field/Ship.h"
#include "Field/Field.h"

int main()
{
    Bot_Arrange arrange;
    Bot_Attack attack;

    std::string cmd;

    int i = 0;
    while (getline(std::cin, cmd))
    {
        i++;

        if (cmd == "Arrange!")
        {
            arrange.arrange();
            arrange.print_personal(std::cout);
        } else if (cmd == "Shoot!")
        {
            attack.shoot(std::cout);
        } else if (cmd == "Miss")
        {
            attack.miss(std::cout);
        } else if (cmd == "Hit")
        {
            attack.hit(std::cout);
        } else if (cmd == "Kill")
        {
            attack.kill(std::cout);
        } else if (cmd == "Win!" || cmd == "Lose")
        {
            break;
        } else if (cmd == "Show")
        {
            attack.show(std::cout);
        }
    }


    return 0;
}