#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include <vector>


#include "../ObjComponents.h"
/*
#include "BaseColor.h"
#include "ButtonColor.h"
#include "FrameColor.h"
#include "GrabColor.h"
#include "HeaderColor.h"
#include "WindowBaseColor.h"*/

class Color;

class ColorManager : public Manager {
private:
    std::vector<Color*> colors;

public:
    ColorManager();
    virtual ~ColorManager();

    void pushColor(Color* color);
    void popColor();

    virtual int applyColors();
    virtual void endApplyColors();
};

class Color {
public:
    Color();
    virtual ~Color();

    virtual int applyColor()=0;
    virtual void endApplyColor()=0;
};

class WindowColor : public Color {
public:
    WindowColor();
    virtual ~WindowColor();
};

class ElementColor : public Color {
public:
    ElementColor();
    virtual ~ElementColor();
};
