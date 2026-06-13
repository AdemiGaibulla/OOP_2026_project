#pragma once

#include <array>

#include "ObjComponents.h"

class Transformation : public Parameter {};

class Transformation2 {
private:
    std::array<int, 2> location;
    std::array<int, 2> size;
    bool transformEnable;

public:
    Transformation2(
        const std::array<int, 2>& location = {0, 0},
        const std::array<int, 2>& size = {50, 50},
        bool transformEnable=false
    );

    std::array<int, 2>& getLocation();
    const std::array<int, 2>& getLocation() const;

    std::array<int, 2>& getSize();
    const std::array<int, 2>& getSize() const;


    const bool getTransformEnable() const; 

    void setLocation(const std::array<int, 2>& location);
    void setSize(const std::array<int, 2>& size);

    void enableTrasform();
    void disableTransform();
};