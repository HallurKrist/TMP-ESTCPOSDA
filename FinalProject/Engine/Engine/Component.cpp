#include "Component.h"

#include "Logger.h"

namespace MyEngine {
    Component::~Component() {
        //std::cout << "Destroing component" << std::endl;
        _gameObject = {};
    }
    std::weak_ptr<GameObject> Component::GetGameObject() {
		return _gameObject;
	}
}