#include "Component.h"
#pragma once
namespace  MyEngine  {
    class FishColliderComponent : public MyEngine::Component {

    public:
        FishColliderComponent(std::shared_ptr<MyEngine::GameObject>);
        void Update(float deltaTime) override;
        bool getIsColliding();
        void setIsColliding(bool _isColliding);

        std::list<glm::vec2> getVertixes();
        void setVertexes(std::list<glm::vec2> _nodes);

        glm::vec2 getCenter();
        void setCenter(glm::vec2 _center);
        glm::vec2 FindFurthestPoint(glm::vec2);
        void updateVertices();
    private:
        bool isColliding = false;

        std::list<glm::vec2> vertexes = std::list<glm::vec2>();
        std::vector<glm::vec2> vertexesOffset = std::vector<glm::vec2>();
        glm::vec2 center = glm::vec2(0, 0);
        glm::vec2 furthestPoint = glm::vec2(0,0);
    };
}