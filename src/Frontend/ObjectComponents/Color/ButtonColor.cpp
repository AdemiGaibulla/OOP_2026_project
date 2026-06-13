#include "ButtonColor.h"

ButtonColor::ButtonColor(
    const ImVec4& buttonColor,
    const ImVec4& buttonHoveredColor,
    const ImVec4& buttonActiveColor
)
    : buttonColor(buttonColor),
      buttonHoveredColor(buttonHoveredColor),
      buttonActiveColor(buttonActiveColor)
{}

ButtonColor::~ButtonColor() {}

ImVec4& ButtonColor::getButtonColor() {
    return buttonColor;
}

const ImVec4& ButtonColor::getButtonColor() const {
    return buttonColor;
}

ImVec4& ButtonColor::getButtonHoveredColor() {
    return buttonHoveredColor;
}

const ImVec4& ButtonColor::getButtonHoveredColor() const {
    return buttonHoveredColor;
}

ImVec4& ButtonColor::getButtonActiveColor() {
    return buttonActiveColor;
}

const ImVec4& ButtonColor::getButtonActiveColor() const {
    return buttonActiveColor;
}

void ButtonColor::setButtonColor(const ImVec4& color) {
    buttonColor = color;
}

void ButtonColor::setButtonHoveredColor(const ImVec4& color) {
    buttonHoveredColor = color;
}

void ButtonColor::setButtonActiveColor(const ImVec4& color) {
    buttonActiveColor = color;
}

int ButtonColor::applyColor() {
    ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, buttonHoveredColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, buttonActiveColor);
    return 3;
}

void ButtonColor::endApplyColor() {
    ImGui::PopStyleColor(3);
}