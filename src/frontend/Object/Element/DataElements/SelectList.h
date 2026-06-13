#pragma once

#include <string>
#include <vector>

#include "../Element.h"

#include "../../../ObjectComponents/Color/FrameColor.h"
#include "../../../ObjectComponents/Color/GrabColor.h"
#include "../../../ObjectComponents/Color/ButtonColor.h"
#include "../../../ObjectComponents/Color/HeaderColor.h"

class SelectList : public DataElement {
private:
    int select;
    std::vector<std::string> nameList;
    std::vector<bool> valueList;
    int selectableNum;

public:
    SelectList(
        const Transformation2& transformation = Transformation2(),
        const BaseColor& baseColor = BaseColor(),
        const HeaderColor& headerColor = HeaderColor(),
        const std::string& name = "SelectList",
        bool active = true,
        int select = 0,
        int selectableNum = 1
    );

    virtual ~SelectList();

    int getSelect() const;
    void setSelect(int select);
    int* accessSelect();

    
    std::vector<std::string>& getNameList();
    const std::vector<std::string>& getNameList() const;

    std::vector<bool>& getValueList();
    const std::vector<bool>& getValueList() const;

    void addSelectable(
        const std::string& name,
        bool value = false
    );

    void addSelectable(
        int index,
        const std::string& name,
        bool value = false
    );

    void removeSelectable(int index);

    void clearSelectable();

    int getSelectableNum() const;
    void setSelectableNum(int selectableNum);

    void render() override;
};