#pragma once

#include <string>
#include <array>

#include "../ObjectComponents/Identity.h"
#include "../ObjectComponents/Transformation.h"
#include "../ObjectComponents/Color/Color.h"
#include "../ObjectComponents/InputManager.h"

class Asset {};

class Object : public Asset {
private:
    Identity identity;
    Transformation2 transformation;
    ColorManager* colorManager;
    InputManager* inputManager;
    bool active;

public:
    Object(
        const Identity& identity,
        const Transformation2& transformation,
        ColorManager* colorManager,
        InputManager* inputManager,
        bool active = true
    );

    virtual ~Object();

    void update();
    virtual void render() = 0;

    const int getID() const;
    std::string getName() const;
    const char* getIDName();

    bool isActive() const;

    const Transformation2& getTransformation() const;
    const InputState& getInputState() const;

    void position();

    void setName(const std::string& name);
    void setActive(bool active);

    void setTransformation(const Transformation2& transformation);
    void setLocation(const std::array<int, 2>& location);
    void setSize(const std::array<int, 2>& size);
    void moveBy(int dx, int dy);

    void enableInput();
    void disableInput();
    void resetInputForNext();

    void pushColor(Color* color);
    void popColor();

    int applyColors();
    void endApplyColors();
};