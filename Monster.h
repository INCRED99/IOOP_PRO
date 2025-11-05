#include "Entity.h"
#include <bits/stdc++.h>

class Monster : public Entity {
private:
    int xpValue;

public:
    Monster(const std::string& n, int h, int s, int xp)
        : Entity(n, h, s), xpValue(xp) {}

    // Polymorphic implementation of attack
    void attack(Entity* target) override {
        // Monster has simple random damage
        int damage = strength + (rand() % 5);
        std::cout << name << " lunges at " << target->getName() << " for " << damage << " damage!" << std::endl;
        target->takeDamage(damage);
    }
    
    int getXPValue() const { return xpValue; }
};