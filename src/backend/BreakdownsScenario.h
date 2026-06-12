#pragma once
#include "ScenarioApply.h"

class BreakdownsScenario : public ScenarioApply {
public:
    void apply(const std::vector<std::shared_ptr<Machine>>& machines) override {
        for (auto& m : machines) {
            if (m->getName() == "Fryer") {
                m->setTotalTime(5);
            }
            m->setBreakChance(6);
        }
    }
};