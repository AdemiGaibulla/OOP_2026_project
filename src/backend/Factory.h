#pragma once
#include "FactorySetup.h"


class Factory{
private:
    bool running = false;
    int currentTick = 0;
    int pid = 1;
    int lostProducts = 0;
    int speed = 1;
    Scenario currentScenario = NORMAL;
    std::shared_ptr<FactorySetup> setup;

    void tick(){
        try{
            currentTick++;
            
            if(currentTick % 4 == 0) donutCreation();
            
            for(auto& obj : setup->getSimulationObjects()){
                obj->update(currentTick);
            }
            
            setup->collectEvents(currentTick);
        }
        catch(const std::exception& e){
             running = false;
             throw std::runtime_error(std::string("Factory::tick: ") + e.what());
            }
    } 
    
    void donutCreation(){
        auto p = std::make_shared<Product>(pid);
        pid++;
            
        if(!setup->entryReceive(p)){
            lostProducts++;
        }
    }

    void reset(){
        try{
            setup->build();
            setup->applyScenario(currentScenario);
            currentTick = 0;
            lostProducts = 0;
            pid = 1;
            running = false;
        }
        catch(const std::exception& e){
            throw std::runtime_error(std::string("Factory::reset(): ") + e.what());
        }
    }

    public:
    Factory (){ setup = std::make_shared<FactorySetup>(); }

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
            setup->applyScenario(currentScenario);
        }
    }

    void applyMachineCmd(MachineCmd& cmd) {
        setup->applyMachineCmd(cmd, currentTick);
    }

    std::vector<MachineSnap> getSnapshots() { return setup->getMachineSnapshots(); }
    std::vector<ConveyorSnap> getConveyorSnapshots() { return setup->getConveyorSnapshots(); }
    std::vector<std::string> takeEventLogs() { return setup->takeEventLogs(); }

    FactoryStats getStats() const {
        auto machineSnaps = setup->getMachineSnapshots();

        if(machineSnaps.empty()){
            throw std::runtime_error("Factory::getStats: machines is empty");
        }

        FactoryStats fs;
        fs.finished = machineSnaps.back().outputCount;
        fs.currentTick = currentTick;

        int breakdownsSum = 0;
        int productLostSum = 0;
        for(const auto& m: machineSnaps){
            breakdownsSum += m.breakdowns;
            productLostSum += m.lostProducts;
        }
        fs.totalBreakdowns = breakdownsSum;
        fs.totalProductLost = productLostSum + this->lostProducts;

        int totalCreated = pid - 1;
        fs.inProgress = totalCreated - fs.finished - fs.totalProductLost;

        return fs;
    }
};