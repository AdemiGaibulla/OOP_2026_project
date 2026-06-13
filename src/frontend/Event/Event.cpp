#include "Event.h"

Event::Event()
    : currentEventState(nullptr)
{}

Event::~Event() {
    for (EventState* eventState : events) {
        delete eventState;
    }

    events.clear();
}

EventState* Event::getCurrentEventState() {
    return currentEventState;
}

const EventState* Event::getCurrentEventState() const {
    return currentEventState;
}

void Event::setCurrentEventState(EventState* state) {
    currentEventState = state;
}

EventState* Event::doCurrentEventState() {
    // TODO: Implement current event state execution logic
    return currentEventState;
}

EventState* Event::addEventState(
    Condition* condition,
    Behaviour* behaviour
) {
    EventState* eventState = new EventState(condition, behaviour);

    events.push_back(eventState);

    if (currentEventState == nullptr) {
        currentEventState = eventState;
    }

    return eventState;
}

void Event::linkEventState(
    EventState* from,
    EventState* to
) {
    from->linkNextEvent(to);
}