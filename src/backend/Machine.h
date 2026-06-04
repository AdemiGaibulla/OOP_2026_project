#pragma once
#include "SimulationObject.h"
#include "definitions.h"
#include "Product.h"
#include <string>
#include <queue>
#include <memory>
#include <random>


class Machine : public SimulationObject{
protected:
    MachineState state;
    double health;
    int progress;
    int totalTime;
    int outputCount;
    int brokenAt = 0;
    int breakChance;
    int totalBreakdowns = 0;
    int lostProducts = 0;
    std::shared_ptr<Product> currentProduct;
    std::shared_ptr<Product> finishedProduct = nullptr;
    std::vector<std::string> newEvents;

    void forceBreak(int currentTick){
        if(state == BROKEN || state == FIXING) return;
        state = BROKEN;
        totalBreakdowns++;
        if(health - 30.0 >= 0) health -= 30.0;
        else health = 0;
        brokenAt = currentTick;
        progress = 0;
        currentProduct = nullptr;
        lostProducts++;

        newEvents.push_back("BROKEN");
    }

    void forceRepair(){
        state = IDLE;
        health = 100.0;
        brokenAt = 0;
        progress = 0;

        newEvents.push_back("REPAIRED");
    }

    void tickHealth(){
        if(state != WORKING) return;
        if(health - 0.5 >= 0) health -= 0.5;
        else health = 0.0;
    }

    void autoRepair(int currentTick){
        if(state == BROKEN) state = FIXING;
        if(currentTick - brokenAt >= 10) forceRepair();
    }

    int getRandomValue() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dist(0, 100);
        return dist(gen);
    }

public:
    Machine(int i, std::string n, int totalT, int breakCh) : SimulationObject(i,n), state(IDLE), health(100), progress(0), totalTime(totalT), outputCount(0), brokenAt(0), breakChance(breakCh) {}
    virtual ~Machine() = 0;
    virtual void changeProductState(std::shared_ptr<Product> p) = 0;

    bool receive(std::shared_ptr<Product> p){
        if(state != IDLE) return false;
        currentProduct = p;
        state = WORKING;

        newEvents.push_back("started P" + std::to_string(p->getId()));
        return true;
    }

    void update(int tick) override{
        if(state == BROKEN || state == FIXING){
            if(tick - brokenAt >= 5) autoRepair(tick);
        }
        else if(state == IDLE){
            progress = 0;
        }
        else if(state == WORKING){
            tickHealth();
            progress++;

            if(getRandomValue() < breakChance){
                forceBreak(tick);
                return;
            }
            
            if(progress >= totalTime){
                int pid = currentProduct->getId();
                changeProductState(currentProduct);
                finishedProduct = currentProduct;
                outputCount++;

                if(next != nullptr){
                    if(!next->receive(finishedProduct)){
                        lostProducts++;
                    }
                }
                finishedProduct = nullptr;
                progress = 0;
                state = IDLE;
                newEvents.push_back("finished good P" + std::to_string(pid));
            }
        }
    }

    MachineSnap getSnapshot(){
        MachineSnap ms;
        ms.id  = id;
        ms.name = name;
        ms.state = state;
        ms.health = health;
        ms.progress = progress;
        ms.totalTime = totalTime;
        ms.outputCount = outputCount;
        ms.breakdowns = totalBreakdowns;
        ms.lostProducts = lostProducts;
        ms.events = newEvents;
        return ms;
    }

    void clearEvents(){
        newEvents.clear();
    }

    void applyCmd(MachineCmd& cmd, int currentTick){
        if(cmd.id != id) return;
        if(cmd.forceBreak) forceBreak(currentTick);
        if (cmd.forceRepair && (state == BROKEN || state == FIXING)) forceRepair();
    }

    void setBreakChance(int chance) { breakChance = chance; }
    void setTotalTime(int time) { totalTime = time; }
};

inline Machine::~Machine() {}

class Shape : public Machine{
    private:
    void changeProductState(std::shared_ptr<Product> p) override{
        if(p) p->setState(SHAPED);
    }
    public:
    Shape() : Machine(1, "Shape", 3, 1) {}

    void update(int tick) override {
        Machine::update(tick);
    }
};

class Fryer : public Machine{
    private:
    void changeProductState(std::shared_ptr<Product> p) override{
        if(p) p->setState(FRIED);
    }
    public:
    Fryer() : Machine(2, "Fryer", 5, 2) {}

    void update(int tick) override {
        Machine::update(tick);
    }
};

class Glazer : public Machine{
    private:
    void changeProductState(std::shared_ptr<Product> p) override{
        if(p) p->setState(GLAZED);
    }
    public:
    Glazer() : Machine(3, "Glazer", 4, 1) {}

    void update(int tick) override {
        Machine::update(tick);
    }
};