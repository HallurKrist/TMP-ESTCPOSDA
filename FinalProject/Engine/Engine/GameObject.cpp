#include "GameObject.h"

#include "sre/RenderPass.hpp"

#include "MyEngine.h"
#include "Component.h"
#include "Logger.h"

namespace MyEngine {
    GameObject::~GameObject() {
        //std::cout << "Destroyed object: " << _name << std::endl;
        RemoveComponents();
    }

	void GameObject::Init() {
		for (auto& component : _components)
			component->Init();
	}

	void GameObject::Update(float deltaTime) {
        timeAlive += deltaTime;
        for(int i = 0; i < _components.size(); i++) {
            _components[i]->Update(deltaTime);
        }
	}

	void GameObject::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder) {
        for(int i = 0; i < _components.size(); i++) {
            _components[i]->Render(spriteBatchBuilder);
        }
	}

	void GameObject::KeyEvent(SDL_Event& e) {
        for(int i = 0; i < _components.size(); i++) {
            _components[i]->KeyEvent(e);
        }
	}

	void GameObject::AddComponent(std::shared_ptr<Component> p_component) {
		_components.push_back(std::move(p_component));
	}

    void GameObject::RemoveComponents() {
        _components.clear();
    }

    std::vector<std::shared_ptr<Component>> GameObject::GetComponents() {
        return _components;
    }

	std::string GameObject::GetName() {
		return _name;
	}

	void GameObject::SetName(std::string p_name) {
		_name = p_name;
	}

    void GameObject::SetRadius(float r) {
        this->radius = r;
    }
}