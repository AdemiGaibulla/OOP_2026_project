#include "Selectable.h"

Selectable::Selectable(
    const Transformation2& transformation,
    const BaseColor& baseColor,
    const HeaderColor& headerColor,
    const std::string& name,
    bool active,
    bool select
)
    : DataElement(
        transformation,
        baseColor,
        name,
        active
    ),
      select(select)
{
    pushColor(new HeaderColor(headerColor));
}

Selectable::~Selectable() {}

bool Selectable::getSelect() const {
    return select;
}

void Selectable::setSelect(bool select) {
    this->select = select;
}


void Selectable::render() {
    if(!isActive()){
        return;
    }

    applyColors();
    position();
    auto temp = getTransformation().getSize();
    ImGui::Selectable(
        getIDName(),
        &select
    );
    update();
    endApplyColors();
}