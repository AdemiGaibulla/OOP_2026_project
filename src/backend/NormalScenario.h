#pragma once
#include "ScenarioApply.h"

class NormalScenario : public ScenarioApply {
public:
    void apply(std::vector<std::shared_ptr<Machine>>& machines) override {
        for(auto& m : machines){
            if(m->getName() == "Fryer"){
                m->setTotalTime(5);
                m->setBreakChance(2);
            } else{
                m->setBreakChance(1);
            }
        }
    }
};