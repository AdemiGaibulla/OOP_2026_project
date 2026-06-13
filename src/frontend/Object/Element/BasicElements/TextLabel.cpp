#include "TextLabel.h"

SimpleTextLabel::SimpleTextLabel(
    const Transformation2& transformation,
    const BaseColor& baseColor,
    const std::string& name,
    bool active
)
    : TextLabel(
        transformation,
        baseColor,
        name,
        active
    )
{}

void SimpleTextLabel::render() {
    if(!isActive()){
        return;
    }

    applyColors();
    position();
    auto temp = getTransformation().getSize();
    ImGui::Text(
        getName().c_str()
    );
    update();
    endApplyColors();
}