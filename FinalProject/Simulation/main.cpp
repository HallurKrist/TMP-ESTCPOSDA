//
// Created by Nicolò Vanzo on 22/09/23.
//
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"
#include "Game/Constants/Engine.h"

void ProcessEvents(SDL_Event& event);
void Update(float deltaTime);
void Render();

MyEngine::Engine engine;
glm::vec2 window_size = glm::vec2(CUSTOM_WINDOW_WIDTH, CUSTOM_WINDOW_HEIGHT);
sre::SDLRenderer renderer;
sre::Camera camera;

int main() {
    renderer.frameRender = Render;
    renderer.frameUpdate = Update;
    renderer.keyEvent = ProcessEvents;

    renderer.setWindowSize(window_size);
    renderer.init();
    camera.setWindowCoordinates();
    engine.atlas = sre::SpriteAtlas::create("data/fish_sprites.json", "data/fish_sprites.png");

    engine.Init();

    renderer.startEventLoop();
}

void ProcessEvents(SDL_Event& event) {
    engine.ProcessEvents(event);
}
void Update(float deltaTime) {
    engine.Update(deltaTime);
}
void Render() {
    engine.Render();
}