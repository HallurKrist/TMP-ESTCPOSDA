#include "BoxColliderComponent.h"
#include "Strategy.h"

#pragma once
namespace  MyEngine {
    class ConcreteStrategyAABB : public MyEngine::Strategy {
    public:
        bool checkCollision(std::shared_ptr<MyEngine::Component> bc1, std::shared_ptr<MyEngine::Component> bc2) override;
    };
}