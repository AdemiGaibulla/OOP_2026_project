#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include <vector>
#include <string>
#include <array>

#include "./Object/Assets.h"


class UIBlock{
private:
    int id;
    static int nextID;
    Object* FirstObj;
public:
    UIBlock(Object* FisrtObj);
    void Blockrender();
};

class UI{
private:
    std::vector<UIBlock*> uiBlocks;
public:
    void addUIBlock(UIBlock* uiBlock);
    void UIrender();
};
