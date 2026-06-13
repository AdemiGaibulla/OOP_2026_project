#include "Slider.h"

Slider::Slider(
    const Transformation2& transformation,
    const BaseColor& baseColor,
    const FrameColor& frameColor,
    const GrabColor& grabColor,
    const std::string& name,
    bool active,
    float value,
    float minVal,
    float maxVal
)
    : DataElement(
        transformation,
        baseColor,
        name,
        active
    ),
      value(value),
      maxVal(maxVal),
      minVal(minVal)
{
    pushColor(new FrameColor(frameColor));
    pushColor(new GrabColor(grabColor));

    setValue(value);
}

Slider::~Slider() {}

float Slider::getValue() const {
    return value;
}

float Slider::getMaxVal() const {
    return maxVal;
}

float Slider::getMinVal() const {
    return minVal;
}


void Slider::setValue(float value) {
    if (value < this->minVal) {
        this->value = this->minVal;
    }
    else if (value > this->maxVal) {
        this->value = this->maxVal;
    }
    else {
        this->value = value;
    }
}

void Slider::setMaxVal(float maxVal) {
    this->maxVal = maxVal;

    if (this->minVal > this->maxVal) {
        this->minVal = this->maxVal;
    }

    setValue(this->value);
}

void Slider::setMinVal(float minVal) {
    this->minVal = minVal;

    if (this->minVal > this->maxVal) {
        this->maxVal = this->minVal;
    }

    setValue(this->value);
}

void Slider::render() {
    if(!isActive()){
        return;
    }

    applyColors();
    position();
    auto temp = getTransformation().getSize();
    ImGui::SliderFloat(
        getIDName(),
        &value,
        getMinVal(),
        getMaxVal(),
        "%.2f"
    );
    update();
    endApplyColors();
}