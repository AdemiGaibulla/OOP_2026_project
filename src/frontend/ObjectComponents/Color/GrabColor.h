#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include <vector>

#include "Color.h"



class GrabColor : public ElementColor {
private:
    ImVec4 grabColor;
    ImVec4 grabActiveColor;
    ImVec4 checkMarkColor;

public:
    GrabColor(
        const ImVec4& grabColor = ImVec4(0.4f, 0.4f, 0.4f, 1.4f),
        const ImVec4& grabActiveColor = ImVec4(0.6f, 0.6f, 0.6f, 1.0f),
        const ImVec4& checkMarkColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f)
    );

    virtual ~GrabColor();

    ImVec4& getGrabColor();
    const ImVec4& getGrabColor() const;

    ImVec4& getGrabActiveColor();
    const ImVec4& getGrabActiveColor() const;

    ImVec4& getCheckMarkColor();
    const ImVec4& getCheckMarkColor() const;

    void setGrabColor(const ImVec4& color);
    void setGrabActiveColor(const ImVec4& color);
    void setCheckMarkColor(const ImVec4& color);

    int applyColor() override;
    void endApplyColor() override;
};
