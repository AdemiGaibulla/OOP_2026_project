#include "BaseColor.h"

BaseColor::BaseColor(
    const ImVec4& textColor,
    const ImVec4& disabledTextColor,
    const ImVec4& borderColor,
    const ImVec4& borderShadowColor
)
    : textColor(textColor),
      disabledTextColor(disabledTextColor),
      borderColor(borderColor),
      borderShadowColor(borderShadowColor)
{}

BaseColor::~BaseColor() {}

ImVec4& BaseColor::getTextColor() {
    return textColor;
}

const ImVec4& BaseColor::getTextColor() const {
    return textColor;
}

ImVec4& BaseColor::getDisabledTextColor() {
    return disabledTextColor;
}

const ImVec4& BaseColor::getDisabledTextColor() const {
    return disabledTextColor;
}

ImVec4& BaseColor::getBorderColor() {
    return borderColor;
}

const ImVec4& BaseColor::getBorderColor() const {
    return borderColor;
}

ImVec4& BaseColor::getBorderShadowColor() {
    return borderShadowColor;
}

const ImVec4& BaseColor::getBorderShadowColor() const {
    return borderShadowColor;
}

void BaseColor::setTextColor(const ImVec4& color) {
    textColor = color;
}

void BaseColor::setDisabledTextColor(const ImVec4& color) {
    disabledTextColor = color;
}

void BaseColor::setBorderColor(const ImVec4& color) {
    borderColor = color;
}

void BaseColor::setBorderShadowColor(const ImVec4& color) {
    borderShadowColor = color;
}

int BaseColor::applyColor() {
    ImGui::PushStyleColor(ImGuiCol_Text, textColor);
    ImGui::PushStyleColor(ImGuiCol_TextDisabled, disabledTextColor);
    ImGui::PushStyleColor(ImGuiCol_Border, borderColor);
    ImGui::PushStyleColor(ImGuiCol_BorderShadow, borderShadowColor);
    return 0;
}

void BaseColor::endApplyColor() {
    ImGui::PopStyleColor(4);
}