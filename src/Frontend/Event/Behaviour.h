#pragma once

#include <string>
#include <vector>

#include "../Object/Assets.h"

class PostBehaviour {};

class Behaviour : public PostBehaviour {
private:
    std::vector<Object*> inputTargetObjs;
    std::vector<Object*> outputTargetObjs;

public:
    Behaviour();
    Behaviour(Object* inputObj);
    Behaviour(const std::vector<Object*>& inputObjs);
    Behaviour(
        const std::vector<Object*>& inputObjs,
        const std::vector<Object*>& outputObjs
    );

    virtual ~Behaviour();

    virtual void behave() = 0;
};