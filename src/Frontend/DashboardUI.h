#pragma once

#include <string>
#include <vector>

#include "../Backend/definitions.h"

class DashboardUI {
private:
    enum class SelectedKind {
        Machine,
        Conveyor
    };

    SelectedKind selectedKind = SelectedKind::Machine;
    int selectedId = 1;
    int uiSpeed = 1;
    Scenario uiScenario = NORMAL;
    bool uiRunning = false;
    bool resetClockRequested = false;
    std::vector<std::string> eventLogs;

    void renderSimulationControl(const FactoryStats& stats, SimulationCmd& cmd);
    void renderFactoryFloor(
        const std::vector<MachineSnap>& machines,
        const std::vector<ConveyorSnap>& conveyors
    );
    void renderInspector(
        const std::vector<MachineSnap>& machines,
        const std::vector<ConveyorSnap>& conveyors,
        MachineCmd& cmd
    );
    void renderEventLog();
    void renderStatistics(const FactoryStats& stats);

public:
    DashboardUI();

    void appendLogs(const std::vector<std::string>& logs);

    void render(
        const std::vector<MachineSnap>& machines,
        const std::vector<ConveyorSnap>& conveyors,
        const FactoryStats& stats,
        SimulationCmd& simCmd,
        MachineCmd& machineCmd
    );

    int getSpeed() const;
    bool consumeResetClockRequest();
};
