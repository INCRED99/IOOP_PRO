#include "Entity.h"
#include <bits/stdc++.h>

class Player : public Entity {
private:
    int level;
    int currentXP;

public:
    Player(const std::string& n) 
        : Entity(n, 100, 15), level(1), currentXP(0) {}
    
    // Polymorphic implementation of attack
    void attack(Entity* target) override {
        int damage = strength + (level * 2);
        std::cout << name << " strikes " << target->getName() << " with " << damage << " damage!" << std::endl;
        target->takeDamage(damage); 
    }
    
    void gainXP(int amount) {
        currentXP += amount;
        std::cout << name << " gained " << amount << " XP. ";
        // Simple level-up logic
        if (currentXP >= level * 50) {
            level++;
            strength += 5;
            health = 100 + (level * 10); // Heals and increases max health
            currentXP = 0;
            std::cout << "LEVEL UP! Now Level " << level << "!" << std::endl;
        } else {
            std::cout << "XP needed for next level: " << (level * 50) - currentXP << std::endl;
        }
    }
    
    int getLevel() const { return level; }
};