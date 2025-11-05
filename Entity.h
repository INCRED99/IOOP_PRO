// Entity.h (Only declarations, no implementation details here)
#pragma once
#include <string>
#include <iostream>
#include <cstdlib> // For simple random damage in Monster

class Entity {
protected:
    std::string name;
    int health;
    int strength;
    // NOTE: Protected members are accessible by derived classes (Player/Monster)

public:
    Entity(const std::string& n, int h, int s)
        : name(n), health(h), strength(s) {}

    // PURE VIRTUAL FUNCTION: Makes Entity abstract and forces derived classes to implement
    virtual void attack(Entity* target) = 0; 

    // VIRTUAL FUNCTION: Can be overridden, but has a default implementation
    virtual void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
        std::cout << name << " took " << damage << " damage! Health remaining: " << health << std::endl;
    }

    // Accessors (Encapsulation)
    std::string getName() const { return name; }
    int getHealth() const { return health; }
    bool isAlive() const { return health > 0; }
    
    // Always good practice for a polymorphic base class
    virtual ~Entity() {} 
};
