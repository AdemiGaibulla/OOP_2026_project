#pragma once
#include "FactorySetup.h"


class Factory{
private:
    bool running = false;
    int currentTick = 0;
    int pid = 1;
    int lostProducts = 0;
    int speed = 1;
    std::vector<std::string> events;
    Scenario currentScenario = NORMAL;
    FactorySetup setup;

    void tick(){
        try{
            currentTick++;
            
            if(currentTick % 4 == 0) donutCreation();
            
            for(auto& obj : setup.getSimulationObjects()){
                obj->update(currentTick);
            }
            
            for(auto& m : setup.getMachines()){
                auto snapshot = m->getSnapshot();
                for(auto& ev : snapshot.events){
                    events.push_back("["+std::to_string(currentTick)+"] "+m->getName()+" "+ev);
                }
                m->clearEvents(); 
            }
            
            for(auto& c : setup.getConveyors()){
                auto snapshot = c->getSnapshot();
                for(auto& ev : snapshot.events){
                    events.push_back("["+std::to_string(currentTick)+"] "+c->getName()+" "+ev);
                }
                c->clearEvents();
            }
        }
        catch(const std::exception& e){
             running = false;
             throw std::runtime_error(std::string("Factory::tick: ") + e.what());
            }
    } 
    
    void donutCreation(){
        auto p = std::make_shared<Product>(pid);
        pid++;
            
        if(!setup.getConveyors().at(0)->receive(p)){
            lostProducts++;
        }
    }

    void applyScenario(Scenario s){
        try{
            setup.getScenarios().at(s)->apply(setup.getMachines());
        }
        catch(const std::exception& e){
            throw std::runtime_error(std::string("Factory::applyScenario: ") + e.what());
        }
    }

    public:
    Factory () = default;

    void reset(){
        try{
            setup.build();
            
            applyScenario(currentScenario);
            events.clear();
            currentTick = 0;
            lostProducts = 0;
            pid = 1;
            running = false;
        }
        catch(const std::exception& e){
            throw std::runtime_error(std::string("Factory::reset(): ") + e.what());
        }
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
        for(auto& m : setup.getMachines()) {
            m->applyCmd(cmd, currentTick);
        }
    }

    std::vector<MachineSnap> getSnapshots(){
        std::vector<MachineSnap> snapshots;
        for(auto& m : setup.getMachines()){
            snapshots.push_back(m->getSnapshot());
        }
        return snapshots;
    }

    std::vector<ConveyorSnap> getConveyorSnapshots(){
        std::vector<ConveyorSnap> snapshots;
        for(auto& c : setup.getConveyors()){
            snapshots.push_back(c->getSnapshot());
        }
        return snapshots;
    }

    FactoryStats getStats() const {
        if(setup.getMachines().empty()){
            throw std::runtime_error("Factory::getStats: machines is empty");
        }

        FactoryStats fs;
        fs.finished = setup.getMachines().back()->getSnapshot().outputCount;
        fs.currentTick = currentTick;

        int breakdownsSum = 0;
        int productLostSum = 0;
        for(auto& m: setup.getMachines()){
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