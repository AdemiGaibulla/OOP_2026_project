#pragma once

#include <string>
#include <vector>

#include "../Element.h"

#include "../../../ObjectComponents/Color/FrameColor.h"
#include "../../../ObjectComponents/Color/GrabColor.h"
#include "../../../ObjectComponents/Color/ButtonColor.h"
#include "../../../ObjectComponents/Color/HeaderColor.h"

class Slider : public DataElement {
private:
    float value;
    float maxVal;
    float minVal;

public:
    Slider(
        const Transformation2& transformation = Transformation2(),
        const BaseColor& baseColor = BaseColor(),
        const FrameColor& frameColor = FrameColor(),
        const GrabColor& grabColor = GrabColor(),
        const std::string& name = "Slider",
        bool active = true,
        float value = 0.0f,
        float minVal = 0.0f,
        float maxVal = 100.0f
    );

    virtual ~Slider();

    float getValue() const;
    float getMaxVal() const;
    float getMinVal() const;
    float* accessValue();  

    void setValue(float value);
    void setMaxVal(float maxVal);
    void setMinVal(float minVal);

    void render() override;
};
