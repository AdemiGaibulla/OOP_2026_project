#include "SelectList.h"

SelectList::SelectList(
    const Transformation2& transformation,
    const BaseColor& baseColor,
    const HeaderColor& headerColor,
    const std::string& name,
    bool active,
    int select,
    int selectableNum
)
    : DataElement(
        transformation,
        baseColor,
        name,
        active
    ),
      select(select),
      selectableNum(selectableNum)
{
    pushColor(new HeaderColor(headerColor));
}

SelectList::~SelectList() {}

int SelectList::getSelect() const {
    return select;
}

void SelectList::setSelect(int select) {
    this->select = select;
}

int* SelectList::accessSelect(){
    return &select;
}


std::vector<std::string>& SelectList::getNameList() {
    return nameList;
}

const std::vector<std::string>& SelectList::getNameList() const {
    return nameList;
}

std::vector<bool>& SelectList::getValueList() {
    return valueList;
}

const std::vector<bool>& SelectList::getValueList() const {
    return valueList;
}

void SelectList::addSelectable(
    const std::string& name,
    bool value
){
    nameList.push_back(name);
    valueList.push_back(value);
}

void SelectList::addSelectable(
    int index,
    const std::string& name,
    bool value
){
    if(index < 0){
        index = 0;
    }

    if(index > static_cast<int>(nameList.size())){
        index = static_cast<int>(nameList.size());
    }

    nameList.insert(
        nameList.begin() + index,
        name
    );

    valueList.insert(
        valueList.begin() + index,
        value
    );
}

void SelectList::removeSelectable(int index){
    if(index < 0 ||
       index >= static_cast<int>(nameList.size())){
        return;
    }

    nameList.erase(
        nameList.begin() + index
    );

    valueList.erase(
        valueList.begin() + index
    );
}

void SelectList::clearSelectable(){
    nameList.clear();
    valueList.clear();
}

int SelectList::getSelectableNum() const {
    return selectableNum;
}

void SelectList::setSelectableNum(int selectableNum) {
    this->selectableNum = selectableNum;
}

void SelectList::render() {
    // TODO: Implement select list rendering
}
