
#include "Component.h"
#pragma once
namespace Buttons {
    using namespace glm;
    class ButtonUpdateComponent: public MyEngine::Component {
    public:
        ButtonUpdateComponent(std::weak_ptr<MyEngine::GameObject>, std::string);
        void KeyEvent(SDL_Event& event);

    private:
    };
}

