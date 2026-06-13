#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include <vector>

#include "Color.h"


class ButtonColor : public ElementColor {
private:
    ImVec4 buttonColor;
    ImVec4 buttonHoveredColor;
    ImVec4 buttonActiveColor;

public:
    ButtonColor(
        const ImVec4& buttonColor = ImVec4(0.4f, 0.4f, 0.4f, 1.0f),
        const ImVec4& buttonHoveredColor = ImVec4(0.6f, 0.6f, 0.6f, 1.0f),
        const ImVec4& buttonActiveColor = ImVec4(0.6f, 0.6f, 0.6f, 1.0f)
    );

    virtual ~ButtonColor();

    ImVec4& getButtonColor();
    const ImVec4& getButtonColor() const;

    ImVec4& getButtonHoveredColor();
    const ImVec4& getButtonHoveredColor() const;

    ImVec4& getButtonActiveColor();
    const ImVec4& getButtonActiveColor() const;

    void setButtonColor(const ImVec4& color);
    void setButtonHoveredColor(const ImVec4& color);
    void setButtonActiveColor(const ImVec4& color);

    int applyColor() override;
    void endApplyColor() override;
};
