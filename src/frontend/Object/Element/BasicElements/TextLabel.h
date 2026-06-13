#pragma once

#include <string>
#include <vector>


#include "BasicElements.h"

#include "../../../ObjectComponents/Color/FrameColor.h"
#include "../../../ObjectComponents/Color/GrabColor.h"
#include "../../../ObjectComponents/Color/ButtonColor.h"
#include "../../../ObjectComponents/Color/HeaderColor.h"

class SimpleTextLabel : public TextLabel {
public:
    SimpleTextLabel(
        const Transformation2& transformation = Transformation2(),
        const BaseColor& baseColor = BaseColor(),
        const std::string& name = "SimpleTextLabel",
        bool active = true
    );

    void render() override;
};
