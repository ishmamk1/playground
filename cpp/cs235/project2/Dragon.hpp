#ifndef DRAGON_H
#define DRAGON_H

#include "Creature.hpp"

class Dragon : public Creature {
    public:
        enum Element {NONE, FIRE, WATER, EARTH, AIR};

        Dragon();
        Dragon(const std::string& name, Category category=MYSTICAL, int hitpoints=1, int level=1, bool tame=false, Element element=NONE, int num_heads=1, bool can_fly=false);

        void setElement(const Element element);
        std::string getElement() const;
        bool setNumberOfHeads(const int heads);
        int getNumberOfHeads() const;
        void setFlight(bool can_fly);
        bool getFlight() const;


    private:
        Element afinity_;
        int num_heads_;
        bool can_fly_;
};

#endif