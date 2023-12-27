#include "BoxColliderComponent.h"
#include "Strategy.h"
#include "FishColliderComponent.h"
#pragma once
namespace  MyEngine {
    class ConcreteStrategyGJK : public MyEngine::Strategy {
    public:
        bool checkCollision(std::shared_ptr<Component> bc1, std::shared_ptr<Component> bc2) override;
        glm::vec2 Support(std::shared_ptr<FishColliderComponent> colliderA, std::shared_ptr<FishColliderComponent> colliderB, const glm::vec2& direction);
        bool NextSimplex(std::list<glm::vec2> simplex, glm::vec2& direction);
        bool Line(std::list<glm::vec2>& simplex, glm::vec2& dir);
        bool Triangle(std::list<glm::vec2>& simplex, glm::vec2& direction);
    private:
        bool SameDirection(const glm::vec2 dir, const glm::vec2 ao);
    };
}