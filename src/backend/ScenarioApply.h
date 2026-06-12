#pragma once
#include <vector>
#include <memory>
#include "Machine.h"

class ScenarioApply {
public:
    ScenarioApply() = default;
    virtual ~ScenarioApply() = 0;

    virtual void apply(std::vector<std::shared_ptr<Machine>>& machines) = 0;
};

inline ScenarioApply::~ScenarioApply() {}