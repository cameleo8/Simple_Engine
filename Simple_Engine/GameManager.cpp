#include "GameManager.h"
#include "Scene.h"
#include "AssetManager.h"
#include "Debug.h"

GameManager::GameManager() {}

GameManager::~GameManager() {
    delete Window;
    delete aScene;
}

void GameManager::Run() {
    sf::Clock clock;
    while (Window && Window->isOpen()) {
        SetDeltaTime(clock.restart().asSeconds());

        HandleInput();

        Update();
        Draw();
    }
}

void GameManager::Update() {
    Debug::Get()->ClearListe();

    if (aScene) {
        aScene->UpdateScene(fDeltaTime);
        aScene->UpdateEntity(fDeltaTime);
    }


    aScene->UpdateList();

}

void GameManager::Draw() {
    if (!Window || !aScene) return;

    Window->clear();
    aScene->DrawScene();

    if (DrawHitBox) {
        Debug::Get()->DrawText(10, 10, std::to_string(GetDeltaTime()), sf::Color::Red);
        Debug::Get()->Draw(Window);
    }

    Window->display();

}

void GameManager::CreateWindow(unsigned int Width, unsigned int Height, const char* Title, int LimiteFPS) {
    Window = new sf::RenderWindow(sf::VideoMode(Width, Height), Title);
    Window->setFramerateLimit(LimiteFPS);

    int x = Width;
    int y = Height;

    WindowSize = { x, y };

    eAssetmanageur = new AssetManager(Window);
    bool fontLoaded = DefaultFont.loadFromFile("../res/font/DefaultFont.ttf");
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


sf::Vector2i GameManager::GetWindowSize() {
    return WindowSize;
}
void GameManager::HandleInput() {
    sf::Event event;
    while (Window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            Window->close();
            return;
        }

        if (aScene)
            aScene->OnEventScene(event);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
        if (!KeyPressed) {
            KeyPressed = true;
            DrawHitBox = !DrawHitBox;
        }
    }
    else {
        KeyPressed = false;
    }
}