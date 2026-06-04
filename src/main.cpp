#include "backend/Factory.h"
#include "backend/definitions.h"

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

        factory.applyCmd(simCmd);
        factory.applyMachineCmd(machineCmd); 

        simCmd = {};
        machineCmd = {};
    }
}