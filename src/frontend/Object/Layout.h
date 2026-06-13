#pragma once

#include <string>
#include <vector>

#include "Assets.h"
#include "../ObjectComponents/Color/WindowBaseColor.h"

class Layout : public Object {
private:
    std::vector<Object*> objs;

public:
    Layout(
        const Transformation2& transformation = Transformation2(),
        const WindowBaseColor& baseColor = WindowBaseColor(),
        const std::string& name = "Layout",
        bool active = true
    );

    void addObj(Object* obj);

    std::vector<Object*>& getObjs();
    const std::vector<Object*>& getObjs() const;

    virtual ~Layout();
};

class HorizontalLayout : public Layout {
public:
    HorizontalLayout(
        const Transformation2& transformation = Transformation2(),
        const WindowBaseColor& baseColor = WindowBaseColor(),
        const std::string& name = "HorizontalLayout",
        bool active = true
    );

    void render() override;
};

class VerticalLayout : public Layout {
public:
    VerticalLayout(
        const Transformation2& transformation = Transformation2(),
        const WindowBaseColor& baseColor = WindowBaseColor(),
        const std::string& name = "VerticalLayout",
        bool active = true
    );

    void render() override;
};