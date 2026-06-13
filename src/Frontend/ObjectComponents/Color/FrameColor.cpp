#include "FrameColor.h"

FrameColor::FrameColor(
    const ImVec4& frameColor,
    const ImVec4& frameHoveredColor,
    const ImVec4& frameActiveColor
)
    : frameColor(frameColor),
      frameHoveredColor(frameHoveredColor),
      frameActiveColor(frameActiveColor)
{}

FrameColor::~FrameColor() {}

ImVec4& FrameColor::getFrameColor() {
    return frameColor;
}

const ImVec4& FrameColor::getFrameColor() const {
    return frameColor;
}

ImVec4& FrameColor::getFrameHoveredColor() {
    return frameHoveredColor;
}

const ImVec4& FrameColor::getFrameHoveredColor() const {
    return frameHoveredColor;
}

ImVec4& FrameColor::getFrameActiveColor() {
    return frameActiveColor;
}

const ImVec4& FrameColor::getFrameActiveColor() const {
    return frameActiveColor;
}

void FrameColor::setFrameColor(const ImVec4& color) {
    frameColor = color;
}

void FrameColor::setFrameHoveredColor(const ImVec4& color) {
    frameHoveredColor = color;
}

void FrameColor::setFrameActiveColor(const ImVec4& color) {
    frameActiveColor = color;
}

int FrameColor::applyColor() {
    ImGui::PushStyleColor(ImGuiCol_FrameBg, frameColor);
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, frameHoveredColor);
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, frameActiveColor);
    return 0;
}

void FrameColor::endApplyColor() {
    ImGui::PopStyleColor(3);
}