#pragma once
#include <random>

class Health{
    private:
    double health = 100.0;
    int brokenAt = 0;
    int breakChance;
    int totalBreakdowns = 0;

    int getRandomValue() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dist(0, 100);
        return dist(gen);
    }

    public:
    Health(int bc) : breakChance(bc) {}

    void tickHealth(){
        if(health - 0.5 >= 0) health -= 0.5;
        else health = 0.0;
    }

    void damage(int currentTick){
        totalBreakdowns++;
        if(health - 30.0 >= 0) health -= 30.0;
        else health = 0;
        brokenAt = currentTick;
    }

    void repair(){
        health = 100.0;
        brokenAt = 0;
    }

    bool shouldBreak() { return getRandomValue() < breakChance; }
    bool startFixing(int tick) { return tick - brokenAt >= 5; }
    bool completeRepair(int tick) { return tick - brokenAt >= 10; }
    double getHealth() const { return health; }
    int getBreakdowns() const { return totalBreakdowns; }
    void setBreakChance(int breakch) { breakChance = breakch; }
};