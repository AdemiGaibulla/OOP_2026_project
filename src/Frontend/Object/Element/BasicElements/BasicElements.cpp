#include "BasicElements.h"

TextLabel::TextLabel(
    const Transformation2& transformation,
    const BaseColor& baseColor,
    const std::string& name,
    bool active
)
    : BasicElement(
        transformation,
        baseColor,
        name,
        active
    )
{}

TextLabel::~TextLabel() {}

Button::Button(
    const Transformation2& transformation,
    const BaseColor& baseColor,
    const ButtonColor& buttonColor,
    const std::string& name,
    bool active
)
    : BasicElement(
        transformation,
        baseColor,
        name,
        active
    )
{
    pushColor(new ButtonColor(buttonColor));
}

Button::~Button() {}

ImageElement::ImageElement(
    const Transformation2& transformation,
    const BaseColor& baseColor,
    const std::string& name,
    bool active
)
    : BasicElement(
        transformation,
        baseColor,
        name,
        active
    )
{}

ImageElement::~ImageElement() {}