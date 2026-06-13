#include "Color.h"

ColorManager::ColorManager() {}

ColorManager::~ColorManager() {
    for (Color* color : colors) {
        delete color;
    }

    colors.clear();
}

void ColorManager::pushColor(Color* color) {
    colors.push_back(color);
}

void ColorManager::popColor() {
    if (colors.size() <= 1) {
        return;
    }

    delete colors.back();
    colors.pop_back();
}

int ColorManager::applyColors() {
    for(Color* color: colors){
        color->applyColor();
    }
    return 0;
}

void ColorManager::endApplyColors() {
    for(Color* color: colors){
        color->endApplyColor();
    }
}

Color::Color() {}

Color::~Color() {}



WindowColor::WindowColor() {}

WindowColor::~WindowColor() {}

ElementColor::ElementColor() {}

ElementColor::~ElementColor() {}