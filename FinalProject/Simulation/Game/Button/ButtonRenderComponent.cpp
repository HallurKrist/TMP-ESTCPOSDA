
#include "ButtonRenderComponent.h"
namespace Buttons {
    using namespace std;
    ButtonRenderComponent::ButtonRenderComponent(std::weak_ptr<MyEngine::GameObject> p) {
        _gameObject = p;
    }
    void ButtonRenderComponent::Render(sre::SpriteBatch::SpriteBatchBuilder & builder) {
        //std::weak_ptr<MyEngine::GameObject> parent = GetGameObject();
        //sprite.setPosition(parent.lock().get()->position);
        //sprite.setRotation(parent.lock().get()->rotation);
        //builder.addSprite(sprite);
    }
}
