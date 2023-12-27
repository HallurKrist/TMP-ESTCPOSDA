#include "FishColliderComponent.h"

namespace MyEngine {
    using namespace MyEngine;

    FishColliderComponent::FishColliderComponent(std::shared_ptr<MyEngine::GameObject> g) {
        _gameObject = g;

        vertexesOffset.push_back(glm::vec2(30, -30));
        vertexesOffset.push_back(glm::vec2(30, 30));
        vertexesOffset.push_back(glm::vec2(-45, 30));
        vertexesOffset.push_back(glm::vec2(-45, -30));
        vertexesOffset.push_back(glm::vec2(-60, 0));

        vertexes.push_back(glm::vec2(10, -10));
        vertexes.push_back(glm::vec2(10, 10));
        vertexes.push_back(glm::vec2(-15, 10));
        vertexes.push_back(glm::vec2(-15, -10));
        vertexes.push_back(glm::vec2(-20, 0));
    }

    void FishColliderComponent::Update(float deltaTime) {
        setCenter(_gameObject.lock()->position);
        updateVertices();
    }

    glm::vec2 FishColliderComponent::FindFurthestPoint(glm::vec2 dir) {
        glm::vec2 maxPoint = glm::vec2(0,0);
        float maxDistance = -999999;

        for(auto it = vertexes.begin(); it != vertexes.end(); ++it) {
            const auto& vertex = *it;
            /**
             * The vertex with the highest projection is considered the furthest point in the specified direction.
             */
            float distance = vertex.x * dir.x + vertex.y * dir.y;
            if(distance > maxDistance) {
                maxDistance = distance;
                maxPoint = glm::vec2(vertex.x, vertex.y);
            }
        }
        return maxPoint;
    }

    bool FishColliderComponent::getIsColliding() {
        return isColliding;
    }

    void FishColliderComponent::setIsColliding(bool _isColliding)
    {
        isColliding = _isColliding;
    }


    std::list<glm::vec2> FishColliderComponent::getVertixes() {
        return vertexes;
    }


    void FishColliderComponent::setVertexes(std::list<glm::vec2> _nodes) {
        vertexes = _nodes;
    }


    glm::vec2 FishColliderComponent::getCenter()
    {
        return center;
    }


    void FishColliderComponent::setCenter(glm::vec2 _center)
    {
        center = _center;
    }

    void FishColliderComponent::updateVertices() {
        int index = 0;
        for (auto& vertex : vertexes) {
            vertex = center + vertexesOffset[index];

            index++;
        }
        //std::cout << "end loop" << std::endl;
    }
}
