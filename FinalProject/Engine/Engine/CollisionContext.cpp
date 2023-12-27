#include "CollisionContext.h"
#include "BoxColliderComponent.h"
#include "FishColliderComponent.h"
#include "ConcreteStrategyGJK.h"
#include "SimulationData.h"

namespace MyEngine {
    using namespace MyEngine;

    void CollisionContext::SetStrategy(std::unique_ptr<Strategy>&& strategy)
    {
        strategy_ = std::move(strategy);
    }

    void CollisionContext::CheckCollision(std::shared_ptr<Component> bc1, std::shared_ptr<Component> bc2) const {
        if(auto s = dynamic_cast<ConcreteStrategyGJK*>(strategy_.get())) {
            CheckGJKCollision(bc1, bc2);
        } else {
            CheckAABBCollision(bc1, bc2);
        }
    }

    void CollisionContext::CheckAABBCollision(std::shared_ptr<Component> bc1, std::shared_ptr<Component> bc2) const
    {
        if (strategy_)
        {
            bool result = strategy_->checkCollision(bc1, bc2);
            if (result)
            {
                //   get the colliders and fish from the given parameters
                auto collider1 = dynamic_cast<BoxColliderComponent*>(bc1.get());
                auto fish1 = collider1->_gameObject.lock()->FindComponent<Fishes::FishUpdateComponent>();
                std::string type1 = fish1.lock()->fishType;

                auto collider2 = dynamic_cast<BoxColliderComponent*>(bc2.get());
                auto fish2 = collider2->_gameObject.lock()->FindComponent<Fishes::FishUpdateComponent>();
                std::string type2 = fish2.lock()->fishType;

                //   if one of the fish is a predator (not both)
                if ((type1 == "predator" || type2 == "predator") && (type1 != type2))
                {
                    glm::vec2 pos1 = collider1->getCenter();
                    glm::vec2 pos2 = collider2->getCenter();

                    float distance = sqrt(pow((pos2.x - pos1.x), 2) + pow((pos2.y - pos1.y), 2));
                    //std::cout << "Checking distance: " << distance << std::endl;
                    if (type1 == "predator")
                    {
                        /*
                         Send distance to the predator collider that will return "Follow" or "Eat"
                         depending on what it should do.
                         if the return is "Follow" then send the follow direction to the predator fish.
                         if the return is "Eat" then delete the prey fish and collider.
                         */
                        if (fish1.lock()->checkDistance(distance)) {
                            fish1.lock()->eat();
                            fish2.lock()->destroyFish();
                            MyEngine::SimulationData::GetInstance()->IncreaseNumberOfCollisions();

                        }
                        else
                            fish1.lock()->follow(fish2.lock()->_gameObject.lock().get()->position);
                    }
                    else if (type2 == "predator") {
                        if (fish2.lock()->checkDistance(distance)) {
                            fish2.lock()->eat();
                            fish1.lock()->destroyFish();
                            MyEngine::SimulationData::GetInstance()->IncreaseNumberOfCollisions();

                        }
                        else
                            fish2.lock()->follow(fish1.lock()->_gameObject.lock().get()->position);
                    }
                }

           }
        }
        else 
        {
            std::cout << "CollisionContext-AABB: Strategy isn't set\n";
        }
    }

    void CollisionContext::CheckGJKCollision(std::shared_ptr<Component> bc1, std::shared_ptr<Component> bc2) const
    {
        if (strategy_) 
        {
            bool result = strategy_->checkCollision(bc1, bc2);
            if (result)
            {
                //std::cout << "success" << std::endl;
                //   get the colliders and fish from the given parameters
                auto collider1 = dynamic_cast<FishColliderComponent*>(bc1.get());
                auto fish1 = collider1->_gameObject.lock()->FindComponent<Fishes::FishUpdateComponent>();
                std::string type1 = fish1.lock()->fishType;

                auto collider2 = dynamic_cast<FishColliderComponent*>(bc2.get());
                auto fish2 = collider2->_gameObject.lock()->FindComponent<Fishes::FishUpdateComponent>();
                std::string type2 = fish2.lock()->fishType;

                //   if one of the fish is a predator (not both)
                if ((type1 == "predator" || type2 == "predator") && (type1 != type2))
                {
                    glm::vec2 pos1 = collider1->getCenter();
                    glm::vec2 pos2 = collider2->getCenter();

                    float distance = sqrt(pow((pos2.x - pos1.x), 2) + pow((pos2.y - pos1.y), 2));
                    if (type1 == "predator")
                    {
                        /*
                         Send distance to the predator collider that will return "Follow" or "Eat"
                         depending on what it should do.
                         if the return is "Follow" then send the follow direction to the predator fish.
                         if the return is "Eat" then delete the prey fish and collider.
                         */
                        if (fish1.lock()->checkDistance(distance)) {
                            fish1.lock()->eat();
                            fish2.lock()->destroyFish();
                            MyEngine::SimulationData::GetInstance()->IncreaseNumberOfCollisions();
                        }
                        else
                            fish1.lock()->follow(fish2.lock()->_gameObject.lock().get()->position);
                    }
                    else if (type2 == "predator") {
                        if (fish2.lock()->checkDistance(distance)) {
                            fish2.lock()->eat();
                            fish1.lock()->destroyFish();
                            MyEngine::SimulationData::GetInstance()->IncreaseNumberOfCollisions();
                        }
                        else
                            fish2.lock()->follow(fish1.lock()->_gameObject.lock().get()->position);
                    }
                }

            }
        }
        else 
        {
            std::cout << "CollisionContext-GJK: Strategy isn't set\n";
        }
    }

}
