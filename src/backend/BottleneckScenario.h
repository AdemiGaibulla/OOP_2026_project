#pragma once
#include "ScenarioApply.h"

class BottleneckScenario : public ScenarioApply {
public:
    void apply(const std::vector<std::shared_ptr<Machine>>& machines) override {
        for (auto& m : machines) {
            if (m->getName() == "Fryer") {
                m->setTotalTime(12);
                m->setBreakChance(2);
            } else {
                m->setBreakChance(1);
            }
        }
    }
};