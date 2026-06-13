#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include "ObjComponents.h"

class InputState {
private:
    bool hovered;
    bool clicked;
    bool r_clicked;
    bool active;
    bool activated;
    bool deactivated;
    bool visible;
    bool focused;

public:
    InputState();

    void clear();

    bool isHovered() const;
    bool isClicked() const;
    bool isRClicked() const;
    bool isActive() const;
    bool isActivated() const;
    bool isDeactivated() const;
    bool isVisible() const;
    bool isFocused() const;

    void setHovered(bool value);
    void setClicked(bool value);
    void setRClicked(bool value);
    void setActive(bool value);
    void setActivated(bool value);
    void setDeactivated(bool value);
    void setVisible(bool value);
    void setFocused(bool value);
};

class InputManager : public Manager {
private:
    InputState state;
    bool enable;

public:
    InputManager();

    void enabled();
    void disabled();
    const bool isEnable() const;

    virtual void checkAfterItem()=0;

    InputState& getState();
    virtual const InputState& getState() const;

    void resetForNext();

    virtual ~InputManager();
};

class WindowInputManager: public InputManager{
public:
    void checkAfterItem() override;
};

class ElementInputManager: public InputManager{
public:
    void checkAfterItem() override;
};