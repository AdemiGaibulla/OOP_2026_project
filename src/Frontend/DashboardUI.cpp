#include "DashboardUI.h"

#include "imgui.h"

#include <algorithm>
#include <string>

namespace {

float ratio(int value, int maxValue)
{
    if (maxValue <= 0) {
        return 0.0f;
    }

    float result = static_cast<float>(value) / static_cast<float>(maxValue);
    return std::max(0.0f, std::min(1.0f, result));
}

float ratio(double value, double maxValue)
{
    if (maxValue <= 0.0) {
        return 0.0f;
    }

    float result = static_cast<float>(value / maxValue);
    return std::max(0.0f, std::min(1.0f, result));
}

const char* machineStateName(MachineState state)
{
    switch (state) {
    case IDLE: return "IDLE";
    case WORKING: return "WORKING";
    case FIXING: return "FIXING";
    case BROKEN: return "BROKEN";
    default: return "UNKNOWN";
    }
}

ImVec4 machineStateColor(MachineState state)
{
    switch (state) {
    case IDLE: return ImVec4(0.45f, 0.55f, 0.70f, 1.0f);
    case WORKING: return ImVec4(0.20f, 0.75f, 0.35f, 1.0f);
    case FIXING: return ImVec4(0.95f, 0.70f, 0.20f, 1.0f);
    case BROKEN: return ImVec4(0.95f, 0.25f, 0.20f, 1.0f);
    default: return ImVec4(0.80f, 0.80f, 0.80f, 1.0f);
    }
}

void applyFactoryStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 4.0f;
    style.ChildRounding = 4.0f;
    style.FrameRounding = 3.0f;
    style.GrabRounding = 3.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 0.0f;
    style.WindowPadding = ImVec2(10.0f, 10.0f);
    style.FramePadding = ImVec2(8.0f, 5.0f);
    style.ItemSpacing = ImVec2(8.0f, 7.0f);

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_Text] = ImVec4(0.88f, 0.91f, 0.92f, 1.0f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.45f, 0.49f, 0.50f, 1.0f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.12f, 0.13f, 1.0f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.15f, 0.16f, 1.0f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.14f, 0.15f, 1.0f);
    colors[ImGuiCol_Border] = ImVec4(0.27f, 0.32f, 0.33f, 1.0f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.22f, 0.23f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.31f, 0.32f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.27f, 0.38f, 0.39f, 1.0f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.11f, 0.12f, 1.0f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.14f, 0.20f, 0.21f, 1.0f);
    colors[ImGuiCol_Button] = ImVec4(0.22f, 0.34f, 0.36f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.45f, 0.47f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.19f, 0.55f, 0.52f, 1.0f);
    colors[ImGuiCol_Header] = ImVec4(0.20f, 0.30f, 0.32f, 1.0f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.27f, 0.42f, 0.44f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.22f, 0.55f, 0.52f, 1.0f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.30f, 0.82f, 0.75f, 1.0f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.30f, 0.72f, 0.68f, 1.0f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.42f, 0.90f, 0.82f, 1.0f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.28f, 0.68f, 0.62f, 1.0f);
}

void renderArrow()
{
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.48f, 0.58f, 0.58f, 1.0f), ">");
    ImGui::SameLine();
}

