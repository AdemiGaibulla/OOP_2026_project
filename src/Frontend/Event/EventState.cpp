#include "EventState.h"

EventState::EventState(
    Condition* condition,
    Behaviour* behaviour
)
    : behaviour(behaviour),
      condition(condition)
{}

EventState::~EventState() {
    delete behaviour;
    delete condition;
}

EventState* EventState::doEvent() {
    // TODO: Implement event state execution logic
    return this;
}

void EventState::linkNextEvent(
    EventState* nextEvent
) {
    nextStates.push_back(nextEvent);
}