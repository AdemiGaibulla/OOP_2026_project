#pragma once
#include "Machine.h"

class Shape : public Machine{
private:
    void changeProductState(std::shared_ptr<Product> p) override{
        if(p) p->setState(SHAPED);
    }
public:
    Shape() : Machine(1, "Shape", 3, 1) {}
};