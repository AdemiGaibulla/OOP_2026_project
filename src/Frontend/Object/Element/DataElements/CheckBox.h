#pragma once

#include <string>
#include <vector>

#include "../Element.h"

#include "../../../ObjectComponents/Color/FrameColor.h"
#include "../../../ObjectComponents/Color/GrabColor.h"
#include "../../../ObjectComponents/Color/ButtonColor.h"
#include "../../../ObjectComponents/Color/HeaderColor.h"

class CheckBox : public DataElement {
private:
    bool select;

public:
    CheckBox(
        const Transformation2& transformation = Transformation2(),
        const BaseColor& baseColor = BaseColor(),
        const FrameColor& frameColor = FrameColor(),
        const GrabColor& grabColor = GrabColor(),
        const std::string& name = "CheckBox",
        bool active = true,
        bool select = false
    );

    virtual ~CheckBox();

    int getSelect() const;
    void setSelect(bool select);

    void render() override;
};