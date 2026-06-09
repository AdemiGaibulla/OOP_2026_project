#include <chrono>
#include <thread>
#include "backend/Factory.h"

int main() {
    Factory factory;
    
    SimulationCmd simCmd;
    MachineCmd machineCmd;

    int running = false;

    auto nextTick = std::chrono::steady_clock::now();

    while(running){
        nextTick += std::chrono::seconds(1);
        
        factory.update();
        
        std::this_thread::sleep_until(nextTick);

        auto machineSnaps = factory.getSnapshots();
        auto conveyorSnaps = factory.getConveyorSnapshots();
        auto stats = factory.getStats();
        auto eventLog = factory.getEventLogs();

        factory.applyCmd(simCmd);
        factory.applyMachineCmd(machineCmd); 

        simCmd = {};
        machineCmd = {};
    }
}