#include "ImageElement.h"

SimpleImageElement::SimpleImageElement(
    const Transformation2& transformation,
    const BaseColor& baseColor,
    const std::string& name,
    bool active
)
    : ImageElement(
        transformation,
        baseColor,
        name,
        active
    )
{}

void SimpleImageElement::render() {
    // TODO: Implement render logic
}