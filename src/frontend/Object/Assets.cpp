#include "Assets.h"

Object::Object(
    const Identity& identity,
    const Transformation2& transformation,
    ColorManager* colorManager,
    InputManager* inputManager,
    bool active
)
    : identity(identity),
      transformation(transformation),
      colorManager(colorManager),
      inputManager(inputManager),
      active(active)
{}

Object::~Object() {
    delete colorManager;
    delete inputManager;
}

void Object::update() {
    if(inputManager->isEnable()){
        inputManager->checkAfterItem();
    }
}

const int Object::getID() const {
    return identity.getID();
}

std::string Object::getName() const {
    return identity.getName();
}

const char* Object::getIDName() {
    return identity.nameID();
}

bool Object::isActive() const {
    return active;
}

const Transformation2& Object::getTransformation() const {
    return transformation;
}

const InputState& Object::getInputState() const {
    return inputManager->getState();
}

void Object::position(){
    if(getTransformation().getTransformEnable()){
        auto temp = getTransformation().getLocation();
        ImGui::SetCursorPos(ImVec2(temp[0],temp[1]));
    }
}

void Object::setName(const std::string& name) {
    identity.setName(name);
}

void Object::setActive(bool active) {
    this->active = active;
}

void Object::setTransformation(
    const Transformation2& transformation
) {
    this->transformation = transformation;
}

void Object::setLocation(
    const std::array<int, 2>& location
) {
    transformation.setLocation(location);
}

void Object::setSize(
    const std::array<int, 2>& size
) {
    transformation.setSize(size);
}

void Object::moveBy(int dx, int dy) {
    std::array<int, 2> location = transformation.getLocation();

    location[0] += dx;
    location[1] += dy;

    transformation.setLocation(location);
}

void Object::enableInput() {
    inputManager->enabled();
}

void Object::disableInput() {
    inputManager->disabled();
}

void Object::resetInputForNext() {
    inputManager->resetForNext();
}

void Object::pushColor(Color* color) {
    colorManager->pushColor(color);
}

void Object::popColor() {
    colorManager->popColor();
}

int Object::applyColors() {
    return colorManager->applyColors();
}

void Object::endApplyColors() {
    colorManager->endApplyColors();
}