#include "Creature.hpp"
#include <iostream>

int main() {
    Creature creature;
    std::cout << creature.getName() << std::endl;
    std::cout << creature.getCategory() << std::endl;
    std::cout << creature.getLevel() << std::endl;
    std::cout << creature.getHitpoints() << std::endl;
    std::cout << creature.isTame() << std::endl;

    Creature creature2("ishmam", Creature::MYSTICAL, -1,-1, true);
    std::cout << creature2.getName() << std::endl;
    std::cout << creature2.getCategory() << std::endl;
    std::cout << creature2.getLevel() << std::endl;
    std::cout << creature2.getHitpoints() << std::endl;
    std::cout << creature2.isTame() << std::endl;
}