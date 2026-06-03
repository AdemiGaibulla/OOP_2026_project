#include <vector>
#include <memory>
#include "Machine.h"
#include "Conveyor.h"


class Factory{
    private:
    bool running = false;
    int currentTick = 0;
    int pid = 1;
    int lostProducts = 0;
    int speed = 1;
    Conveyor* entry = nullptr;
    Glazer* lastmachine = nullptr;
    std::vector<std::unique_ptr<SimulationObject>> simulationObjects;
    std::vector<Machine*> machines; 
    std::vector<Conveyor*> conveyors;
    Scenario currentScenario = NORMAL;

    void donutCreation(){
        auto p = std::make_unique<Product>(pid);
        pid++;

        if(!entry->receive(std::move(p))){
            lostProducts++;
        }
    }

    void build(){
        auto shape = std::make_unique<Shape>();
        auto fryer = std::make_unique<Fryer>();
        auto glazer = std::make_unique<Glazer>();

        auto c0 = std::make_unique<Conveyor>(1,"Conveyor0", 6);
        auto c1 = std::make_unique<Conveyor>(2,"Conveyor1", 6);
        auto c2 = std::make_unique<Conveyor>(3,"Conveyor2", 6);

        entry = c0.get();
        lastmachine = glazer.get();

        machines.push_back(shape.get());
        machines.push_back(fryer.get());
        machines.push_back(glazer.get());

        conveyors.push_back(c0.get());
        conveyors.push_back(c1.get());
        conveyors.push_back(c2.get());

        c0->setNext(shape.get());
        shape->setNext(c1.get());
        c1->setNext(fryer.get());
        fryer->setNext(c2.get());
        c2->setNext(glazer.get());
        glazer->setNext(nullptr);

        simulationObjects.push_back(std::move(glazer));
        simulationObjects.push_back(std::move(c2));
        simulationObjects.push_back(std::move(fryer));
        simulationObjects.push_back(std::move(c1));
        simulationObjects.push_back(std::move(shape));
        simulationObjects.push_back(std::move(c0));
    }

    void applyScenario(Scenario s){
        if(s == BOTTLENECK){
            machines[1]->setTotalTime(12);
        }
        else if(s == BREAKDOWNS){
            machines[0]->setBreakChance(6);
            machines[1]->setBreakChance(6);
            machines[2]->setBreakChance(6);
        }
        else if(s == NORMAL){
            machines[1]->setTotalTime(5);
            machines[0]->setBreakChance(1);
            machines[1]->setBreakChance(2);
            machines[2]->setBreakChance(1);
        }
        else if(s == OVERFLOW_SCENARIO){
            machines[1]->setTotalTime(10);
        }
    }

    public:
    Factory (){ build(); }

    void reset(){
        simulationObjects.clear();
        machines.clear();
        conveyors.clear();
        currentTick = 0;
        lostProducts = 0;
        pid = 1;
        running = false;
        build();
        applyScenario(currentScenario);
    }

    void update(){
        if(!running) return;
        currentTick++;

        if(currentTick % 4 == 0) donutCreation();

        for(auto& obj : simulationObjects){
            obj->update(currentTick);
        }
    }

    void applyCmd(SimulationCmd& cmd){
        if(cmd.start) running = true;
        if(cmd.pause) running = false;
        if(cmd.reset) reset();
        speed = cmd.speed;
        currentScenario = cmd.scenario;
        applyScenario(currentScenario);

    }

    void applyMachineCmd(MachineCmd& cmd) {
        for(auto& m : machines) {
            m->applyCmd(cmd, currentTick);
        }
    }

    std::vector<MachineSnap> getSnapshots() const{
        std::vector<MachineSnap> snapshots;
        for(auto& m : machines){
            snapshots.push_back(m->getSnapshot());
        }
        return snapshots;
    }

    std::vector<ConveyorSnap> getConveyorSnapshots() const{
        std::vector<ConveyorSnap> snapshots;
        for(auto& c : conveyors){
            snapshots.push_back(c->getSnapshot());
        }
        return snapshots;
    }

    FactoryStats getStats() const{
        FactoryStats fs;
        fs.finished = lastmachine->getSnapshot().outputCount;
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
};

