#pragma once
#include "ScenarioApply.h"

class BreakdownsScenario : public ScenarioApply {
public:
    void apply(std::vector<std::shared_ptr<Machine>>& machines) override {
        for(auto& m : machines){ m->setBreakChance(6); }
    }
};