//
// Created by Nicolò Vanzo on 25/09/23.
//
#include "Component.h"
#pragma once
namespace Fishes {
    using namespace glm;
    class FishUpdateComponent: public MyEngine::Component {
    public:
        FishUpdateComponent(std::weak_ptr<MyEngine::GameObject>, std::string);
        void Update(float deltaTime) override;
        void SetDirection(int);

        bool checkDistance(float distance);
        void follow(glm::vec2 dir);
        void eat();

        void destroyFish();
        
        std::string fishType;
        double energy = 100;

    private:
        int direction = 1;
        int MAX_SPEED = 2;


        float swayTimer = -1;
        int swayAmount = 30;
        int swayCount = 40;
        float swayDir;

        float speed = rand() % MAX_SPEED + 2;
        vec2 originDirection = vec2(-1, 0);

        void CheckWrap();
    };
}

