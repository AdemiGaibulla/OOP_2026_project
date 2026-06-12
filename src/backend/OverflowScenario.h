#pragma once
#include "ScenarioApply.h"

class OverflowScenario : public ScenarioApply {
public:
    void apply(std::vector<std::shared_ptr<Machine>>& machines) override {
        for(auto& m : machines){
            if(m->getName() == "Fryer"){
                m->setTotalTime(10);
            }
        }
    }
};