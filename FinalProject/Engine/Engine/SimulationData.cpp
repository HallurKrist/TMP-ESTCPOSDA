//
// Created by Nicolò Vanzo on 17/12/23.
//
#include "MyEngine.h"
#include "SimulationData.h"
using namespace MyEngine;
SimulationData *SimulationData::GetInstance() {
    if(simulationData == nullptr) {
        simulationData = new SimulationData();
    }
    return simulationData;
}
int SimulationData::GetPredatorSpawned() {
    return predatorSpawned;
}
int SimulationData::GetPreysSpawned() {
    return preysSpawned;
}
int SimulationData::IncreasePredatorSpawned() {
    ++predatorSpawned;
    return predatorSpawned;
}
int SimulationData::IncreasePreysSpawned() {
    ++preysSpawned;
    return preysSpawned;
}
int SimulationData::IncreaseNumberOfCollisions() {
    ++numberOfCollisions;
    return numberOfCollisions;
}
int SimulationData::GetNumberOfCollisions() {
    return numberOfCollisions;
}
double SimulationData::GetSecondsPassed() {
    std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;
    double seconds_passed = duration.count();
    return seconds_passed;
}

double SimulationData::GetFPS() {
    //MyEngine.GetFrame();
    return 0;
}

