#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Scene;
class AssetManager;

class GameManager
{
private:
    std::vector<Scene*> lScenes;
    Scene* aScene = nullptr;

    AssetManager* eAssetmanageur = nullptr;
    sf::RenderWindow* Window = nullptr;

    sf::Font DefaultFont;
    float fDeltaTime = 0.0f;

    sf::Vector2i WindowSize = { 0,0 };

public:
    enum Tag {
        tCount
    };

    GameManager();
    ~GameManager();

    void Run();
    void Update();
    void Draw();
    void HandleInput();

    void SetDeltaTime(float DeltaTime) { fDeltaTime = DeltaTime; }
    float GetDeltaTime() const { return fDeltaTime; }

    void CreateWindow(unsigned int Width, unsigned int Height, const char* Title, int LimiteFPS);

    static GameManager* Get();

    template<typename T>
    void LaunchScene();

    Scene* GetScene() const { return aScene; }

    sf::Font& GetFont() { return DefaultFont; }
    sf::RenderWindow* GetWindow() { return Window; }
    sf::Vector2i GetWindowSize();

    sf::Texture& GetTexture(const std::string& path);

    void SetAssetManager(AssetManager* manager) { eAssetmanageur = manager; }

    friend class Scene;
};

#include "GameManager.inl"
