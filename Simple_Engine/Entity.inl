#pragma once 
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include "GameManager.h"

template<typename T>
T* Entity::GetScene() const
{
	T* pScene = dynamic_cast<T*>(GetScene());

	_ASSERT(pScene != nullptr);

	return pScene;
}

template<typename T>
T* Entity::CreateEntity(float radius, const sf::Color& color)
{
	return GetScene()->CreateEntity<T>(radius, color);
}

template<typename T>
T* Entity::CreateEntity(std::string path)
{
	return GetScene()->CreateEntity<T>(path);
}