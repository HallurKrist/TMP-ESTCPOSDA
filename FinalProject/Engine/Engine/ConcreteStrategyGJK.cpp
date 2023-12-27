//
// Created by Nicolò Vanzo on 12/12/23.
//
#include "ConcreteStrategyGJK.h"
namespace MyEngine {
    bool ConcreteStrategyGJK::checkCollision(std::shared_ptr<Component> bc1, std::shared_ptr<Component> bc2) {
        if (bc1 == nullptr || bc2 == nullptr)
            return false;

        auto bc1Collider = std::static_pointer_cast<FishColliderComponent>(bc1);
        auto bc2Collider = std::static_pointer_cast<FishColliderComponent>(bc2);

        if(bc1Collider && bc2Collider) {
            glm::vec2 initialDir = glm::vec2(1,1);
            glm::vec2 support = ConcreteStrategyGJK::Support(bc1Collider, bc2Collider, initialDir);
            std::list<glm::vec2> simplex;
            simplex.push_back(support);
            glm::vec2 direction = -support;
            while(true) {
                direction = glm::normalize(direction);
                support = ConcreteStrategyGJK::Support(bc1Collider, bc2Collider, direction);

                /**
                 * No collision detected
                 */
                if(glm::dot(support, direction) <= 0) {
                    return false;
                }

                if(ConcreteStrategyGJK::NextSimplex(simplex, direction)) {
                    return true;
                }

                simplex.push_back(support);

            }
        }

        return false;
    }
    glm::vec2 ConcreteStrategyGJK::Support(std::shared_ptr<FishColliderComponent> colliderA,std::shared_ptr<FishColliderComponent> colliderB, const glm::vec2& direction) {
        glm::vec2 f1 = colliderA->FindFurthestPoint(direction);
        glm::vec2 f2 = colliderB->FindFurthestPoint(-direction);
        glm::vec2 support = f1 - f2;
        return support;
    }
    bool ConcreteStrategyGJK::NextSimplex(std::list<glm::vec2> simplex, glm::vec2& direction) {
        switch (simplex.size()) {
            case 2: return Line(simplex, direction);
            case 3: return Triangle(simplex, direction);
            case 4: return true;
        }
        return false;
    }
    bool ConcreteStrategyGJK::SameDirection(const glm::vec2 dir, const glm::vec2 ao) {
        return glm::dot(dir, ao) > 0;
    }

    bool ConcreteStrategyGJK::Line(std::list<glm::vec2>& simplex, glm::vec2& dir) {
        glm::vec2 a = *simplex.begin();
        glm::vec2 b = *std::next(simplex.begin());

        glm::vec2 ab = b - a;
        glm::vec2 ao = -a;

        if(SameDirection(ab, ao)) {
            dir = glm::vec2(ab.y, ab.x); // no need to cross product since we are in 2D
        } else {
            simplex.clear();
            simplex.push_front(a);
            dir = ao;
        }
        return true;
    }

    bool ConcreteStrategyGJK::Triangle(std::list<glm::vec2>& simplex, glm::vec2& direction) {
        glm::vec2 a = *simplex.begin();
        glm::vec2 b = *std::next(simplex.begin());
        glm::vec2 c = *std::next(std::next(simplex.begin()));

        glm::vec2 ab = b - a;
        glm::vec2 ac = c - a;
        glm::vec2 ao = -a;

        glm::vec2 abc = glm::vec2(ab.x * ac.y - ab.y * ac.x, ab.y * ac.x - ab.x * ac.y);

        if (SameDirection(glm::cross(glm::vec3(abc.x, abc.y, 0), glm::vec3(ac.x, ac.y, 0)), ao)) {
            if (SameDirection(ac, ao)) {
                simplex.clear();
                simplex.push_front(a);
                simplex.push_front(c);
                direction = glm::cross(glm::cross(glm::vec3(ac.x, ac.y, 0), glm::vec3(ao.x, ao.y, 0)), glm::vec3(ac.x, ac.y, 0));
            } else {
                simplex.clear();
                simplex.push_front(a);
                simplex.push_front(b);
                Line(simplex, direction);
            }
        } else {
            if (SameDirection(glm::cross(glm::vec3(ab.x, ab.y, 0), glm::vec3(abc.x, abc.y, 0)), ao)) {
                simplex.clear();
                simplex.push_front(a);
                simplex.push_front(b);
                Line(simplex, direction);
            } else {
                if (SameDirection(abc, ao)) {
                    direction = abc;
                } else {
                    simplex.clear();
                    simplex.push_front(a);
                    simplex.push_front(c);
                    simplex.push_front(b);
                    direction = -abc;
                }
                // Continue checking the next simplex in case the triangle case needs further iterations
                return false;
            }
        }
        return true;
    }

}