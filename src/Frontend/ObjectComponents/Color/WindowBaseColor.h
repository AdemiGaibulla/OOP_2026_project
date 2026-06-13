#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include <vector>

#include "Color.h"

class WindowBaseColor : public WindowColor {
private:
    ImVec4 normalColor;
    ImVec4 backgroundColor;
    ImVec4 borderColor;
    ImVec4 disabledTextColor;

    ImVec4 scrollBackground;
    ImVec4 scrollGrab;
    ImVec4 scrollHovered;
    ImVec4 scrollActive;

public:
    WindowBaseColor(
        const ImVec4& normalColor = ImVec4(0.4f, 0.4f, 0.4f, 1.0f),
        const ImVec4& backgroundColor = ImVec4(0.4f, 0.4f, 0.4f, 1.0f),
        const ImVec4& borderColor = ImVec4(0.4f, 0.4f, 0.4f, 1.0f),
        const ImVec4& disabledTextColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f),
        const ImVec4& scrollBackground = ImVec4(0.5f, 0.5f, 0.5f, 1.0f),
        const ImVec4& scrollGrab = ImVec4(0.3f, 0.3f, 0.3f, 1.0f),
        const ImVec4& scrollHovered = ImVec4(0.2f, 0.2f, 0.2f, 1.0f),
        const ImVec4& scrollActive = ImVec4(0.2f, 0.2f, 0.2f, 1.0f)
    );

    virtual ~WindowBaseColor();

    ImVec4& getNormalColor();
    const ImVec4& getNormalColor() const;

    ImVec4& getBackgroundColor();
    const ImVec4& getBackgroundColor() const;

    ImVec4& getBorderColor();
    const ImVec4& getBorderColor() const;

    ImVec4& getDisabledTextColor();
    const ImVec4& getDisabledTextColor() const;

    ImVec4& getScrollBackground();
    const ImVec4& getScrollBackground() const;

    ImVec4& getScrollGrab();
    const ImVec4& getScrollGrab() const;

    ImVec4& getScrollHovered();
    const ImVec4& getScrollHovered() const;

    ImVec4& getScrollActive();
    const ImVec4& getScrollActive() const;

    void setNormalColor(const ImVec4& color);
    void setBackgroundColor(const ImVec4& color);
    void setBorderColor(const ImVec4& color);
    void setDisabledTextColor(const ImVec4& color);

    void setScrollBackground(const ImVec4& color);
    void setScrollGrab(const ImVec4& color);
    void setScrollHovered(const ImVec4& color);
    void setScrollActive(const ImVec4& color);

    int applyColor() override;
    void endApplyColor() override;
};