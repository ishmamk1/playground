#include "Cavern.hpp"

Cavern::Cavern() : ArrayBag<Creature>(), level_sum_{0}, tame_count_{0} {};

bool Cavern::enterCavern(Creature& creature) {
    if (contains(creature)) {
        return false;
    }

    add(creature);

    level_sum_ += creature.getLevel();
    tame_count_ += creature.isTame();
    return true;
};



bool Cavern::exitCavern(Creature& creature) {
    if (!remove(creature)) {
        return false;
    }

    level_sum_ -= creature.getLevel();
    tame_count_ -= creature.isTame();
    return true;
}

int Cavern::getLevelSum() const {
    return level_sum_;
};

int Cavern::calculateAvgLevel() const {
    return level_sum_ / getCurrentSize();
}

int Cavern::getTameCount() const {
    return tame_count_;
}

double Cavern::calculateTamePercentage() const {
    if (isEmpty()) return 0.0;

    return static_cast<double> tame_count_;
}

int tallyCategory(const std::string& category) const;
int releaseCreaturesBelowLevel(const int level) const;
int releaseCreaturesOfCategory(const std::string& category) const;
void cavernReport();