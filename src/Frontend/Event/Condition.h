#pragma once

#include <string>
#include <vector>

#include "../Object/Assets.h"

class PostCondition {};

class Condition : public PostCondition {
private:
    std::vector<Object*> inputTargetObjs;

public:
    Condition();
    Condition(Object* inputObj);
    Condition(const std::vector<Object*>& inputObjs);

    virtual ~Condition();

    virtual bool check() = 0;
    void inputRequest();
};