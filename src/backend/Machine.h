#pragma once
#include "SimulationObject.h"
#include "definitions.h"
#include "Product.h"
#include <string>
#include <queue>
#include <memory>


class Machine : public SimulationObject{
private:
    MachineState state;
    double health;
    int progress;
    int totalTime;
    int outputCount;
    std::queue<std::unique_ptr<Product>> q;
    int brokenAt = 0;

    void forceBreak(int currentTick){
        if(state == BROKEN) return;
        state = BROKEN;
        if(health - 30.0 >= 0) health -= 30.0;
        else health = 0;
        brokenAt = currentTick;
    }

    void forceRepair(){
        state = IDLE;
        health = 100.0;
        progress = 0;
        brokenAt = 0;
    }

    void tickHealth(){
        if(state != WORKING) return;
        if(health - 0.5 >= 0) health -= 0.5;
        else health = 0.0;
    }

    void autoRepair(int currentTick){
        if(state != BROKEN) return;
        if(currentTick - brokenAt >= 10){
            state = IDLE;
            brokenAt = 0;
        }

    }

public:
    Machine(int i, std::string n, int totalT) : SimulationObject(i,n), state(IDLE), health(100), progress(0), totalTime(totalT), outputCount(0), brokenAt(0) {}
    virtual ~Machine() {}

    virtual void update(int tick) = 0;
    virtual std::string getInfo() const = 0;

    MachineSnap getSnapshot(int currentTick) const{
        MachineSnap ms;
        ms.id  = id;
        ms.name = name;
        ms.state = state;
        ms.health = health;
        ms.progress = progress;
        ms.totalTime = totalTime;
        ms.queueCount = q.size();
        ms.outputCount = outputCount;
        if(state == BROKEN) ms.repairTime = 7 - (currentTick - brokenAt);
        else ms.repairTime = 0;
        return ms;
    }

    void applyCmd(MachineCmd& cmd, int currentTick){
        if(cmd.id != id) return;
        if(cmd.forceBreak) forceBreak(currentTick);
        if(cmd.forceRepair) forceRepair();
    }

};

class Shape : public Machine{

};

class Fryer : public Machine{

};

class Glazer : public Machine{

};