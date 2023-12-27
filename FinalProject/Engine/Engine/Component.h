#pragma once

#include <memory>

#include "sre/RenderPass.hpp"

#include "GameObject.h"

namespace MyEngine {
	class Engine;

	class Component {
		friend class GameObject;
	public:
        ~Component();
		virtual void Init() {};
		virtual void Update(float) {};
		virtual void Render(sre::SpriteBatch::SpriteBatchBuilder&) {};
		virtual void KeyEvent(SDL_Event&) {};
        std::weak_ptr<MyEngine::GameObject> _gameObject;
	protected:
		std::weak_ptr<GameObject> GetGameObject();
	private:
		void SetGameObject(std::weak_ptr<GameObject>);
	};
}