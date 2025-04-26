#pragma once
#include "Scene.h"
#include "EntityDemo.h"

class SceneDemo : public Scene
{
	EntityDemo* E1;
	EntityDemo* E2;

	EntityDemo* Selected;

	Entity* mousse;
	
	void InitializeScene() override;
	void UpdateScene(float deltaTime) override;
	void OnEventScene(const sf::Event& event) override;
public :
	void MoveToPos(sf::Vector2i);

};

