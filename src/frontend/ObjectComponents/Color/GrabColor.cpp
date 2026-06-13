#include "GrabColor.h"

GrabColor::GrabColor(
    const ImVec4& grabColor,
    const ImVec4& grabActiveColor,
    const ImVec4& checkMarkColor
)
    : grabColor(grabColor),
      grabActiveColor(grabActiveColor),
      checkMarkColor(checkMarkColor)
{}

GrabColor::~GrabColor() {}

ImVec4& GrabColor::getGrabColor() {
    return grabColor;
}

const ImVec4& GrabColor::getGrabColor() const {
    return grabColor;
}

ImVec4& GrabColor::getGrabActiveColor() {
    return grabActiveColor;
}

const ImVec4& GrabColor::getGrabActiveColor() const {
    return grabActiveColor;
}

ImVec4& GrabColor::getCheckMarkColor() {
    return checkMarkColor;
}

const ImVec4& GrabColor::getCheckMarkColor() const {
    return checkMarkColor;
}

void GrabColor::setGrabColor(const ImVec4& color) {
    grabColor = color;
}

void GrabColor::setGrabActiveColor(const ImVec4& color) {
    grabActiveColor = color;
}

void GrabColor::setCheckMarkColor(const ImVec4& color) {
    checkMarkColor = color;
}

int GrabColor::applyColor() {
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, grabColor);
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, grabActiveColor);
    ImGui::PushStyleColor(ImGuiCol_CheckMark, checkMarkColor);
    return 0;
}

void GrabColor::endApplyColor() {
    ImGui::PopStyleColor(3);
}