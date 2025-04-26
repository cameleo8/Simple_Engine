#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <filesystem>
#include <memory>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

AssetManager::AssetManager() = default;

AssetManager::AssetManager(sf::RenderWindow* win) : window(win) {
    LoadFromFile("../../../img/");
}

sf::Texture& AssetManager::GetTexture(const std::string& name) {
    auto it = textures.find(name);
    if (it != textures.end())
        return it->second;
    throw std::runtime_error("Texture introuvable : " + name);
}

void AssetManager::LoadFromFile(const std::string& path) {
    if (!loadedFolders.contains(path))
        LoadFromFile(std::vector<std::string>{ path });
}

void AssetManager::LoadFromFile(const std::vector<std::string>& paths) {
    totalImagesToLoad = imagesLoaded = 0;
    progress = 0.0f;

    if (!loadingBackgroundTexture.loadFromFile("../../../img/LoadingScreen.png")) {
        std::cerr << "Erreur : Impossible de charger l'image de fond.\n";
    }

    loadingBackgroundSprite.setTexture(loadingBackgroundTexture);
    loadingBackgroundSprite.setScale(
        static_cast<float>(window->getSize().x) / loadingBackgroundTexture.getSize().x,
        static_cast<float>(window->getSize().y) / loadingBackgroundTexture.getSize().y
    );

    progressBarBg.setSize({ window->getSize().x / 2.f, window->getSize().y / 15.f });
    progressBarBg.setFillColor(sf::Color(30, 30, 30));
    progressBarBg.setPosition(
        (window->getSize().x - progressBarBg.getSize().x) / 2.f,
        (window->getSize().y * 5.f / 6.f) - (progressBarBg.getSize().y / 2.f)
    );

    progressBar.setFillColor(sf::Color::Blue);
    progressBar.setPosition(progressBarBg.getPosition());

    for (const auto& path : paths) {
        if (loadedFolders.contains(path)) continue;

        countImagesInDirectory(path);
        loadImagesFromDirectory(path);

        loadedFolders.insert(path);
    }
}

void AssetManager::countImagesInDirectory(const std::string& path) {
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (!entry.is_regular_file() || entry.path().extension() != ".png") continue;

        std::string name = entry.path().stem().string();
        if (isTileMap(name)) {
            std::stringstream ss(name);
            std::string _;
            int cols, rows;
            std::getline(ss, _, '_'); std::getline(ss, _, '_');
            cols = std::stoi(_); std::getline(ss, _, '_');
            rows = std::stoi(_);
            totalImagesToLoad += cols * rows;
        }
        else {
            ++totalImagesToLoad;
        }
    }

    textures.reserve(totalImagesToLoad);
}

void AssetManager::loadImagesFromDirectory(const std::string& path) {
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (!entry.is_regular_file() || entry.path().extension() != ".png") continue;

        const std::string filepath = entry.path().string();
        const std::string filename = entry.path().stem().string();

        if (isTileMap(filename)) {
            parseTileMap(filepath, filename);
        }
        else {
            sf::Texture tex;
            if (tex.loadFromFile(filepath)) {
                textures.emplace(filename, std::move(tex));
            }
            else {
                std::cerr << "Erreur : Impossible de charger l'image " << filepath << std::endl;
            }

            ++imagesLoaded;
            if (imagesLoaded % 10 == 0 || imagesLoaded == totalImagesToLoad)
                updateProgressBar();
        }
    }
}

bool AssetManager::isTileMap(const std::string& filename) const {
    return filename.starts_with("CUT_");
}

void AssetManager::parseTileMap(const std::string& filepath, const std::string& filename) {
    std::stringstream ss(filename);
    std::string prefix, colStr, rowStr, baseName;
    std::getline(ss, prefix, '_');
    std::getline(ss, colStr, '_');
    std::getline(ss, rowStr, '_');
    std::getline(ss, baseName, '_');

    int cols = std::stoi(colStr);
    int rows = std::stoi(rowStr);

    sf::Texture fullTex;
    if (!fullTex.loadFromFile(filepath)) {
        std::cerr << "Erreur : Impossible de charger la tilemap " << filepath << std::endl;
        return;
    }

    sf::Image fullImage = fullTex.copyToImage();
    const int tileW = fullTex.getSize().x / cols;
    const int tileH = fullTex.getSize().y / rows;

    for (int y = 0, idx = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x, ++idx) {
            sf::Texture tileTex;
            tileTex.loadFromImage(fullImage, sf::IntRect(x * tileW, y * tileH, tileW, tileH));

            std::ostringstream nameStream;
            nameStream << baseName << "_" << std::setw(4) << std::setfill('0') << idx;

            textures.emplace(nameStream.str(), std::move(tileTex));

            ++imagesLoaded;
            if (imagesLoaded % 10 == 0 || imagesLoaded == totalImagesToLoad)
                updateProgressBar();
        }
    }
}

void AssetManager::updateProgressBar() {
    progress = static_cast<float>(imagesLoaded) / totalImagesToLoad;
    progressBar.setSize({ (window->getSize().x / 2.f) * progress, progressBarBg.getSize().y });

    window->clear();
    window->draw(loadingBackgroundSprite);
    window->draw(progressBarBg);
    window->draw(progressBar);
    window->display();
}
