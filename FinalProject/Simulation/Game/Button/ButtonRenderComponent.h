
#include "Component.h"

namespace  Buttons {
    class ButtonRenderComponent: public MyEngine::Component {
    public:
        ButtonRenderComponent(std::weak_ptr<MyEngine::GameObject>);
        sre::Sprite sprite;
        void Render(sre::SpriteBatch::SpriteBatchBuilder&) override;
    };
}



