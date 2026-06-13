#pragma once

#include <string>
#include <vector>

#include "../Element.h"
#include "../../../ObjectComponents/Color/FrameColor.h"
#include "../../../ObjectComponents/Color/GrabColor.h"
#include "../../../ObjectComponents/Color/ButtonColor.h"
#include "../../../ObjectComponents/Color/HeaderColor.h"

class TextLabel : public BasicElement {
public:
    TextLabel(
        const Transformation2& transformation = Transformation2(),
        const BaseColor& baseColor = BaseColor(),
        const std::string& name = "TextLabel",
        bool active = true
    );

    virtual ~TextLabel();
};

class Button : public BasicElement {
public:
    Button(
        const Transformation2& transformation = Transformation2(),
        const BaseColor& baseColor = BaseColor(),
        const ButtonColor& buttonColor = ButtonColor(),
        const std::string& name = "Button",
        bool active = true
    );

    virtual ~Button();
};

class ImageElement : public BasicElement {
public:
    ImageElement(
        const Transformation2& transformation = Transformation2(),
        const BaseColor& baseColor = BaseColor(),
        const std::string& name = "ImageElement",
        bool active = true
    );

    virtual ~ImageElement();
};