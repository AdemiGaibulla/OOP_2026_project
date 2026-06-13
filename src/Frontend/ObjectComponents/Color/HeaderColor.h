#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include <vector>

#include "Color.h"


class HeaderColor : public ElementColor {
private:
    ImVec4 headerColor;
    ImVec4 headerHoveredColor;
    ImVec4 headerActiveColor;

public:
    HeaderColor(
        const ImVec4& headerColor = ImVec4(0.4f, 0.4f, 0.4f, 1.0f),
        const ImVec4& headerHoveredColor = ImVec4(0.6f, 0.6f, 0.6f, 1.0f),
        const ImVec4& headerActiveColor = ImVec4(0.6f, 0.6f, 0.6f, 1.0f)
    );

    virtual ~HeaderColor();

    ImVec4& getHeaderColor();
    const ImVec4& getHeaderColor() const;

    ImVec4& getHeaderHoveredColor();
    const ImVec4& getHeaderHoveredColor() const;

    ImVec4& getHeaderActiveColor();
    const ImVec4& getHeaderActiveColor() const;

    void setHeaderColor(const ImVec4& color);
    void setHeaderHoveredColor(const ImVec4& color);
    void setHeaderActiveColor(const ImVec4& color);

    int applyColor() override;
    void endApplyColor() override;
};
