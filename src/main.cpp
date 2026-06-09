#include "backend/Factory.h"

int main() {
    Factory factory;
    
    SimulationCmd simCmd;
    MachineCmd machineCmd;

    int running = false;

    while(running){
        factory.update();

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