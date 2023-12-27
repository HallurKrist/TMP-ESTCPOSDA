#include "Component.h"
#include "BoxColliderComponent.h"
#pragma once
namespace  MyEngine {
    class Strategy {

    public:
        virtual ~Strategy() = default;
        virtual bool checkCollision(std::shared_ptr<MyEngine::Component> bc1, std::shared_ptr<MyEngine::Component> bc2) = 0;
    private:

    };
}