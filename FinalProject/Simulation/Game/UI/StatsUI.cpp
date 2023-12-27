//
// Created by Nicolò Vanzo on 20/12/23.
//
#include "StatsUI.h"
#include "SimulationData.h"
using namespace std;
void StatsUI::Init() {
}
void StatsUI::Update(float deltaTime) {
}
void StatsUI::Render(sre::SpriteBatch::SpriteBatchBuilder &) {
    bool open = true;

    ImGui::SetNextWindowPos(ImVec2(100,000));
    ImGui::SetNextWindowSize(ImVec2(500,200));
    ImGui::Begin("#TestLabel",&open,ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);
    ImGui::Text("Number of prey spawned: %d", MyEngine::SimulationData::GetInstance()->GetPreysSpawned());
    ImGui::Text("Press G to spawn more prey");
    ImGui::Text("Number of predators spawned: %d", MyEngine::SimulationData::GetInstance()->GetPredatorSpawned());
    ImGui::Text("Press F to spawn more predators");
    ImGui::Text("Number of collisions detected: %d", MyEngine::SimulationData::GetInstance()->GetNumberOfCollisions());
    ImGui::Text("Press S to To use the AABB collision Algorithm");
    ImGui::Text("Press D to use the GJK collision Algorithm");
    ImGui::Text("Time passed: %f", MyEngine::SimulationData::GetInstance()->GetSecondsPassed());
    //ImGui::Text("FPS: %f", MyEngine::SimulationData::GetInstance()->GetFPS());
    ImGui::End();
}
void StatsUI::KeyEvent(SDL_Event &) {
}