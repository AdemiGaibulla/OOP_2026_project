#include "Layout.h"

Layout::Layout(
    const Transformation2& transformation,
    const WindowBaseColor& baseColor,
    const std::string& name,
    bool active
)
    : Object(
        Identity(name),
        transformation,
        new ColorManager(),
        new WindowInputManager(),
        active
    )
{
    pushColor(new WindowBaseColor(baseColor));
}

Layout::~Layout() {
    for (Object* obj : objs) {
        delete obj;
    }

    objs.clear();
}

void Layout::addObj(Object* obj) {
    objs.push_back(obj);
}

std::vector<Object*>& Layout::getObjs() {
    return objs;
}

const std::vector<Object*>& Layout::getObjs() const {
    return objs;
}

HorizontalLayout::HorizontalLayout(
    const Transformation2& transformation,
    const WindowBaseColor& baseColor,
    const std::string& name,
    bool active
)
    : Layout(
        transformation,
        baseColor,
        name,
        active
    )
{}

void HorizontalLayout::render() {
    if(!isActive()){
        return;
    }

    applyColors();
    position();

    auto temp = getTransformation().getSize();
    ImGui::BeginChild(
        getIDName(),
        ImVec2(temp[0],temp[1]),
        true
    );

    for(Object* obj:getObjs()){
        obj->render();
        ImGui::SameLine();
    }

    ImGui::EndChild();
    update();
    endApplyColors();
}

VerticalLayout::VerticalLayout(
    const Transformation2& transformation,
    const WindowBaseColor& baseColor,
    const std::string& name,
    bool active
)
    : Layout(
        transformation,
        baseColor,
        name,
        active
    )
{}

void VerticalLayout::render() {
    if(!isActive()){
        return;
    }

    applyColors();
    position();

    auto temp = getTransformation().getSize();
    ImGui::BeginChild(
        getIDName(),
        ImVec2(temp[0],temp[1]),
        true
    );

    for(Object* obj:getObjs()){
        obj->render();
        //ImGui::SameLine();
    }

    ImGui::EndChild();
    update();
    endApplyColors();
}