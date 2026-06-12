#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include "Shape.h"
#include "Fryer.h"
#include "Glazer.h"
#include "Conveyor.h"
#include "NormalScenario.h"
#include "BreakdownsScenario.h"
#include "BottleneckScenario.h"
#include "OverflowScenario.h"


class Builder{
private:
    std::vector<std::shared_ptr<SimulationObject>> simulationObjects;
    std::vector<std::shared_ptr<Machine>> machines; 
    std::vector<std::shared_ptr<Conveyor>> conveyors;
    std::unordered_map<Scenario, std::shared_ptr<ScenarioApply>> scenarios;

public:  
    Builder() { build(); }
    void build(){
        simulationObjects.clear();
        machines.clear();
        conveyors.clear();
        scenarios.clear();

        auto shape = std::make_shared<Shape>();
        auto fryer = std::make_shared<Fryer>();
        auto glazer = std::make_shared<Glazer>();

        auto c0 = std::make_shared<Conveyor>(1,"Conveyor0", 6);
        auto c1 = std::make_shared<Conveyor>(2,"Conveyor1", 6);
        auto c2 = std::make_shared<Conveyor>(3,"Conveyor2", 6);

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

    std::vector<std::shared_ptr<SimulationObject>>& getSimulationObjects() { return simulationObjects; }
    std::vector<std::shared_ptr<Machine>>& getMachines() { return machines; }
    std::vector<std::shared_ptr<Conveyor>>& getConveyors() { return conveyors; }
    std::unordered_map<Scenario, std::shared_ptr<ScenarioApply>>& getScenarios() { return scenarios; }

    const std::vector<std::shared_ptr<Machine>>& getMachines() const { return machines; }
    const std::vector<std::shared_ptr<Conveyor>>& getConveyors() const { return conveyors; }
};