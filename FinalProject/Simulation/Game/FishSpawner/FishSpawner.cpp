//
// Created by Nicolò Vanzo on 25/09/23.
//
#include "FishSpawner.h"
#include "../Fish/FishRenderComponent.h"
#include "MyEngine.h"
#include "SimulationData.h"
#include "../Enums/FishSpawnerPositions.h"
#include <cstdlib>
#include "../Constants/Engine.h"
#include <BoxColliderComponent.h>
#include <FishColliderComponent.h>
#include "CollisionContext.h"
#include "ConcreteStrategyAABB.h"

namespace Fishes {
    using namespace glm;
    using namespace std;
    FishSpawner::FishSpawner(int direction, std::weak_ptr<MyEngine::GameObject> parent):
    direction(direction){
        _gameObject = parent;
        ctx = std::make_shared<MyEngine::CollisionContext>();
        ctx->SetStrategy(std::make_unique<MyEngine::ConcreteStrategyAABB>());
    }

    void FishSpawner::Update(float deltaTime) {
        timeCounter -= deltaTime;
        if((timeCounter < 0) && (fishCount < maxFishCount) && !initialSpawnDone) {
            ++fishCount;
            
            SpawnFish(glm::vec2(0, 0));
            timeCounter = TIME_TO_SPAWN_FISH;
        }
        if (fishCount == maxFishCount && !initialSpawnDone) {
            initialSpawnDone = true;
        }

        if (initialSpawnDone) {
            for (std::shared_ptr<MyEngine::GameObject>fish : fishes) {
                if (fish != nullptr) {
                    auto fishUpdate = fish->FindComponent<Fishes::FishUpdateComponent>();
                    if (!fishUpdate.expired()) {
                        auto fishHealth = fishUpdate.lock()->energy;
                        if (fishHealth >= 500) {
                            fishUpdate.lock()->energy = 100;
                            ++fishCount;
                            SpawnFish(fish->position);
                            break;
                        }
                    }
                }
            }
            ResetFishList();
        }
    }

    void FishSpawner::SpawnFish(glm::vec2 position) {
        MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
        auto gameObject = engine->CreateGameObject("fish");
        std::weak_ptr<MyEngine::GameObject> obj = gameObject;
        auto fishRenderComponent = std::make_shared<Fishes::FishRenderComponent>(obj);
        auto fishUpdateComponent = std::make_shared<Fishes::FishUpdateComponent>(obj, fish);
        auto fishBoxColliderComponent = std::make_shared<MyEngine::BoxColliderComponent>(obj.lock());
        auto fishFishColliderComponent = std::make_shared<MyEngine::FishColliderComponent>(obj.lock());

        if (fish == "predator") {
            fishRenderComponent->sprite = engine->atlas->get("tuna.png");
            fishRenderComponent->sprite.setScale(glm::vec2(0.15, 0.15));
            MyEngine::SimulationData::GetInstance()->IncreasePredatorSpawned();
        }
        else {
            fishRenderComponent->sprite = engine->atlas->get("clown-fish.png");
            fishRenderComponent->sprite.setScale(glm::vec2(0.1, 0.1));
            MyEngine::SimulationData::GetInstance()->IncreasePreysSpawned();
        }
        gameObject->rotation = rand() % 360 - 180;

        float randX = 0;
        float randY = 0;

        /////////////////////////////////////// CHANGE WHEN FISHUPDATECOMPONENT HAS BEEN CAHNGED//////////////////////////////////
        if (position == glm::vec2(0,0)) {
            if (direction == LOWER) {
                //spawn only along the lower part of the screen
                randX = rand() % (int)CUSTOM_WINDOW_WIDTH;
                randY = 10;
                fishUpdateComponent->SetDirection(LOWER);
            }
            else if (direction == UPPER) {
                //spawn only along the upper part of the screen
                randY = CUSTOM_WINDOW_HEIGHT + 100;
                randX = rand() % (int)CUSTOM_WINDOW_WIDTH;
                fishUpdateComponent->SetDirection(UPPER);
            }
            gameObject->position = glm::vec2(randX, randY);

        }
        else {
            gameObject->position = position;
        }

        gameObject->AddComponent(fishRenderComponent);
        gameObject->AddComponent(fishUpdateComponent);
        gameObject->AddComponent(fishBoxColliderComponent);
        gameObject->AddComponent(fishFishColliderComponent);

        fishes.push_back(gameObject);

    }

    void FishSpawner::SetMaxFishCount(int _maxFishCount) {
        maxFishCount = _maxFishCount;
    }

    void FishSpawner::SetFishType(std::string _type) {
        fish = _type;
    }

    void FishSpawner::ResetFishList() {
        auto newFishes = std::vector< std::shared_ptr<MyEngine::GameObject>>();
        for (std::shared_ptr<MyEngine::GameObject>fish : fishes) {
            auto updateComponent = fish.get()->FindComponent<FishUpdateComponent>();
            if (fish != nullptr && !updateComponent.expired()) {
                newFishes.push_back(fish);
            }
        }
        fishes = newFishes;
    }

}