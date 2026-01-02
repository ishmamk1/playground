#ifndef GHOUL_H
#define GHOUL_H

#include "Creature.hpp"

class Ghoul : public Creature {
    public:
        enum Faction {NONE, FLESHGORGER, SHADOWSTALKER, PLAGUEWEAVER};

        Ghoul();
        Ghoul(const std::string& name, Category category=UNDEAD, int hitpoints=1, int level=1, bool tame=false, int level_of_decay = 0, Faction faction=NONE, bool can_transform=false);

        bool setDecay(const int decay);
        int getDecay() const;
        void setFaction(Faction faction);
        std::string getFaction() const;
        void setTransformation(bool can_transform);
        bool getTransformation() const;

    private:
        int level_of_decay_;
        Faction faction_;
        bool can_transform_;
};

#endif