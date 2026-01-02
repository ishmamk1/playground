#include "Creature.hpp"
#include <iostream>


Creature::Creature() : name_{"NAMELESS"}, category_{Category::UNKNOWN}, hitpoints_{1}, level_{1} {}

Creature::Creature(const std::string& name, Category category, int hitpoints, int level, bool tame) : category_{category}, is_tame_{tame} {
    setName(name);
    setHitpoints(std::max(hitpoints, 1));
    setLevel(std::max(level, 1));
};

bool Creature::setName(const std::string& name) {
    std::string uppercase_name;

    for (const char& ch : name) {
        if (!isalpha(ch)) {
            return false;
        }
        uppercase_name += toupper(ch);
    }
    name_ = uppercase_name;
    return true;
}


std::string Creature::getName() const {
    return name_;
}

void Creature::setCategory(Category category) {
    switch (category) {
        case UNDEAD:
            category_ = UNDEAD;
            break;
        case MYSTICAL:
            category_ = MYSTICAL;
            break;
        case ALIEN:
            category_ = ALIEN;
            break;
        default:
            category_ = UNKNOWN;
            break;
    };
}
std::string Creature::getCategory() const {
    switch (category_) {
        case UNDEAD:
            return "UNDEAD";
        case MYSTICAL:
            return "MYSTICAL";
        case ALIEN:
            return "ALIEN";
        default:
            return "UNKNOWN";
    };
}

bool Creature::setHitpoints(int hitpoints) {
    if (hitpoints < 0) return false;
    hitpoints_ = hitpoints;
    return true;
}
int Creature::getHitpoints() const {
    return hitpoints_;
}

bool Creature::setLevel(int level) {
    if (level < 0) return false;
    level_ = level;
    return true;
}
int Creature::getLevel() const {
    return level_;
}

void Creature::setTame(bool tame) {
    is_tame_ = tame;
}
bool Creature::isTame() const {
    return is_tame_;
}

void Creature::display() const {
    
}
