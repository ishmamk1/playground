#include "Dragon.hpp"
#include <iostream>

int main() {
    Dragon dragon;
    std::cout << dragon.getName() << std::endl;
    std::cout << dragon.getCategory() << std::endl;
    std::cout << dragon.getLevel() << std::endl;
    std::cout << dragon.getHitpoints() << std::endl;
    std::cout << dragon.isTame() << std::endl;

    Dragon dragon2("ishmam", Creature::MYSTICAL, -1,-1, true, Dragon::FIRE, 2, true);
    std::cout << dragon2.getName() << std::endl;
    std::cout << dragon2.getCategory() << std::endl;
    std::cout << dragon2.getLevel() << std::endl;
    std::cout << dragon2.getHitpoints() << std::endl;
    std::cout << dragon2.isTame() << std::endl;
    std::cout << dragon2.getElement() << std::endl;
    std::cout << dragon2.getFlight() << std::endl;
    std::cout << dragon2.getNumberOfHeads() << std::endl;

}