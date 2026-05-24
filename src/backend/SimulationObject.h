#pragma once
#include <string>

class SimulationObject{
    protected:
    int id;
    std::string name;
    public:
    SimulationObject(int i, std::string n) : id(i), name(n) {}

    virtual ~SimulationObject() {}
    virtual void update(int tick) = 0;
    virtual std::string getInfo() const = 0;
    int getId() const{
        return id;
    }
    std::string getName() const{
        return name;
    }
};