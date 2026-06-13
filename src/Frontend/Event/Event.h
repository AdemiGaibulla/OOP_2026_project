#pragma once

#include <string>
#include <vector>

#include "EventState.h"
#include "Condition.h"
#include "Behaviour.h"

class Event {
private:
    EventState* currentEventState;
    std::vector<EventState*> events;

public:
    Event();

    virtual ~Event();

    EventState* getCurrentEventState();
    const EventState* getCurrentEventState() const;

    void setCurrentEventState(EventState* state);

    EventState* doCurrentEventState();

    EventState* addEventState(
        Condition* condition,
        Behaviour* behaviour
    );

    void linkEventState(
        EventState* from,
        EventState* to
    );
};