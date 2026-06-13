#include "Button.h"

SimpleButton::SimpleButton(
    const Transformation2& transformation,
    const BaseColor& baseColor,
    const ButtonColor& buttonColor,
    const std::string& name,
    bool active
)
    : Button(
        transformation,
        baseColor,
        buttonColor,
        name,
        active
    )
{}

void SimpleButton::render() {
    if(!isActive()){
        return;
    }

    applyColors();
    position();
    auto temp = getTransformation().getSize();
    ImGui::Button(
        getIDName(),
        ImVec2(temp[0],temp[1])
    );
    update();
    endApplyColors();
}