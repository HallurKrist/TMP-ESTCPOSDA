#pragma once

#include <list>
#include <memory>
#include <string>

#include "sre/SpriteBatch.hpp"

namespace MyEngine {
	class Component;

	class GameObject {
		friend class Engine;
		// public API
	public:
		glm::vec2 position;
		float rotation;
        float radius = 0;
        ~GameObject();

		void Init();
		void Update(float);
		void Render(sre::SpriteBatch::SpriteBatchBuilder&);
		void KeyEvent(SDL_Event&);
        void SetRadius(float);

		void AddChild(std::shared_ptr<GameObject>);
        void RemoveChild(std::shared_ptr<GameObject>);
        void RemoveComponents();
		void AddComponent(std::shared_ptr<Component>);

		std::string GetName();
		void SetName(std::string);
        std::vector< std::shared_ptr<Component>> GetComponents();
        float timeAlive = 0;
		// private fields

        template <class T>
        std::weak_ptr<T> FindComponent() {
            for(std::shared_ptr<Component> component : _components)
            {
                std::shared_ptr<T> candidate_ret = std::dynamic_pointer_cast<T>(component);
                if (candidate_ret != nullptr)
                    return candidate_ret;
            }
            return std::weak_ptr<T>();
        }

	private:
		std::vector<std::shared_ptr<Component>> _components = {};
		std::string _name;
	};
}