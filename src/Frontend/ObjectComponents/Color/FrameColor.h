#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include <vector>

#include "Color.h"

class FrameColor : public ElementColor {
private:
    ImVec4 frameColor;
    ImVec4 frameHoveredColor;
    ImVec4 frameActiveColor;

public:
    FrameColor(
        const ImVec4& frameColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
        const ImVec4& frameHoveredColor = ImVec4(0.6f, 0.6f, 0.6f, 1.0f),
        const ImVec4& frameActiveColor = ImVec4(0.6f, 0.6f, 0.6f, 1.0f)
    );

    virtual ~FrameColor();

    ImVec4& getFrameColor();
    const ImVec4& getFrameColor() const;

    ImVec4& getFrameHoveredColor();
    const ImVec4& getFrameHoveredColor() const;

    ImVec4& getFrameActiveColor();
    const ImVec4& getFrameActiveColor() const;

    void setFrameColor(const ImVec4& color);
    void setFrameHoveredColor(const ImVec4& color);
    void setFrameActiveColor(const ImVec4& color);

    int applyColor() override;
    void endApplyColor() override;
};