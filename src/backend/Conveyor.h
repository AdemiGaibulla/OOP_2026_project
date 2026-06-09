#pragma once
#include <deque>
#include "SimulationObject.h"
#include "EventLog.h"

class Conveyor : public SimulationObject{
private:
    std::deque<std::shared_ptr<Product>> conveyor_q;
    int capacity;
    EventLog event;
public:
    Conveyor(int i, std::string n, int c) : SimulationObject(i, n), capacity(c) {}

    bool receive(std::shared_ptr<Product> p) {
        if(capacity > conveyor_q.size()){
            conveyor_q.push_back(p);
            return true;
        }
        event.log("Overflow at");
        return false;
    }

    void update(int tick) override {
        if(conveyor_q.empty()) return;

        if ((next->receive(conveyor_q.front()))) {
            conveyor_q.pop_front();
        }
    }

    ConveyorSnap getSnapshot(){
        ConveyorSnap cs;
        cs.id = id;
        cs.name = name;
        cs.load = conveyor_q.size();
        cs.totalCapacity = capacity;
        cs.events = event.getevents();
        return cs;
    }

    void clearEvents(){ event.clear(); }
};