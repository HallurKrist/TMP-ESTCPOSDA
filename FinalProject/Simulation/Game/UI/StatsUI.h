//
// Created by Nicolò Vanzo on 20/12/23.
//

#include "sre/SDLRenderer.hpp"
#include "Component.h"
#pragma once

class StatsUI: public MyEngine::Component {
public:
    void Init() override;
    void Update(float) override;
    void Render(sre::SpriteBatch::SpriteBatchBuilder&) override;
    void KeyEvent(SDL_Event&) override;
};
