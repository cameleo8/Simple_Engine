#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class AssetManager {
public:
    AssetManager();
    explicit AssetManager(sf::RenderWindow* window);

    sf::Texture& GetTexture(const std::string& name);
    void LoadFromFile(const std::string& path);
    void LoadFromFile(const std::vector<std::string>& paths);

private:
    void updateProgressBar();
    void parseTileMap(const std::string& filepath, const std::string& filename);
    void countImagesInDirectory(const std::string& path);
    void loadImagesFromDirectory(const std::string& path);
    bool isTileMap(const std::string& filename) const;

    sf::RenderWindow* window = nullptr;

    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_set<std::string> loadedFolders;

    sf::Texture loadingBackgroundTexture;
    sf::Sprite loadingBackgroundSprite;

    sf::RectangleShape progressBarBg;
    sf::RectangleShape progressBar;

    int totalImagesToLoad = 0;
    int imagesLoaded = 0;
    float progress = 0.0f;
};
