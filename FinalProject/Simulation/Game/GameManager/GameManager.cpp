//
// Created by Nicolò Vanzo on 27/09/23.
//
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include "Engine/MyEngine.h"
#include "../Enums/FishSpawnerPositions.h"
#include "../Button/ButtonUpdateComponent.h"
#include "../Button/ButtonRenderComponent.h"
#include "GameManager.h"
#include "ConcreteStrategyAABB.h"
#include "ConcreteStrategyGJK.h"


GameManager::~GameManager() {
    std::cout << "Destroyed game manager" << std::endl;
}

void GameManager::Init() {
    CreateFishSpawner();
    CreateButtons();
    ctx = std::make_shared<MyEngine::CollisionContext>();
    ctx->SetStrategy(std::make_unique<MyEngine::ConcreteStrategyGJK>());
}

void GameManager::Update(float deltaTime) {
    auto fishes = predatorSpawner->FindComponent<Fishes::FishSpawner>().lock()->fishes;
    auto fishes2 = preySpawner->FindComponent<Fishes::FishSpawner>().lock()->fishes;
    fishes.insert(fishes.end(), fishes2.begin(), fishes2.end());

    if (auto s = dynamic_cast<MyEngine::ConcreteStrategyAABB*>(ctx->strategy_.get())) {
        for(int i = 0; i < fishes.size(); i++) {
            auto bx1 = fishes[i]->FindComponent<MyEngine::BoxColliderComponent>();
            for(int j = i + 1; j < fishes.size() - 1; j++) {
                auto bx2 = fishes[j]->FindComponent<MyEngine::BoxColliderComponent>();
                ctx->CheckCollision(std::dynamic_pointer_cast<MyEngine::Component>(bx1.lock()), std::dynamic_pointer_cast<MyEngine::Component>(bx2.lock()));
            }
        }
    }
    else {
        for (int i = 0; i < fishes.size(); i++) {
            auto fc1 = fishes[i]->FindComponent<MyEngine::FishColliderComponent>();
            for (int j = i + 1; j < fishes.size() - 1; j++) {
                auto fc2 = fishes[j]->FindComponent<MyEngine::FishColliderComponent>();
                ctx->CheckCollision(std::dynamic_pointer_cast<MyEngine::Component>(fc1.lock()), std::dynamic_pointer_cast<MyEngine::Component>(fc2.lock()));
            }
        }
    }


}

void GameManager::CreateFishSpawner() {
    MyEngine::Engine* engine = MyEngine::Engine::GetInstance();

    predatorSpawner = engine->CreateGameObject("FishSpawner");
    auto lowerSpawnerUpdateComponent = std::make_shared<Fishes::FishSpawner>(Fishes::LOWER, predatorSpawner);
    lowerSpawnerUpdateComponent->SetFishType("predator");
    lowerSpawnerUpdateComponent->SetMaxFishCount(0);
    predatorSpawner->AddComponent(lowerSpawnerUpdateComponent);

    preySpawner = engine->CreateGameObject("FishSpawner");
    auto upperSpawnerUpdateComponent = std::make_shared<Fishes::FishSpawner>(Fishes::UPPER, preySpawner);
    upperSpawnerUpdateComponent->SetMaxFishCount(1);
    upperSpawnerUpdateComponent->SetFishType("prey");
    preySpawner->AddComponent(upperSpawnerUpdateComponent);
}

std::shared_ptr<MyEngine::GameObject> GameManager::GetPredatorSpawner() {
    return predatorSpawner;
}

std::shared_ptr<MyEngine::GameObject> GameManager::GetPreySpawner() {
    return preySpawner;
}

void GameManager::CreateButtons() {
    MyEngine::Engine* engine = MyEngine::Engine::GetInstance();

    auto gameObject = engine->CreateGameObject("button");
    std::weak_ptr<MyEngine::GameObject> obj = gameObject;
    auto ButtonRenderComponent = std::make_shared<Buttons::ButtonRenderComponent>(obj);
    auto ButtonUpdateComponent = std::make_shared<Buttons::ButtonUpdateComponent>(obj, "collider");

    ButtonRenderComponent->sprite = engine->atlas->get("tuna.png"); /// TODO: find sprite for the buttons

    gameObject->position = glm::vec2(100, 100); // TODO get correct positions

    gameObject->AddComponent(ButtonRenderComponent);
    gameObject->AddComponent(ButtonUpdateComponent);
}