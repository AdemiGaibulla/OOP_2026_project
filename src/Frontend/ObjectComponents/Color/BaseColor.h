#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include <vector>

#include "Color.h"


class BaseColor : public ElementColor {
private:
    ImVec4 textColor;
    ImVec4 disabledTextColor;
    ImVec4 borderColor;
    ImVec4 borderShadowColor;

public:
    BaseColor(
        const ImVec4& textColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f),
        const ImVec4& disabledTextColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f),
        const ImVec4& borderColor = ImVec4(0.4f, 0.4f, 0.4f, 1.0f),
        const ImVec4& borderShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.0f)
    );

    virtual ~BaseColor();

    ImVec4& getTextColor();
    const ImVec4& getTextColor() const;

    ImVec4& getDisabledTextColor();
    const ImVec4& getDisabledTextColor() const;

    ImVec4& getBorderColor();
    const ImVec4& getBorderColor() const;

    ImVec4& getBorderShadowColor();
    const ImVec4& getBorderShadowColor() const;

    void setTextColor(const ImVec4& color);
    void setDisabledTextColor(const ImVec4& color);
    void setBorderColor(const ImVec4& color);
    void setBorderShadowColor(const ImVec4& color);

    int applyColor() override;
    void endApplyColor() override;
};
