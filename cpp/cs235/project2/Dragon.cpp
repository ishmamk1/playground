#include "Dragon.hpp"

Dragon::Dragon() : Creature("NAMELESS", MYSTICAL), afinity_{NONE}, num_heads_{1}, can_fly_{false}  {}

Dragon::Dragon(const std::string& name, Category category, 
               int hitpoints, int level, bool tame, Element element, 
               int num_heads, bool can_fly) : Creature(name, category, hitpoints, level, tame) 
{
    setNumberOfHeads(num_heads);
    setFlight(can_fly);
    setElement(element);
}

void Dragon::setElement(const Element element) {
    switch (element)
    {
    case FIRE:
        afinity_ = FIRE;
        break;
    case WATER:
        afinity_ = WATER;
        break;
    case EARTH:
        afinity_ = EARTH;
        break;
    case AIR:
        afinity_ = AIR;
        break;
    default:
        afinity_ = NONE;
        break;
    }
}

std::string Dragon::getElement() const {
    switch (afinity_)
        {
        case FIRE:
            return "FIRE";
            break;
        case WATER:
            return "WATER";
            break;
        case EARTH:
            return "EARTH";
            break;
        case AIR:
            return "AIR";
            break;
        default:
            return "NONE";
            break;
    }
}

bool Dragon::setNumberOfHeads(const int heads) {
    if (heads <= 0) return false;

    num_heads_ = heads;
    return true;
}

int Dragon::getNumberOfHeads() const {
    return num_heads_;
}

void Dragon::setFlight(bool can_fly) {
    can_fly_ = can_fly;
}

bool Dragon::getFlight() const {
    return can_fly_;
}