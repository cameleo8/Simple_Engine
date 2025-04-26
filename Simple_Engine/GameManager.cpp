#include "GameManager.h"
#include "Scene.h"
#include "AssetManager.h"

GameManager::GameManager() {}

GameManager::~GameManager() {
    delete Window;
    delete aScene;
}

void GameManager::Run() {
    sf::Clock clock;
    while (Window && Window->isOpen()) {
        SetDeltaTime(clock.restart().asSeconds());

        Update();
        Draw();
    }
}

void GameManager::Update() {
    if (aScene) {
        aScene->UpdateEntity(fDeltaTime);
        aScene->UpdateScene(fDeltaTime);
    }
}

void GameManager::Draw() {
    if (!Window || !aScene) return;

    Window->clear();
    aScene->DrawScene();
    Window->display();
}

void GameManager::CreateWindow(unsigned int Width, unsigned int Height, const char* Title, int LimiteFPS) {
    Window = new sf::RenderWindow(sf::VideoMode(Width, Height), Title);
    Window->setFramerateLimit(LimiteFPS);

    WindowWidth = Width;
    WindowHeight = Height;
}

GameManager* GameManager::Get() {
    static GameManager instance;
    return &instance;
}

sf::Texture& GameManager::GetTexture(const std::string& path) {
    if (!eAssetmanageur) {
        throw std::runtime_error("AssetManager non défini !");
    }
    return eAssetmanageur->GetTexture(path);
}
