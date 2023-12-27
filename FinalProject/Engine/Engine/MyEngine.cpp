#include "MyEngine.h"

#include <random>
#include "../../Simulation/Game/UI/StatsUI.h"
#include "sre/RenderPass.hpp"
#include "SimulationData.h"

namespace MyEngine {
    SimulationData* SimulationData::simulationData = nullptr;
    Engine* Engine::_instance = nullptr;
    Engine::~Engine() {
        std::cout << "Distruttore di MyEngine" << std::endl;
        gameObjects.clear();
    }
    Engine::Engine() {
        assert(_instance == nullptr && " Only one instance of MyEngine::Engine allowed!");
        _instance = this;
    }
    glm::vec2 Engine::GetScreenSize() const
    {
        return WIN_SIZE;
    }
    void Engine::Init() {
        // initializes random generator
        std::srand(std::time(nullptr));
        _camera.setWindowCoordinates();

        gameManager = CreateGameObject("GameManager");
        auto c = std::make_shared<GameManager>();
        gameManager->AddComponent(c);
        
        auto statsUIComponent = std::make_shared<StatsUI>();
        gameManager->AddComponent(statsUIComponent);

        for(auto g : gameObjects)
            if(g != nullptr) {
                g->Init();
            }
    }

    std::weak_ptr<GameManager> Engine::GetGameManager() {
        return gameManager.get()->FindComponent<GameManager>();
    }

    void Engine::RestartGame() {
        gameObjects.clear();
        Init();
    }

    void Engine::ProcessEvents(SDL_Event& event) {
        for(int i = 0; i <gameObjects.size(); i++) {
            gameObjects[i]->KeyEvent(event);
        }
    }

    void Engine::Update(float deltaTime) {
        ++frame;
        time += deltaTime;
        for(int i = 0; i < gameObjects.size(); i++) {
            gameObjects[i]->Update(deltaTime);
        }
    }

    void Engine::Render()
    {
        sre::RenderPass renderPass = sre::RenderPass::create()
                .withCamera(_camera)
                .withClearColor(true, { .3f, .3f, 1, 1 })
                .build();

        sre::SpriteBatch::SpriteBatchBuilder spriteBatchBuilder = sre::SpriteBatch::create();

        for(int i = 0; i < gameObjects.size(); i++) {
            gameObjects[i]->Render(spriteBatchBuilder);
        }

        auto spriteBatch = spriteBatchBuilder.build();
        renderPass.draw(spriteBatch);
    }

    void Engine::RemoveObject(std::shared_ptr<MyEngine::GameObject> p) {
        for(int i = 0; i < gameObjects.size(); i++) {
            if(gameObjects[i] == p) {
                gameObjects.erase(gameObjects.begin() + i);
            }
        }
    }

    std::shared_ptr<GameObject> Engine::CreateGameObject(std::string name) {
        auto ret = std::make_shared<GameObject>();
        ret->SetName(name);
        gameObjects.push_back(ret);
        return ret;
    }
}