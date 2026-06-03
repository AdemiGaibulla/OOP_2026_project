#pragma once
#include <deque>
#include <memory>
#include "Product.h"
#include "SimulationObject.h"

class Conveyor : public SimulationObject{
    private:
    std::deque<std::unique_ptr<Product>> conveyor_q;
    int capacity;

    public:
    Conveyor(int i, std::string n, int c) : SimulationObject(i, n), capacity(c) {}

    void update(int tick) override {
        if(conveyor_q.empty()) return;

        auto p =  std::move(conveyor_q.front());
        conveyor_q.pop_front();

        if (!(next->receive(std::move(p)))) {
            conveyor_q.push_front(std::move(p));
        }
    }

    bool receive(std::unique_ptr<Product> p){
        if(capacity > conveyor_q.size()){
            conveyor_q.push_back(std::move(p));
            return true;
        }
        return false;
    }

    ConveyorSnap getSnapshot() const{
        ConveyorSnap cs;
        cs.id = id;
        cs.name = name;
        cs.load = conveyor_q.size();
        cs.totalCapacity = capacity;
        return cs;
    }
};