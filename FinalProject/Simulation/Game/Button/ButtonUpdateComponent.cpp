
#include "ButtonUpdateComponent.h"
#include "MyEngine.h"
#include "../GameManager/GameManager.h"
#include "../FishSpawner/FishSpawner.h"
#include "../../../Engine/Engine/ConcreteStrategyAABB.h"
#include "../../../Engine/Engine/ConcreteStrategyGJK.h"

#pragma once
namespace Buttons {
    using namespace glm;
    ButtonUpdateComponent::ButtonUpdateComponent(std::weak_ptr<MyEngine::GameObject> p, std::string _buttonType) {
        _gameObject = p;
    }

    void ButtonUpdateComponent::KeyEvent(SDL_Event& event) {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        glm::vec2 midScreen = glm::vec2(engine->GetScreenSize().x / 2, engine->GetScreenSize().y / 2);

        auto gm = engine->GetGameManager();

        std::cout << "key event in button update called" << std::endl;

        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_s) {
                std::cout << "S clicked to switch to AABB" << std::endl;
                gm.lock().get()->ctx->SetStrategy(std::make_unique<MyEngine::ConcreteStrategyAABB>());
            }
            if (event.key.keysym.sym == SDLK_d) {
                std::cout << "D clicked to switch to GJK" << std::endl;
                gm.lock().get()->ctx->SetStrategy(std::make_unique<MyEngine::ConcreteStrategyGJK>());
            }
            if (event.key.keysym.sym == SDLK_f) {
                std::cout << "F clicked to spawn predator" << std::endl;
                std::shared_ptr<MyEngine::GameObject> spawnerObject = gm.lock().get()->GetPredatorSpawner();
                std::weak_ptr<Fishes::FishSpawner> spawner = spawnerObject->FindComponent<Fishes::FishSpawner>();
                spawner.lock().get()->SpawnFish(midScreen);
            }
            if (event.key.keysym.sym == SDLK_g) {
                std::cout << "G clicked to spawn prey" << std::endl;
                std::shared_ptr<MyEngine::GameObject> spawnerObject = gm.lock().get()->GetPreySpawner();
                std::weak_ptr<Fishes::FishSpawner> spawner = spawnerObject->FindComponent<Fishes::FishSpawner>();
                spawner.lock().get()->SpawnFish(midScreen);
            }
        }

    }
}