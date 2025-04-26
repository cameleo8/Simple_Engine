#pragma once 
#include "Scene.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.h"

template<typename T>
T* Scene::CreateEntity(std::string path){
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T();

	Entity* entity = newEntity;
	entity->InitialiseEntity(path);
	lEntityToAdd.push_back(newEntity);
	return newEntity;
}