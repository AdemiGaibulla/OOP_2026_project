#pragma once
#include "Machine.h"

class Glazer : public Machine{
private:
    void changeProductState(std::shared_ptr<Product> p) override{
        if(p) p->setState(GLAZED);
    }
public:
    Glazer() : Machine(3, "Glazer", 4, 1) {}
};