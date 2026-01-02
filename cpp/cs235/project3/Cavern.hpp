#ifndef CAVERN_H
#define CAVERN_H

#include "ArrayBag.hpp"
#include "Creature.hpp"

class Cavern : public ArrayBag<Creature> {
    public:
        bool enterCavern(Creature& creature);
        bool exitCavern(Creature& creature);
        int getLevelSum() const;
        int calculateAvgLevel() const;
        int getTameCount() const;
        double calculateTamePercentage() const;
        int tallyCategory(const std::string& category) const;
        int releaseCreaturesBelowLevel(const int level) const;
        int releaseCreaturesOfCategory(const std::string& category) const;
        void cavernReport();
    private:
        int level_sum_;
        int tame_count_;
};

#endif