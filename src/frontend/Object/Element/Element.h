#pragma once

#include <string>
#include <vector>

#include "../Assets.h"
#include "../../ObjectComponents/Color/BaseColor.h"

class Element : public Object {
public:
    Element(
        const Transformation2& transformation = Transformation2(),
        const BaseColor& baseColor = BaseColor(),
        const std::string& name = "Element",
        bool active = true
    );

    virtual ~Element();
};

class DataElement : public Element {
public:
    DataElement(
        const Transformation2& transformation = Transformation2(),
        const BaseColor& baseColor = BaseColor(),
        const std::string& name = "DataElement",
        bool active = true
    );

    virtual ~DataElement();
};

class BasicElement : public Element {
public:
    BasicElement(
        const Transformation2& transformation = Transformation2(),
        const BaseColor& baseColor = BaseColor(),
        const std::string& name = "BasicElement",
        bool active = true
    );

    virtual ~BasicElement();
};