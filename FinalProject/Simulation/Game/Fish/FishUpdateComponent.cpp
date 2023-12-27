//
// Created by Nicolò Vanzo on 25/09/23.
//

#include "FishUpdateComponent.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include "MyEngine.h"


namespace Fishes {
    using namespace glm;
    FishUpdateComponent::FishUpdateComponent(std::weak_ptr<MyEngine::GameObject> p, std::string _fishType) {
        _gameObject = p;
        fishType = _fishType;
    }
    void FishUpdateComponent::SetDirection(int direction) {
        this->direction = direction;
    }
    void FishUpdateComponent::Update(float deltaTime) {
        std::weak_ptr<MyEngine::GameObject> parent = GetGameObject();
        if (swayTimer < 0) {
            swayTimer = (rand() % 3) + 1;
            swayDir = int (rand() % 3) - 1;
            while (swayDir == 0) {
                swayDir = int(rand() % 2) - 1;
            }
            swayCount = 0;
            parent.lock().get()->rotation += (swayDir);

        } 
        else if (swayCount < swayAmount) {
            parent.lock().get()->rotation += (swayDir);
            parent.lock().get()->position += glm::rotate(
                originDirection,
                glm::radians(parent.lock().get()->rotation)
            ) * speed;
            swayCount += abs(swayDir);

        }
        else {
            parent.lock().get()->position += glm::rotate(
                originDirection, 
                glm::radians(parent.lock().get()->rotation)
            ) * speed;
            swayTimer -= deltaTime;
        }

        
        CheckWrap();

        if (fishType == "prey") {
            energy += 1;
        }
        else {
            energy -= 0.15;
        }

        if (energy < 0) {
            destroyFish();
        }
    }

    void FishUpdateComponent::CheckWrap() {
        std::weak_ptr<MyEngine::GameObject> parent = GetGameObject();

        glm::vec2 screenSize = MyEngine::Engine::GetInstance()->GetScreenSize();

        float _x = parent.lock().get()->position.x;
        float _y = parent.lock().get()->position.y;

        if (_x < 0) {
            parent.lock().get()->position.x = screenSize.x;
        } 
        else if (screenSize.x < _x) {
            parent.lock().get()->position.x = 0;
        }
        if (_y < 0) {
            parent.lock().get()->position.y = screenSize.y;
        }
        else if (screenSize.y < _y) {
            parent.lock().get()->position.y = 0;
        }
    }

    //  Check the distance and return true if the
    //  predator is close enough to eat the prey otherwise return false
    bool FishUpdateComponent::checkDistance(float distance) {
        if (distance < 20) {
            return true;
        }
        else 
            return false;
    }

    //  Change the direction that the fish is going to the direction given
    void FishUpdateComponent::follow(glm::vec2 dir) {
        std::weak_ptr<MyEngine::GameObject> parent = GetGameObject();
        //parent.lock().get()->rotation += dir;
    }

    //  gain energy
    void FishUpdateComponent::eat() {
        energy += 100;
    }

    void FishUpdateComponent::destroyFish() {
        std::weak_ptr<MyEngine::GameObject> parent = GetGameObject();
        parent.lock().get()->~GameObject();
    }
}