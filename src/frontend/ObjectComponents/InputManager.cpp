#include "InputManager.h"

InputState::InputState()
    : hovered(false),
      clicked(false),
      r_clicked(false),
      active(false),
      activated(false),
      deactivated(false),
      visible(false),
      focused(false)
{}

void InputState::clear() {
    hovered = false;
    clicked = false;
    r_clicked = false;
    active = false;
    activated = false;
    deactivated = false;
    visible = false;
    focused = false;
}

bool InputState::isHovered() const {
    return hovered;
}

bool InputState::isClicked() const {
    return clicked;
}

bool InputState::isRClicked() const {
    return r_clicked;
}

bool InputState::isActive() const {
    return active;
}

bool InputState::isActivated() const {
    return activated;
}

bool InputState::isDeactivated() const {
    return deactivated;
}

bool InputState::isVisible() const {
    return visible;
}

bool InputState::isFocused() const {
    return focused;
}

void InputState::setHovered(bool value) {
    hovered = value;
}

void InputState::setClicked(bool value) {
    clicked = value;
}

void InputState::setRClicked(bool value) {
    r_clicked = value;
}

void InputState::setActive(bool value) {
    active = value;
}

void InputState::setActivated(bool value) {
    activated = value;
}

void InputState::setDeactivated(bool value) {
    deactivated = value;
}

void InputState::setVisible(bool value) {
    visible = value;
}

void InputState::setFocused(bool value) {
    focused = value;
}


InputManager::InputManager()
    : enable(false)
{}

void InputManager::enabled() {
    enable = true;
}

void InputManager::disabled() {
    enable = false;
}

const bool InputManager::isEnable() const {
    return enable;
}

InputState& InputManager::getState() {
    return state;
}

const InputState& InputManager::getState() const {
    return state;
}

void InputManager::resetForNext() {
    enable=false;
    getState().clear();
}

InputManager::~InputManager() {}


void WindowInputManager::checkAfterItem() {
    getState().setActivated(false);
    getState().setActive(ImGui::IsWindowHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left));
    getState().setClicked(ImGui::IsWindowHovered() &&  ImGui::IsMouseClicked(ImGuiMouseButton_Left));
    getState().setDeactivated(false);
    getState().setFocused(ImGui::IsWindowFocused());
    getState().setHovered(ImGui::IsWindowHovered());
    getState().setRClicked(ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right));
    getState().setVisible(false);
}

void ElementInputManager::checkAfterItem() {
    getState().setActivated(ImGui::IsItemActivated());
    getState().setActive(ImGui::IsItemActive());
    getState().setClicked(ImGui::IsItemClicked());
    getState().setDeactivated(ImGui::IsItemDeactivated());
    getState().setFocused(ImGui::IsItemFocused());
    getState().setHovered(ImGui::IsItemHovered());
    getState().setRClicked(ImGui::IsItemClicked(ImGuiMouseButton_Right));
    getState().setVisible(ImGui::IsItemVisible());
}