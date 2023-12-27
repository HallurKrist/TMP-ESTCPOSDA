#include "Component.h"
#include "../../Simulation/Game/Fish/FishUpdateComponent.h"

#pragma once
namespace  MyEngine  {
    class BoxColliderComponent : public MyEngine::Component {

    public:
        BoxColliderComponent(std::shared_ptr<MyEngine::GameObject>);
        void Update(float deltaTime) override;

        bool getIsColliding();
        void setIsColliding(bool _isColliding);

        int getVerticalOffset();
        void setVerticalOffset(int _verticalOffset);

        int getHorizontalOffset();
        void setHorizontalOffset(int _horizontalOffset);

        glm::vec2 getCenter();
        void setCenter(glm::vec2 _center);

        void Collision(std::string _type);

    private:
        bool isColliding = false;
        int verticalOffset = 30;
        int horizontalOffset = 30;
        glm::vec2 center = glm::vec2(0, 1);
    };
}