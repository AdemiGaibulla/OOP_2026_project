#pragma once

#include <string>
#include <vector>

#include "Condition.h"
#include "Behaviour.h"
#include "EventState.h"

class EventState {
private:
    Behaviour* behaviour;
    Condition* condition;
    std::vector<EventState*> nextStates;

public:
    EventState(
        Condition* condition,
        Behaviour* behaviour
    );

    EventState* doEvent();

    void linkNextEvent(EventState* nextEvent);

    virtual ~EventState();
};