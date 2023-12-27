#include "Component.h"
#include "Strategy.h"
#include "BoxColliderComponent.h"
#include "FishColliderComponent.h"
#pragma once
namespace  MyEngine {
    class CollisionContext {

    public:
        explicit CollisionContext(std::unique_ptr<Strategy>&& strategy = {}) : strategy_(std::move(strategy)) {}
        void CheckCollision(std::shared_ptr<Component> bc1, std::shared_ptr<Component> bc2) const;
        void SetStrategy(std::unique_ptr<Strategy>&& strategy);

        void CheckAABBCollision(std::shared_ptr<Component> bc1, std::shared_ptr<Component> bc2) const;
        void CheckGJKCollision(std::shared_ptr<Component> bc1, std::shared_ptr<Component> bc2) const;

        std::unique_ptr<Strategy> strategy_;
    private:
    };
}