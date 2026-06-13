#pragma once
#include "ScenarioApply.h"

class NormalScenario : public ScenarioApply {
public:
    void apply(const std::vector<std::shared_ptr<Machine>>& machines) override {
        for(const auto& m : machines){
            if(m->getName() == "Fryer"){
                m->setTotalTime(5);
                m->setBreakChance(2);
            } else{
                m->setBreakChance(1);
            }
        }
    }
};