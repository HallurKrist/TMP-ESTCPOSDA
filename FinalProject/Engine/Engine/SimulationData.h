//
// Created by Nicolò Vanzo on 17/12/23.
//


#pragma once
#include <iostream>
#include <chrono>
#include <thread>

namespace MyEngine {
    class SimulationData {
    protected:
        SimulationData(){}
        static SimulationData* simulationData;
        int preysSpawned = 0;
        int predatorSpawned = 0;
        int numberOfCollisions = 0;
        std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    public:
        SimulationData(SimulationData &) = delete;
        void operator=(const SimulationData&) = delete;
        static SimulationData *GetInstance();
        int GetPreysSpawned();
        int GetPredatorSpawned();
        int GetNumberOfCollisions();
        int IncreasePreysSpawned();
        int IncreasePredatorSpawned();
        int IncreaseNumberOfCollisions();
        double GetSecondsPassed();
        double GetFPS();

    };
}

