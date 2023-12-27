//
// Created by Nicolò Vanzo on 24/11/23.
//
#include "ConcreteStrategyAABB.h"
#include "Component.h"
namespace MyEngine {
    bool ConcreteStrategyAABB::checkCollision(std::shared_ptr<MyEngine::Component> bc1,
                                              std::shared_ptr<MyEngine::Component> bc2) {
        if (bc1 == nullptr || bc2 == nullptr)
            return false;

        auto bc1BoxCollider = std::static_pointer_cast<BoxColliderComponent>(bc1);
        auto bc2BoxCollider = std::static_pointer_cast<BoxColliderComponent>(bc2);

        if (bc1BoxCollider && bc2BoxCollider) {
            auto bc1Center = bc1BoxCollider->getCenter();
            auto bc2Center = bc2BoxCollider->getCenter();
            auto bc1Width = bc1BoxCollider->getHorizontalOffset() * 2;
            auto bc2Width = bc2BoxCollider->getHorizontalOffset() * 2;
            auto bc1Height = bc1BoxCollider->getVerticalOffset() * 2;
            auto bc2Height = bc2BoxCollider->getVerticalOffset() * 2;

            return (bc1Center.x < bc2Center.x + bc2Width) &&
                   (bc1Center.x + bc1Width > bc2Center.x) &&
                   (bc1Center.y < bc2Center.y + bc2Height) &&
                   (bc1Height + bc1Center.y > bc2Center.y);
        }

        return false;
}

}