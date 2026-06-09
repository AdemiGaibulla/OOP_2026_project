#pragma once
#include "Machine.h"

class Fryer : public Machine{
private:
    void changeProductState(std::shared_ptr<Product> p) override{
        if(p) p->setState(FRIED);
    }
public:
    Fryer() : Machine(2, "Fryer", 5, 2) {}
};