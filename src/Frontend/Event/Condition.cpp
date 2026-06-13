#include "Condition.h"

Condition::Condition() {}

Condition::Condition(
    Object* inputObj
) {
    if (inputObj != nullptr) {
        inputTargetObjs.push_back(inputObj);
    }
}

Condition::Condition(
    const std::vector<Object*>& inputObjs
)
    : inputTargetObjs(inputObjs)
{}

Condition::~Condition() {}

void Condition::inputRequest() {
    // TODO: Implement input request logic
}