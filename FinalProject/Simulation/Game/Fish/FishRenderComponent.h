//
// Created by Nicolò Vanzo on 25/09/23.
//
#include "Component.h"

namespace  Fishes {
    class FishRenderComponent: public MyEngine::Component {
    public:
        FishRenderComponent(std::weak_ptr<MyEngine::GameObject>);
        sre::Sprite sprite;
        void Render(sre::SpriteBatch::SpriteBatchBuilder&) override;
    };
}



