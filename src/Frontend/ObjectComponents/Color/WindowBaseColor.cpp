#include "WindowBaseColor.h"

WindowBaseColor::WindowBaseColor(
    const ImVec4& normalColor,
    const ImVec4& backgroundColor,
    const ImVec4& borderColor,
    const ImVec4& disabledTextColor,
    const ImVec4& scrollBackground,
    const ImVec4& scrollGrab,
    const ImVec4& scrollHovered,
    const ImVec4& scrollActive
)
    : normalColor(normalColor),
      backgroundColor(backgroundColor),
      borderColor(borderColor),
      disabledTextColor(disabledTextColor),
      scrollBackground(scrollBackground),
      scrollGrab(scrollGrab),
      scrollHovered(scrollHovered),
      scrollActive(scrollActive)
{}

WindowBaseColor::~WindowBaseColor() {}

ImVec4& WindowBaseColor::getNormalColor() {
    return normalColor;
}

const ImVec4& WindowBaseColor::getNormalColor() const {
    return normalColor;
}

ImVec4& WindowBaseColor::getBackgroundColor() {
    return backgroundColor;
}

const ImVec4& WindowBaseColor::getBackgroundColor() const {
    return backgroundColor;
}

ImVec4& WindowBaseColor::getBorderColor() {
    return borderColor;
}

const ImVec4& WindowBaseColor::getBorderColor() const {
    return borderColor;
}

ImVec4& WindowBaseColor::getDisabledTextColor() {
    return disabledTextColor;
}

const ImVec4& WindowBaseColor::getDisabledTextColor() const {
    return disabledTextColor;
}

ImVec4& WindowBaseColor::getScrollBackground() {
    return scrollBackground;
}

const ImVec4& WindowBaseColor::getScrollBackground() const {
    return scrollBackground;
}

ImVec4& WindowBaseColor::getScrollGrab() {
    return scrollGrab;
}

const ImVec4& WindowBaseColor::getScrollGrab() const {
    return scrollGrab;
}

ImVec4& WindowBaseColor::getScrollHovered() {
    return scrollHovered;
}

const ImVec4& WindowBaseColor::getScrollHovered() const {
    return scrollHovered;
}

ImVec4& WindowBaseColor::getScrollActive() {
    return scrollActive;
}

const ImVec4& WindowBaseColor::getScrollActive() const {
    return scrollActive;
}

void WindowBaseColor::setNormalColor(const ImVec4& color) {
    normalColor = color;
}

void WindowBaseColor::setBackgroundColor(const ImVec4& color) {
    backgroundColor = color;
}

void WindowBaseColor::setBorderColor(const ImVec4& color) {
    borderColor = color;
}

void WindowBaseColor::setDisabledTextColor(const ImVec4& color) {
    disabledTextColor = color;
}

void WindowBaseColor::setScrollBackground(const ImVec4& color) {
    scrollBackground = color;
}

void WindowBaseColor::setScrollGrab(const ImVec4& color) {
    scrollGrab = color;
}

void WindowBaseColor::setScrollHovered(const ImVec4& color) {
    scrollHovered = color;
}

void WindowBaseColor::setScrollActive(const ImVec4& color) {
    scrollActive = color;
}

int WindowBaseColor::applyColor() {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, backgroundColor);
    ImGui::PushStyleColor(ImGuiCol_Border, borderColor);
    ImGui::PushStyleColor(ImGuiCol_Text, normalColor);
    ImGui::PushStyleColor(ImGuiCol_TextDisabled, disabledTextColor);
    ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, scrollBackground);
    ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, scrollGrab);
    ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabActive, scrollActive);
    ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabHovered, scrollHovered);
    return 0;
}

void WindowBaseColor::endApplyColor() {
    ImGui::PopStyleColor(8);
}