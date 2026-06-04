#pragma once
#include <deque>
#include <memory>
#include "Product.h"
#include "SimulationObject.h"

class Conveyor : public SimulationObject{
    private:
    std::deque<std::shared_ptr<Product>> conveyor_q;
    int capacity;
    std::vector<std::string> newEvents;

    public:
    Conveyor(int i, std::string n, int c) : SimulationObject(i, n), capacity(c) {}

    void update(int tick) override {
        if(conveyor_q.empty()) return;

        if ((next->receive(conveyor_q.front()))) {
            conveyor_q.pop_front();
        }
    }

    bool receive(std::shared_ptr<Product> p){
        if(capacity > conveyor_q.size()){
            conveyor_q.push_back(p);
            return true;
        }
        newEvents.push_back("Overflow at");
        return false;
    }

    ConveyorSnap getSnapshot(){
        ConveyorSnap cs;
        cs.id = id;
        cs.name = name;
        cs.load = conveyor_q.size();
        cs.totalCapacity = capacity;
        cs.events = newEvents;
        return cs;
    }

    void clearEvents(){
        newEvents.clear();
    }
};