// Game.h
#pragma once
#include <map>
#include <vector>
#include <sstream>
#include "Player.h"
#include "Monster.h"

// Simple forward declaration for Room.
class Room {
private:
    std::string description;
    // Map of Exit direction ("north") to the Room ID (int)
    std::map<std::string, int> exits; 
    std::vector<Monster*> monsters; // Aggregation/Composition
    
public:
    Room(const std::string& desc) : description(desc) {}
    ~Room() { for (auto m : monsters) delete m; }

    void addExit(const std::string& direction, int nextRoomID) {
        exits[direction] = nextRoomID;
    }
    
    void addMonster(Monster* m) {
        monsters.push_back(m);
    }
    
    // Core Display Function
    void displayInfo() const {
        std::cout << "\n==========================================" << std::endl;
        std::cout << description << std::endl;
        std::cout << "Exits: ";
        for (const auto& pair : exits) {
            std::cout << "[" << pair.first << "] ";
        }
        std::cout << "\nMonsters Present: " << monsters.size() << std::endl;
        for (const auto& m : monsters) {
            std::cout << " - " << m->getName() << " (HP: " << m->getHealth() << ")" << std::endl;
        }
        std::cout << "==========================================" << std::endl;
    }
    
    int getExitID(const std::string& direction) const {
        if (exits.count(direction)) {
            return exits.at(direction);
        }
        return -1; // Invalid exit
    }
    
    std::vector<Monster*>& getMonsters() { return monsters; }
};


class Game {
private:
    std::map<int, Room*> worldMap;
    Player* player;
    int currentRoomID;
    bool isRunning;

    // Internal methods
    void processCommand(const std::string& command);
    void handleMove(const std::string& direction);
    void handleAttack();
    void handleStatus() const;
    void setupMap();

public:
    Game() : player(new Player("Hero")), currentRoomID(1), isRunning(true) {
        srand(time(0)); // Seed random number generator
        setupMap();
    }
    ~Game() {
        delete player;
<<<<<<< HEAD
        for (auto const&entry : worldMap) delete entry.second;
=======
        for (auto const& [id, room] : worldMap) delete room;
>>>>>>> 253370af55256d87389ffc8d9df32379e7f28fe0
    }

    void startLoop() {
        std::cout << "Welcome to the C++ RPG Adventure!" << std::endl;
        while (isRunning && player->isAlive()) {
            worldMap[currentRoomID]->displayInfo();
            std::cout << "\nWhat will you do? (move/attack/status/quit): ";
            std::string input;
            std::getline(std::cin, input);
            processCommand(input);
        }
        if (!player->isAlive()) {
            std::cout << "\n*** GAME OVER: " << player->getName() << " has been defeated. ***" << std::endl;
        } else {
            std::cout << "\nSaving progress and exiting game." << std::endl;
        }
    }
};

// Implementations for Game methods (often placed in Game.cpp)
void Game::setupMap() {
    // Room 1: Starting Area
    Room* r1 = new Room("You are in a dimly lit starting chamber. There is a path to the north.");
    r1->addExit("north", 2);
    worldMap[1] = r1;

    // Room 2: The Forest Path
    Room* r2 = new Room("A winding forest path. You hear growling nearby. You can go north or south.");
    r2->addExit("north", 3);
    r2->addExit("south", 1);
    r2->addMonster(new Monster("Goblin", 30, 8, 10)); // Name, HP, Strength, XP
    worldMap[2] = r2;
    
    // Room 3: The Boss Lair (Winning condition is defeating the Boss)
    Room* r3 = new Room("This is the Boss Lair! A massive Ogre guards a treasure chest! South leads back.");
    r3->addExit("south", 2);
    r3->addMonster(new Monster("Ogre Boss", 150, 25, 100)); // The big challenge
    worldMap[3] = r3;
}

void Game::handleMove(const std::string& direction) {
    int nextID = worldMap[currentRoomID]->getExitID(direction);
    if (nextID != -1) {
        currentRoomID = nextID;
        std::cout << "You move " << direction << "." << std::endl;
    } else {
        std::cout << "You cannot go that way." << std::endl;
    }
}

void Game::handleAttack() {
    Room* currentRoom = worldMap[currentRoomID];
    if (currentRoom->getMonsters().empty()) {
        std::cout << "There are no monsters to attack here." << std::endl;
        return;
    }
    
    // Simple combat: player targets the first monster in the list
    Monster* target = currentRoom->getMonsters().front();
    
    // Combat Loop (simplified single turn)
    std::cout << "\n*** COMBAT TURN ***" << std::endl;
    
    // Player's Turn
    player->attack(target);

    if (!target->isAlive()) {
        std::cout << target->getName() << " is defeated!" << std::endl;
        player->gainXP(target->getXPValue());
        
        // Remove monster from the room (Memory management is crucial here!)
        currentRoom->getMonsters().erase(currentRoom->getMonsters().begin());
        delete target;

        // Check for winning condition
        if (currentRoomID == 3 && currentRoom->getMonsters().empty()) {
            std::cout << "\n*** YOU HAVE DEFEATED THE OGRE AND WON THE GAME! ***" << std::endl;
            isRunning = false;
        }
        return;
    }

    // Monster's Turn (only if the monster survived the player's attack)
    target->attack(player);
}

void Game::handleStatus() const {
    std::cout << "\n*** PLAYER STATUS ***" << std::endl;
    std::cout << "Name: " << player->getName() << std::endl;
    std::cout << "Level: " << player->getLevel() << std::endl;
    std::cout << "Health: " << player->getHealth() << std::endl;
    std::cout << "---------------------" << std::endl;
}

void Game::processCommand(const std::string& input) {
    std::stringstream ss(input);
    std::string verb;
    std::string noun;
    ss >> verb;
    ss >> noun; // Reads the second word (e.g., 'north' for 'move north')

    if (verb == "move") {
        handleMove(noun);
    } else if (verb == "attack") {
        handleAttack();
    } else if (verb == "status") {
        handleStatus();
    } else if (verb == "quit" || verb == "exit") {
        isRunning = false;
    } else {
        std::cout << "Unknown command. Try: move [direction], attack, status, or quit." << std::endl;
    }
}