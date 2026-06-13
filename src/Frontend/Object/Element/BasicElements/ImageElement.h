#pragma once

#include <string>
#include <vector>


#include "BasicElements.h"

#include "../../../ObjectComponents/Color/FrameColor.h"
#include "../../../ObjectComponents/Color/GrabColor.h"
#include "../../../ObjectComponents/Color/ButtonColor.h"
#include "../../../ObjectComponents/Color/HeaderColor.h"

class SimpleImageElement : public ImageElement {
public:
    SimpleImageElement(
        const Transformation2& transformation = Transformation2(),
        const BaseColor& baseColor = BaseColor(),
        const std::string& name = "SimpleImageElement",
        bool active = true
    );

    void render() override;
};