#include "CheckBox.h"

CheckBox::CheckBox(
        const Transformation2& transformation = Transformation2(),
        const BaseColor& baseColor = BaseColor(),
        const FrameColor& frameColor = FrameColor(),
        const GrabColor& grabColor = GrabColor(),
        const std::string& name = "CheckBox",
        bool active = true,
        bool select = false
    )
    : DataElement(
        transformation,
        baseColor,
        name,
        active
    ),
      select(select)
{}

CheckBox::~CheckBox() {}

int CheckBox::getSelect() const {
    return select;
}

void CheckBox::setSelect(bool select) {
    this->select = select;
}


void CheckBox::render() {
    if(!isActive()){
        return;
    }

    applyColors();
    position();
    auto temp = getTransformation().getSize();
    ImGui::Checkbox(
        getIDName(),
        &select
    );
    update();
    endApplyColors();
}