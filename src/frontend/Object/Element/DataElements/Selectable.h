#pragma once

#include <string>
#include <vector>

#include "../Element.h"

#include "../../../ObjectComponents/Color/FrameColor.h"
#include "../../../ObjectComponents/Color/GrabColor.h"
#include "../../../ObjectComponents/Color/ButtonColor.h"
#include "../../../ObjectComponents/Color/HeaderColor.h"

class Selectable : public DataElement {
private:
    bool select;

public:
    Selectable(
        const Transformation2& transformation = Transformation2(),
        const BaseColor& baseColor = BaseColor(),
        const HeaderColor& headerColor = HeaderColor(),
        const std::string& name = "Selectable",
        bool active = true,
        bool select = false
    );

    virtual ~Selectable();

    bool getSelect() const;
    void setSelect(bool select);
    void render() override;
};
