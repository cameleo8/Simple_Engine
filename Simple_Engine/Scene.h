#pragma once
#include <list>
#include"SFML/Graphics.hpp"

class Entity;
class TileMap;
class CameraSys;
class Player;
class Pointer;

class Scene
{
	std::vector<Entity*> lEntity;
	std::vector<Entity*> lEntityToAdd;
	std::vector<Entity*> lEntityToDestroy;

	std::vector<Entity*> lUI;
	std::vector<Entity*> lUIToAdd;     // pas sur de l'utiliter mais au cas ou 
	std::vector<Entity*> lUIToDestroy; // pas sur de l'utiliter mais au cas ou 

	std::vector<Entity*> lLayoutEntity;
	
	Pointer* ePointer;
	CameraSys* eCamera;
	Player* ePlayer;

	std::string sSceneName;

public :
	Scene() = default;

	virtual void InitializeScene();
	virtual void UpdateScene(float deltaTime);
	virtual void OnEventScene();

	void DrawScene();
	void UpdateEntity(float deltaTime);

	float GetDeltaTime();
	sf::Vector2i GetWindowSize();

	template<typename T>
	T* CreateEntity(std::string path);
};

#include "Scene.inl"
