#include "Transformation.h"

Transformation2::Transformation2(
    const std::array<int, 2>& location,
    const std::array<int, 2>& size,
     bool transformEnable
)
    : location(location),
      size(size),
      transformEnable(transformEnable)
{}

std::array<int, 2>& Transformation2::getLocation() {
    return location;
}

const std::array<int, 2>& Transformation2::getLocation() const {
    return location;
}

std::array<int, 2>& Transformation2::getSize() {
    return size;
}

const std::array<int, 2>& Transformation2::getSize() const {
    return size;
}

const bool Transformation2::getTransformEnable() const{
    return transformEnable;
}

void Transformation2::setLocation(
    const std::array<int, 2>& location
) {
    this->location = location;
}

void Transformation2::setSize(
    const std::array<int, 2>& size
) {
    this->size = size;
}

void Transformation2::enableTrasform(){
    transformEnable=true;
}

void Transformation2::disableTransform(){
    transformEnable=false;
}