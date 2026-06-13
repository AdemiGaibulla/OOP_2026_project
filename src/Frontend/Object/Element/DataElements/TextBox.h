#pragma once

#include <string>
#include <vector>


#include "../Element.h"

#include "../../../ObjectComponents/Color/FrameColor.h"
#include "../../../ObjectComponents/Color/GrabColor.h"
#include "../../../ObjectComponents/Color/ButtonColor.h"
#include "../../../ObjectComponents/Color/HeaderColor.h"

class TextBox : public DataElement {
private:
    char text[100];

public:
    TextBox(
        const Transformation2& transformation = Transformation2(),
        const BaseColor& baseColor = BaseColor(),
        const FrameColor& frameColor = FrameColor(),
        const std::string& name = "TextBox",
        bool active = true
    );

    virtual ~TextBox();

    char* getText();
    const char* getText() const;

    void setText(const char* text);//길이제한 필요

    void render() override;
};