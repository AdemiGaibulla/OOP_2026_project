#pragma once
#include <string>

enum MachineState{
    IDLE,
    WORKING,
    FIXING,
    BROKEN
};

enum ProductState{
    RAW,
    SHAPED,
    FRIED,
    GLAZED
};

enum Scenario{
    NORMAL,
    BOTTLENECK,
    BREAKDOWNS,
    OVERFLOW_SCENARIO
};

struct MachineSnap{
    int id = 0;
    std::string name = "";
    MachineState state = IDLE;
    double health = 100.0;
    int progress = 0;
    int totalTime  = 0;
    int outputCount = 0;
    int breakdowns = 0;
    int lostProducts = 0;
    std::vector<std::string> events;
};

struct ConveyorSnap{
    int id = 0;
    std::string name = "";
    int load  = 0;
    int totalCapacity = 0; 
    std::vector<std::string> events;
};

struct FactoryStats{
    int finished = 0;
    int inProgress = 0;
    int totalBreakdowns = 0;
    int totalProductLost = 0;
    int currentTick = 0;
};

struct MachineCmd{
    int  id = -1;
    bool forceBreak = false;
    bool forceRepair = false;
};

struct SimulationCmd{
    bool start = false;
    bool pause = false;
    bool reset = false;
    int speed = 1;
    Scenario scenario = NORMAL;
};