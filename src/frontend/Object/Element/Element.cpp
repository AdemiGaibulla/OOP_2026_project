#include "Element.h"

Element::Element(
    const Transformation2& transformation,
    const BaseColor& baseColor,
    const std::string& name,
    bool active
)
    : Object(
        Identity(name),
        transformation,
        new ColorManager(),
        new ElementInputManager(),
        active
    )
{
    pushColor(new BaseColor(baseColor));
}

Element::~Element() {}

DataElement::DataElement(
    const Transformation2& transformation,
    const BaseColor& baseColor,
    const std::string& name,
    bool active
)
    : Element(
        transformation,
        baseColor,
        name,
        active
    )
{}

DataElement::~DataElement() {}

BasicElement::BasicElement(
    const Transformation2& transformation,
    const BaseColor& baseColor,
    const std::string& name,
    bool active
)
    : Element(
        transformation,
        baseColor,
        name,
        active
    )
{}

BasicElement::~BasicElement() {}