bool renderConveyorCard(const ConveyorSnap& conveyor, bool selected)
{
    bool clicked = false;
    ImVec4 cardColor = selected
        ? ImVec4(0.18f, 0.28f, 0.30f, 1.0f)
        : ImVec4(0.15f, 0.17f, 0.17f, 1.0f);

    ImGui::PushID(1000 + conveyor.id);
    ImGui::PushStyleColor(ImGuiCol_ChildBg, cardColor);
    ImGui::BeginChild("ConveyorCard", ImVec2(150.0f, 105.0f), true);

    if (ImGui::IsWindowHovered()) {
        ImGui::GetWindowDrawList()->AddRectFilled(
            ImGui::GetWindowPos(),
            ImVec2(
                ImGui::GetWindowPos().x + ImGui::GetWindowSize().x,
                ImGui::GetWindowPos().y + ImGui::GetWindowSize().y
            ),
            ImGui::GetColorU32(ImVec4(0.22f, 0.32f, 0.33f, 0.35f)),
            ImGui::GetStyle().ChildRounding
        );
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            clicked = true;
        }
    }

    ImGui::Text("%s", conveyor.name.c_str());
    ImGui::TextColored(ImVec4(0.62f, 0.70f, 0.70f, 1.0f), "Conveyor");

    std::string loadLabel =
        std::to_string(conveyor.load) + " / " + std::to_string(conveyor.totalCapacity);
    ImGui::ProgressBar(
        ratio(conveyor.load, conveyor.totalCapacity),
        ImVec2(-1.0f, 0.0f),
        loadLabel.c_str()
    );

    ImGui::EndChild();
    ImGui::PopStyleColor();
    ImGui::PopID();

    return clicked;
}

bool renderMachineCard(const MachineSnap& machine, bool selected)
{
    bool clicked = false;
    ImVec4 cardColor = selected
        ? ImVec4(0.19f, 0.27f, 0.28f, 1.0f)
        : ImVec4(0.13f, 0.16f, 0.17f, 1.0f);

    ImGui::PushID(machine.id);
    ImGui::PushStyleColor(ImGuiCol_ChildBg, cardColor);
    ImGui::BeginChild("MachineCard", ImVec2(170.0f, 130.0f), true);

    if (ImGui::IsWindowHovered()) {
        ImGui::GetWindowDrawList()->AddRectFilled(
            ImGui::GetWindowPos(),
            ImVec2(
                ImGui::GetWindowPos().x + ImGui::GetWindowSize().x,
                ImGui::GetWindowPos().y + ImGui::GetWindowSize().y
            ),
            ImGui::GetColorU32(ImVec4(0.25f, 0.38f, 0.39f, 0.35f)),
            ImGui::GetStyle().ChildRounding
        );
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            clicked = true;
        }
    }

    ImGui::Text("%s", machine.name.c_str());
    ImGui::TextColored(machineStateColor(machine.state), "%s", machineStateName(machine.state));

    std::string progressLabel =
        std::to_string(machine.progress) + " / " + std::to_string(machine.totalTime);
    ImGui::ProgressBar(
        ratio(machine.progress, machine.totalTime),
        ImVec2(-1.0f, 0.0f),
        progressLabel.c_str()
    );

    ImGui::TextColored(ImVec4(0.58f, 0.68f, 0.68f, 1.0f), "Click to inspect");

    ImGui::EndChild();
    ImGui::PopStyleColor();
    ImGui::PopID();

    return clicked;
}

} // namespace

DashboardUI::DashboardUI()
{
    applyFactoryStyle();
}

void DashboardUI::appendLogs(const std::vector<std::string>& logs)
{
    eventLogs.insert(eventLogs.end(), logs.begin(), logs.end());
    if (eventLogs.size() > 1000) {
        eventLogs.erase(eventLogs.begin(), eventLogs.begin() + static_cast<int>(eventLogs.size() - 1000));
    }
}

void DashboardUI::render(
    const std::vector<MachineSnap>& machines,
    const std::vector<ConveyorSnap>& conveyors,
    const FactoryStats& stats,
    SimulationCmd& simCmd,
    MachineCmd& machineCmd
)
{
    resetClockRequested = false;

    // Backend is unchanged, so the UI bridge keeps command values complete every frame.
    simCmd.speed = 1;
    simCmd.scenario = uiScenario;

    renderSimulationControl(stats, simCmd);
    renderFactoryFloor(machines, conveyors);
    renderInspector(machines, conveyors, machineCmd);
    renderEventLog();
    renderStatistics(stats);
}

int DashboardUI::getSpeed() const
{
    return uiSpeed;
}

bool DashboardUI::consumeResetClockRequest()
{
    bool result = resetClockRequested;
    resetClockRequested = false;
    return result;
}

