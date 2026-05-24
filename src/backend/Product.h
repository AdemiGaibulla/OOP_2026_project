#pragma once
#include "definitions.h"

class Product{
    private:
    int id;
    ProductState state;
    public:
    Product(int i) : id(i), state(RAW) {}

    int getId() const {
        return id;
    }
    ProductState getState() const{
        return state;
    }
    void setState(ProductState ps){
        state = ps;
    }
};