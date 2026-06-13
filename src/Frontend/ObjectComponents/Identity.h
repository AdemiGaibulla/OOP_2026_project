#pragma once

#include <string>

#include "ObjComponents.h"

class Identity : public Parameter {
private:
    static int nextID;

    const int id;
    std::string name;

    std::string cachedNameID;

public:
    Identity(
        const std::string& name = "Object"
    );

    int getID() const;
    std::string getName() const;

    void setName(const std::string& name);

    const char* nameID();
};