void DashboardUI::renderSimulationControl(const FactoryStats& stats, SimulationCmd& cmd)
{
    ImGui::Begin("Simulation Control");

    // The UI only writes commands. main.cpp delivers them to Factory.
    if (ImGui::Button("Start")) {
        cmd.start = true;
        uiRunning = true;
        resetClockRequested = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Pause")) {
        cmd.pause = true;
        uiRunning = false;
        resetClockRequested = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset")) {
        cmd.reset = true;
        uiRunning = false;
        eventLogs.clear();
        resetClockRequested = true;
    }

    ImGui::SliderInt("Speed", &uiSpeed, 1, 5, "%dx");

    const char* scenarioItems[] = {
        "Normal",
        "Bottleneck",
        "Random Breakdowns",
        "Overflow"
    };
    int scenarioIndex = static_cast<int>(uiScenario);
    if (ImGui::Combo("Scenario", &scenarioIndex, scenarioItems, IM_ARRAYSIZE(scenarioItems))) {
        uiScenario = static_cast<Scenario>(scenarioIndex);

        // Scenario changes start from a clean simulation and a clean visible log.
        cmd.reset = true;
        cmd.scenario = uiScenario;
        uiRunning = false;
        eventLogs.clear();
        resetClockRequested = true;
    }

    ImGui::Text("Status: %s", uiRunning ? "Running" : "Paused");
    ImGui::Text("Live Tick: %d", stats.currentTick);

    ImGui::End();
}

void DashboardUI::renderFactoryFloor(
    const std::vector<MachineSnap>& machines,
    const std::vector<ConveyorSnap>& conveyors
)
{
    ImGui::Begin("Factory Floor");

    if (selectedId < 0 && !machines.empty()) {
        selectedKind = SelectedKind::Machine;
        selectedId = machines.front().id;
    }

    ImGui::TextColored(ImVec4(0.72f, 0.80f, 0.80f, 1.0f), "Production Line");
    ImGui::Separator();

    ImGui::BeginChild(
        "FactoryPipelineScroll",
        ImVec2(0.0f, 170.0f),
        true,
        ImGuiWindowFlags_HorizontalScrollbar
    );

    ImGui::BeginGroup();
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.16f, 0.18f, 0.17f, 1.0f));
    ImGui::BeginChild("InputCard", ImVec2(120.0f, 105.0f), true);
    ImGui::Text("Input");
    ImGui::TextColored(ImVec4(0.62f, 0.70f, 0.70f, 1.0f), "Raw dough");
    ImGui::EndChild();
    ImGui::PopStyleColor();
    ImGui::EndGroup();

    const int count = std::max(machines.size(), conveyors.size());
    for (int i = 0; i < count; ++i) {
        renderArrow();

        if (i < static_cast<int>(conveyors.size())) {
            const auto& conveyor = conveyors[i];
            bool selected =
                selectedKind == SelectedKind::Conveyor &&
                selectedId == conveyor.id;

            if (renderConveyorCard(conveyor, selected)) {
                selectedKind = SelectedKind::Conveyor;
                selectedId = conveyor.id;
            }
        }

        if (i < static_cast<int>(machines.size())) {
            renderArrow();
            const auto& machine = machines[i];
            bool selected =
                selectedKind == SelectedKind::Machine &&
                selectedId == machine.id;

            if (renderMachineCard(machine, selected)) {
                selectedKind = SelectedKind::Machine;
                selectedId = machine.id;
            }
        }
    }

    renderArrow();
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.15f, 0.19f, 0.18f, 1.0f));
    ImGui::BeginChild("OutputCard", ImVec2(120.0f, 105.0f), true);
    ImGui::Text("Output");
    ImGui::TextColored(ImVec4(0.62f, 0.70f, 0.70f, 1.0f), "Finished");
    ImGui::EndChild();
    ImGui::PopStyleColor();

    ImGui::EndChild();

    ImGui::End();
}

