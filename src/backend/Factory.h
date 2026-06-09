#pragma once
#include <vector>
#include "Shape.h"
#include "Fryer.h"
#include "Glazer.h" 
#include "Conveyor.h"


class Factory{
private:
    bool running = false;
    int currentTick = 0;
    int pid = 1;
    int lostProducts = 0;
    int speed = 1;
    Conveyor* entry = nullptr;
    std::vector<std::shared_ptr<SimulationObject>> simulationObjects;
    std::vector<std::shared_ptr<Machine>> machines; 
    std::vector<std::shared_ptr<Conveyor>> conveyors;
    Scenario currentScenario = NORMAL;
    std::vector<std::string> events;

    void build(){
        auto shape = std::make_shared<Shape>();
        auto fryer = std::make_shared<Fryer>();
        auto glazer = std::make_shared<Glazer>();

        auto c0 = std::make_shared<Conveyor>(1,"Conveyor0", 6);
        auto c1 = std::make_shared<Conveyor>(2,"Conveyor1", 6);
        auto c2 = std::make_shared<Conveyor>(3,"Conveyor2", 6);

        entry = c0.get();

        machines.push_back(shape);
        machines.push_back(fryer);
        machines.push_back(glazer);

        conveyors.push_back(c0);
        conveyors.push_back(c1);
        conveyors.push_back(c2);

        c0->setNext(shape.get());
        shape->setNext(c1.get());
        c1->setNext(fryer.get());
        fryer->setNext(c2.get());
        c2->setNext(glazer.get());
        glazer->setNext(nullptr);

        simulationObjects.push_back(glazer);
        simulationObjects.push_back(c2);
        simulationObjects.push_back(fryer);
        simulationObjects.push_back(c1);
        simulationObjects.push_back(shape);
        simulationObjects.push_back(c0);
    }

    void tick(){
        currentTick++;

        if(currentTick % 4 == 0) donutCreation();

        for(auto& obj : simulationObjects){
            obj->update(currentTick);
        }

        for(auto& m : machines){
            auto snapshot = m->getSnapshot();
            for(auto& ev : snapshot.events){
                events.push_back("["+std::to_string(currentTick)+"] "+m->getName()+" "+ev);
            }
            m->clearEvents(); 
        }

        for(auto& c : conveyors){
            auto snapshot = c->getSnapshot();
            for(auto& ev : snapshot.events){
                events.push_back("["+std::to_string(currentTick)+"] "+c->getName()+" "+ev);
            }
            c->clearEvents();
        }
    } 
    
    void donutCreation(){
        auto p = std::make_shared<Product>(pid);
        pid++;

        if(!entry->receive(p)){
            lostProducts++;
        }
    }

    void applyScenario(Scenario s){
        if(s == BOTTLENECK){ if (auto* m = findMachine("Fryer")) m->setTotalTime(12); }
        else if(s == BREAKDOWNS){ for (auto& m : machines) m->setBreakChance(6); }
        else if(s == NORMAL){ if (auto* m = findMachine("Fryer")) m->setTotalTime(5); }
        else if(s == OVERFLOW_SCENARIO){ if (auto* m = findMachine("Fryer")) m->setTotalTime(10); }
    }
    
    Machine* findMachine(const std::string& name) {
        for (auto& m : machines)
        if (m->getName() == name) return m.get();
        return nullptr;
    }

    public:
    Factory (){ build(); }

    void reset(){
        simulationObjects.clear();
        machines.clear();
        conveyors.clear();
        events.clear();
        entry = nullptr;
        currentTick = 0;
        lostProducts = 0;
        pid = 1;
        running = false;
        build();
        applyScenario(currentScenario);
    }

    void update(){
        if(!running) return;
        for(int i = 0; i < speed; ++i) tick();
    }

    void applyCmd(SimulationCmd& cmd){
        if(cmd.start) running = true;
        if(cmd.pause) running = false;
        if(cmd.reset) reset();
        if(cmd.speed > 0) speed = cmd.speed;
        if (cmd.scenario != currentScenario) {
            currentScenario = cmd.scenario;
            applyScenario(currentScenario);
        }
    }

    void applyMachineCmd(MachineCmd& cmd) {
        for(auto& m : machines) {
            m->applyCmd(cmd, currentTick);
        }
    }

    std::vector<MachineSnap> getSnapshots(){
        std::vector<MachineSnap> snapshots;
        for(auto& m : machines){
            snapshots.push_back(m->getSnapshot());
        }
        return snapshots;
    }

    std::vector<ConveyorSnap> getConveyorSnapshots(){
        std::vector<ConveyorSnap> snapshots;
        for(auto& c : conveyors){
            snapshots.push_back(c->getSnapshot());
        }
        return snapshots;
    }

    FactoryStats getStats(){
        FactoryStats fs;
        fs.finished = machines.back()->getSnapshot().outputCount;
        fs.currentTick = currentTick;

        int breakdownsSum = 0;
        int productLostSum = 0;
        for(auto& m: machines){
            breakdownsSum += m->getSnapshot().breakdowns;
            productLostSum += m->getSnapshot().lostProducts;
        }
        fs.totalBreakdowns = breakdownsSum;
        fs.totalProductLost = productLostSum + this->lostProducts;

        int totalCreated = pid - 1;
        fs.inProgress = totalCreated - fs.finished - fs.totalProductLost;

        return fs;
    }
    
    std::vector<std::string> getEventLogs(){
        auto copy = events;
        events.clear();
        return copy;
    }
};