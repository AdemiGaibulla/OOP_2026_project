#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include "Shape.h"
#include "Fryer.h"
#include "Glazer.h"
#include "Conveyor.h"
#include "NormalScenario.h"
#include "BreakdownsScenario.h"
#include "BottleneckScenario.h"
#include "OverflowScenario.h"

class FactorySetup
{
private:
    std::vector<std::shared_ptr<SimulationObject>> simulationObjects;
    std::vector<std::shared_ptr<Machine>> machines;
    std::vector<std::shared_ptr<Conveyor>> conveyors;
    std::unordered_map<Scenario, std::shared_ptr<ScenarioApply>> scenarios;
    EventLog events;

public:
    FactorySetup() { build(); }
    void build()
    {
        try
        {
            simulationObjects.clear();
            machines.clear();
            conveyors.clear();
            scenarios.clear();

            events.clear();

            auto shape = std::make_shared<Shape>();
            auto fryer = std::make_shared<Fryer>();
            auto glazer = std::make_shared<Glazer>();

            auto c0 = std::make_shared<Conveyor>(1, "Conveyor0", 6);
            auto c1 = std::make_shared<Conveyor>(2, "Conveyor1", 6);
            auto c2 = std::make_shared<Conveyor>(3, "Conveyor2", 6);

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

            scenarios[NORMAL] = std::make_shared<NormalScenario>();
            scenarios[BREAKDOWNS] = std::make_shared<BreakdownsScenario>();
            scenarios[BOTTLENECK] = std::make_shared<BottleneckScenario>();
            scenarios[OVERFLOW_SCENARIO] = std::make_shared<OverflowScenario>();
        }
        catch (const std::exception &e)
        {
            simulationObjects.clear();
            machines.clear();
            conveyors.clear();
            scenarios.clear();
            events.clear();
            throw std::runtime_error(std::string("FactorySetup::build(): ") + e.what());
        }
    }

    void applyScenario(Scenario s){
        try{
            scenarios.at(s)->apply(machines);
        }
        catch(const std::exception& e){
            throw std::runtime_error(std::string("Factory::applyScenario: ") + e.what());
        }
    }

    void collectEvents(int currentTick){
        for(auto& m : machines){
                auto snapshot = m->getSnapshot();
                for(auto& ev : snapshot.events){
                    events.log("["+std::to_string(currentTick)+"] "+m->getName()+" "+ev);
                }
                m->clearEvents(); 
            }
            
            for(auto& c : conveyors){
                auto snapshot = c->getSnapshot();
                for(auto& ev : snapshot.events){
                    events.log("["+std::to_string(currentTick)+"] "+c->getName()+" "+ev);
                }
                c->clearEvents();
            }
    }

    std::vector<std::string> takeEventLogs() {
        auto copy = events.getevents();
        events.clear();
        return copy;
    }

    std::vector<MachineSnap> getMachineSnapshots() const {
        std::vector<MachineSnap> snapshots;
        for (const auto& m : machines) {
            snapshots.push_back(m->getSnapshot());
        }
        return snapshots;
    }

    std::vector<ConveyorSnap> getConveyorSnapshots() const {
        std::vector<ConveyorSnap> snapshots;
        for (const auto& c : conveyors) {
            snapshots.push_back(c->getSnapshot());
        }
        return snapshots;
    }

    bool entryReceive(std::shared_ptr<Product> p) {
        if (conveyors.empty()) return false;
        return conveyors.at(0)->receive(p);
    }

    void applyMachineCmd(MachineCmd& cmd, int currentTick) {
        for (auto& m : machines) {
            m->applyCmd(cmd, currentTick);
        }
    }

    const std::vector<std::shared_ptr<SimulationObject>> &getSimulationObjects() const { return simulationObjects; }
};