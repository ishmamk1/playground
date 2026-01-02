#include "Ghoul.hpp"
#include <iostream>

int main() {
    Ghoul ghoul;
    std::cout << ghoul.getName() << std::endl;
    std::cout << ghoul.getCategory() << std::endl;
    std::cout << ghoul.getLevel() << std::endl;
    std::cout << ghoul.getHitpoints() << std::endl;
    std::cout << ghoul.isTame() << std::endl;

    Ghoul ghoul2("ishmam", Creature::UNDEAD, 6,-1, true, 3, Ghoul::SHADOWSTALKER, true);
    std::cout << ghoul2.getName() << std::endl;
    std::cout << ghoul2.getCategory() << std::endl;
    std::cout << ghoul2.getLevel() << std::endl;
    std::cout << ghoul2.getHitpoints() << std::endl;
    std::cout << ghoul2.isTame() << std::endl;
    std::cout << ghoul2.getFaction() << std::endl;
    std::cout << ghoul2.getDecay() << std::endl;
    std::cout << ghoul2.getTransformation() << std::endl;

}