void DashboardUI::renderInspector(
    const std::vector<MachineSnap>& machines,
    const std::vector<ConveyorSnap>& conveyors,
    MachineCmd& cmd
)
{
    ImGui::Begin("Inspector");

    if (selectedKind == SelectedKind::Conveyor) {
        const ConveyorSnap* selectedConveyor = nullptr;
        for (const auto& conveyor : conveyors) {
            if (conveyor.id == selectedId) {
                selectedConveyor = &conveyor;
                break;
            }
        }

        if (selectedConveyor == nullptr) {
            ImGui::Text("No conveyor selected");
            ImGui::End();
            return;
        }

        ImGui::Text("Name: %s", selectedConveyor->name.c_str());
        ImGui::TextColored(ImVec4(0.62f, 0.78f, 0.80f, 1.0f), "Type: Conveyor");
        ImGui::Text("Load: %d", selectedConveyor->load);
        ImGui::Text("Capacity: %d", selectedConveyor->totalCapacity);

        std::string loadLabel =
            std::to_string(selectedConveyor->load) + " / " +
            std::to_string(selectedConveyor->totalCapacity);
        ImGui::ProgressBar(
            ratio(selectedConveyor->load, selectedConveyor->totalCapacity),
            ImVec2(-1.0f, 0.0f),
            loadLabel.c_str()
        );

        ImGui::End();
        return;
    }

    const MachineSnap* selectedMachine = nullptr;
    for (const auto& machine : machines) {
        if (machine.id == selectedId) {
            selectedMachine = &machine;
            break;
        }
    }

    if (selectedMachine == nullptr) {
        ImGui::Text("No machine selected");
        ImGui::End();
        return;
    }

    ImGui::Text("Name: %s", selectedMachine->name.c_str());
    ImGui::TextColored(
        machineStateColor(selectedMachine->state),
        "State: %s",
        machineStateName(selectedMachine->state)
    );

    ImGui::Text("Health");
    ImGui::ProgressBar(ratio(selectedMachine->health, 100.0), ImVec2(-1.0f, 0.0f));

    ImGui::Text("Progress");
    std::string progressLabel =
        std::to_string(selectedMachine->progress) + " / " + std::to_string(selectedMachine->totalTime);
    ImGui::ProgressBar(
        ratio(selectedMachine->progress, selectedMachine->totalTime),
        ImVec2(-1.0f, 0.0f),
        progressLabel.c_str()
    );

    ImGui::Text("Process Time: %d ticks", selectedMachine->totalTime);
    ImGui::Text("Output Count: %d", selectedMachine->outputCount);
    ImGui::Text("Breakdowns: %d", selectedMachine->breakdowns);
    ImGui::Text("Lost Products: %d", selectedMachine->lostProducts);

    // These buttons create MachineCmd only. Machine still owns the actual state change.
    if (ImGui::Button("Force Break")) {
        cmd.id = selectedMachine->id;
        cmd.forceBreak = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Instant Repair")) {
        cmd.id = selectedMachine->id;
        cmd.forceRepair = true;
    }

    ImGui::End();
}

void DashboardUI::renderEventLog()
{
    ImGui::Begin("Event Log");

    if (ImGui::Button("Clear Log")) {
        eventLogs.clear();
    }

    ImGui::BeginChild("EventLogScroll", ImVec2(0.0f, 0.0f), true);
    for (const auto& event : eventLogs) {
        ImGui::TextWrapped("%s", event.c_str());
    }

    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
        ImGui::SetScrollHereY(1.0f);
    }
    ImGui::EndChild();

    ImGui::End();
}

void DashboardUI::renderStatistics(const FactoryStats& stats)
{
    ImGui::Begin("Statistics");

    ImGui::Text("Finished Goods: %d", stats.finished);
    ImGui::Text("WIP Count: %d", stats.inProgress);
    ImGui::Text("Total Breakdowns: %d", stats.totalBreakdowns);
    ImGui::Text("Lost Products: %d", stats.totalProductLost);
    ImGui::Text("Current Tick: %d", stats.currentTick);

    ImGui::End();
}
