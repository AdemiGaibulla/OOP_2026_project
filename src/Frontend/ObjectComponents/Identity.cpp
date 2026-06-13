#include "Identity.h"

int Identity::nextID = 0;

Identity::Identity(
    const std::string& name
)
    : id(nextID++),
      name(name)
{}

int Identity::getID() const {
    return id;
}

std::string Identity::getName() const {
    return name;
}

void Identity::setName(
    const std::string& name
) {
    this->name = name;
}

const char* Identity::nameID() {
    cachedNameID = name +
        "##" +
        std::to_string(id);

    return cachedNameID.c_str();
}