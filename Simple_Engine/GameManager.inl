#pragma once
#include <iostream>
#include "GameManager.h"
#include "Scene.h"

template<typename T>
void GameManager::LaunchScene()
{
    static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");

    T* newScene = new T();
    newScene->SetGameManager(this);

    if (!newScene) {
        std::cerr << "Erreur : Impossible d'initialiser la nouvelle scène." << std::endl;
        return;
    }

    aScene = newScene;
    aScene->InitializeScene();
    lScenes.push_back(aScene);

    Run();
}
