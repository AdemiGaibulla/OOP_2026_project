#pragma once
#include "SimulationObject.h"
#include "Health.h"
#include "EventLog.h"
#include "Product.h"


class Machine : public SimulationObject{
protected:
    MachineState state = IDLE;
    int progress = 0;
    int totalTime;
    int outputCount = 0;
    int lostProducts = 0;
    Health health;
    EventLog event;
    std::shared_ptr<Product> currentProduct;
    std::shared_ptr<Product> finishedProduct = nullptr;

    void forceBreak(int currentTick){
        if(state == BROKEN || state == FIXING) return;
        state = BROKEN;
        health.damage(currentTick);
        progress = 0;
        currentProduct = nullptr;
        lostProducts++;

        event.log("BROKEN");
    }

    void forceRepair(){
        state = IDLE;
        health.repair();
        progress = 0;

        event.log("REPAIRED");
    }

    void autoRepair(int currentTick){
        if(state == BROKEN) state = FIXING;
        if(health.completeRepair(currentTick)) forceRepair();
    }

public:
    Machine(int i, std::string n, int totalT, int breakCh) : SimulationObject(i,n), totalTime(totalT), health(breakCh) {}
    virtual ~Machine() = 0;
    virtual void changeProductState(std::shared_ptr<Product> p) = 0;

    bool receive(std::shared_ptr<Product> p){
        if(state != IDLE) return false;
        currentProduct = p;
        state = WORKING;

        event.log("started P" + std::to_string(p->getId()));
        return true;
    }

    void update(int tick) override{
        if(state == BROKEN || state == FIXING){
            if(health.startFixing(tick)) autoRepair(tick);
        }
        else if(state == IDLE){
            progress = 0;
        }
        else if(state == WORKING){
            health.tickHealth();
            progress++;

            if(health.shouldBreak()){
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
                event.log("finished good P" + std::to_string(pid));
            }
        }
    }

    MachineSnap getSnapshot() const{
        MachineSnap ms;
        ms.id  = id;
        ms.name = name;
        ms.state = state;
        ms.health = health.getHealth();
        ms.progress = progress;
        ms.totalTime = totalTime;
        ms.outputCount = outputCount;
        ms.breakdowns = health.getBreakdowns();
        ms.lostProducts = lostProducts;
        ms.events = event.getevents();
        return ms;
    }

    void clearEvents() { event.clear(); }

    void applyCmd(MachineCmd& cmd, int currentTick){
        if(cmd.id != id) return;
        if(cmd.forceBreak) forceBreak(currentTick);
        if (cmd.forceRepair && (state == BROKEN || state == FIXING)) forceRepair();
    }

    void setBreakChance(int chance) { health.setBreakChance(chance); }
    void setTotalTime(int time) { totalTime = time; }
};

inline Machine::~Machine() {}