#include "UI.h"

int UIBlock::nextID = 0;

UIBlock::UIBlock(Object* FisrtObj):FirstObj(FisrtObj){
    id = nextID++;
}

void UIBlock::Blockrender() {
    auto loc = FirstObj->getTransformation().getLocation();
    auto size = FirstObj->getTransformation().getSize();

    ImGui::SetNextWindowPos(ImVec2(loc[0], loc[1]));
    ImGui::SetNextWindowSize(ImVec2(size[0], size[1]));

    std::string temp1 = "##" + std::to_string(id);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    ImGui::SetNextWindowBgAlpha(0.0f);

    ImGui::Begin(
        temp1.c_str(),
        nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse
    );

    FirstObj->render();

    ImGui::End();

    ImGui::PopStyleVar(2);
}

void UI::addUIBlock(UIBlock* uiBlock){
    uiBlocks.push_back(uiBlock);
}
void UI::UIrender(){ 
    for(UIBlock* uiBlock:uiBlocks){
        uiBlock->Blockrender();
    }
}