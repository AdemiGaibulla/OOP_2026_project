#include "TextBox.h"

#include <cstring>

TextBox::TextBox(
    const Transformation2& transformation,
    const BaseColor& baseColor,
    const FrameColor& frameColor,
    const std::string& name,
    bool active
)
    : DataElement(
        transformation,
        baseColor,
        name,
        active
    )
{
    text[0] = '\0';

    pushColor(new FrameColor(frameColor));
}

TextBox::~TextBox() {}

char* TextBox::getText() {
    return text;
}

const char* TextBox::getText() const {
    return text;
}

void TextBox::setText(const char* text) {
    if (text == nullptr) {
        return;
    }

    std::strncpy(
        this->text,
        text,
        sizeof(this->text) - 1
    );

    this->text[sizeof(this->text) - 1] = '\0';
}

void TextBox::render() {
    if(!isActive()){
        return;
    }

    applyColors();
    position();
    //auto temp = getTransformation().getLocation();
    ImGui::InputText(
        getIDName(),
        text,
        sizeof(text)
    );
    update();
    endApplyColors();
}