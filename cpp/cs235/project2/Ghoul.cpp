#include "Ghoul.hpp"


Ghoul::Ghoul() : Creature("NAMELESS", UNDEAD), level_of_decay_{0}, faction_{NONE}, can_transform_{false} {}

Ghoul::Ghoul(const std::string& name, Category category, 
    int hitpoints, int level, bool tame, int level_of_decay, 
    Faction faction, bool can_transform) : Creature(name, category, hitpoints, level, tame) 
{
    setDecay(level_of_decay);
    setFaction(faction);
    setTransformation(can_transform);
}

bool Ghoul::setDecay(const int decay) {
    if (decay <= 0) return false;

    level_of_decay_ = decay;
    return true;
}

int Ghoul::getDecay() const {
    return level_of_decay_;
}

void Ghoul::setFaction(Faction faction) {
    switch (faction)
    {
    case FLESHGORGER:
        faction_ = FLESHGORGER;
        break;
    case SHADOWSTALKER:
        faction_ = SHADOWSTALKER;
        break;
    case PLAGUEWEAVER:
        faction_ = PLAGUEWEAVER;
        break;
    default:
        faction_ = NONE;
        break;
    }
}

std::string Ghoul::getFaction() const {
    switch (faction_)
    {
    case FLESHGORGER:
        return "FLESHGORGER";
        break;
    case SHADOWSTALKER:
        return "SHADOWSTALKER";
        break;
    case PLAGUEWEAVER:
        return "PLAGUEWEAVER";
        break;
    default:
        return "NONE";
        break;
    }
}

void Ghoul::setTransformation(bool can_transform) {
    can_transform_ = can_transform;
}
bool Ghoul::getTransformation() const {
    return can_transform_;
}

