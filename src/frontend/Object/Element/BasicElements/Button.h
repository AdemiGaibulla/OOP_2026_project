#pragma once

#include <string>
#include <vector>

#include "BasicElements.h"

#include "../../../ObjectComponents/Color/FrameColor.h"
#include "../../../ObjectComponents/Color/GrabColor.h"
#include "../../../ObjectComponents/Color/ButtonColor.h"
#include "../../../ObjectComponents/Color/HeaderColor.h"

class SimpleButton : public Button {
public:
    SimpleButton(
        const Transformation2& transformation = Transformation2(),
        const BaseColor& baseColor = BaseColor(),
        const ButtonColor& buttonColor = ButtonColor(),
        const std::string& name = "SimpleButton",
        bool active = true
    );

    void render() override;
};
