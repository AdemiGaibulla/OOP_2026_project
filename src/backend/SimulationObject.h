#pragma once
#include <string>
#include <memory>
#include "Product.h"

class SimulationObject{
protected:
    int id;
    std::string name;
    SimulationObject* next = nullptr;

public:
    SimulationObject(int i, std::string n) : id(i), name(n) {}

    virtual ~SimulationObject() {}
    virtual void update(int tick) = 0;
    virtual bool receive(std::shared_ptr<Product> p) = 0;

    void setNext(SimulationObject* next){ this->next = next; }
    int getId() const{ return id; }
    std::string getName() const{ return name; }
};