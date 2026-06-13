#include "Behaviour.h"

Behaviour::Behaviour() {}

Behaviour::Behaviour(
    Object* inputObj
) {
    if (inputObj != nullptr) {
        inputTargetObjs.push_back(inputObj);
    }
}

Behaviour::Behaviour(
    const std::vector<Object*>& inputObjs
)
    : inputTargetObjs(inputObjs)
{}

Behaviour::Behaviour(
    const std::vector<Object*>& inputObjs,
    const std::vector<Object*>& outputObjs
)
    : inputTargetObjs(inputObjs),
      outputTargetObjs(outputObjs)
{}

Behaviour::~Behaviour() {}