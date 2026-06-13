#include "HeaderColor.h"

HeaderColor::HeaderColor(
    const ImVec4& headerColor,
    const ImVec4& headerHoveredColor,
    const ImVec4& headerActiveColor
)
    : headerColor(headerColor),
      headerHoveredColor(headerHoveredColor),
      headerActiveColor(headerActiveColor)
{}

HeaderColor::~HeaderColor() {}

ImVec4& HeaderColor::getHeaderColor() {
    return headerColor;
}

const ImVec4& HeaderColor::getHeaderColor() const {
    return headerColor;
}

ImVec4& HeaderColor::getHeaderHoveredColor() {
    return headerHoveredColor;
}

const ImVec4& HeaderColor::getHeaderHoveredColor() const {
    return headerHoveredColor;
}

ImVec4& HeaderColor::getHeaderActiveColor() {
    return headerActiveColor;
}

const ImVec4& HeaderColor::getHeaderActiveColor() const {
    return headerActiveColor;
}

void HeaderColor::setHeaderColor(const ImVec4& color) {
    headerColor = color;
}

void HeaderColor::setHeaderHoveredColor(const ImVec4& color) {
    headerHoveredColor = color;
}

void HeaderColor::setHeaderActiveColor(const ImVec4& color) {
    headerActiveColor = color;
}

int HeaderColor::applyColor() {
    ImGui::PushStyleColor(ImGuiCol_Header, headerColor);
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, headerActiveColor);
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, headerHoveredColor);
    return 0;
}

void HeaderColor::endApplyColor() {
    ImGui::PopStyleColor(3);
}