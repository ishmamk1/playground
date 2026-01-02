#ifndef CREATURE_H
#define CREATURE_H

#include <string>

class Creature {
    public:
        enum Category { UNKNOWN, UNDEAD, MYSTICAL, ALIEN };
        
        Creature();
        Creature(const std::string&name, Category category=UNKNOWN, int hitpoints=1, int level=1, bool tame=false);

        bool setName(const std::string& name);
        std::string getName() const;

        void setCategory(Category category);
        std::string getCategory() const;

        bool setHitpoints(int hitpoints);
        int getHitpoints() const;

        bool setLevel(int level);
        int getLevel() const;

        void setTame(bool tame);
        bool isTame() const;

        void display() const;

    private:
        std::string name_;
        Category category_;
        int hitpoints_;
        int level_;
        bool is_tame_;
};

#endif