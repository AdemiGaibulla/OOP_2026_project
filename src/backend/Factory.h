#pragma once
#include <vector>
#include "Builder.h"


class Factory{
private:
    bool running = false;
    int currentTick = 0;
    int pid = 1;
    int lostProducts = 0;
    int speed = 1;
    std::vector<std::string> events;
    Scenario currentScenario = NORMAL;
    Builder builder;

    void tick(){
        currentTick++;

        if(currentTick % 4 == 0) donutCreation();

        for(auto& obj : builder.getSimulationObjects()){
            obj->update(currentTick);
        }

        for(auto& m : builder.getMachines()){
            auto snapshot = m->getSnapshot();
            for(auto& ev : snapshot.events){
                events.push_back("["+std::to_string(currentTick)+"] "+m->getName()+" "+ev);
            }
            m->clearEvents(); 
        }

        for(auto& c : builder.getConveyors()){
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

        if(!builder.getConveyors()[0]->receive(p)){
            lostProducts++;
        }
    }

    void applyScenario(Scenario s){
        builder.getScenarios().at(s)->apply(builder.getMachines());
    }

    public:
    Factory () = default;

    void reset(){
        builder.build();
    
        applyScenario(currentScenario);
        events.clear();
        currentTick = 0;
        lostProducts = 0;
        pid = 1;
        running = false;
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
        for(auto& m : builder.getMachines()) {
            m->applyCmd(cmd, currentTick);
        }
    }

    std::vector<MachineSnap> getSnapshots(){
        std::vector<MachineSnap> snapshots;
        for(auto& m : builder.getMachines()){
            snapshots.push_back(m->getSnapshot());
        }
        return snapshots;
    }

    std::vector<ConveyorSnap> getConveyorSnapshots(){
        std::vector<ConveyorSnap> snapshots;
        for(auto& c : builder.getConveyors()){
            snapshots.push_back(c->getSnapshot());
        }
        return snapshots;
    }

    FactoryStats getStats() const {
        FactoryStats fs;
        fs.finished = builder.getMachines().back()->getSnapshot().outputCount;
        fs.currentTick = currentTick;

        int breakdownsSum = 0;
        int productLostSum = 0;
        for(auto& m: builder.getMachines()){
            breakdownsSum += m->getSnapshot().breakdowns;
            productLostSum += m->getSnapshot().lostProducts;
        }
        fs.totalBreakdowns = breakdownsSum;
        fs.totalProductLost = productLostSum + this->lostProducts;

        int totalCreated = pid - 1;
        fs.inProgress = totalCreated - fs.finished - fs.totalProductLost;

        return fs;
    }
    
    std::vector<std::string> takeEventLogs(){
        auto copy = events;
        events.clear();
        return copy;
    }
};