#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "GameManager.h"

void Scene::DrawScene() {

	sf::RenderWindow* win = GameManager::Get()->GetWindow();
	for (auto entity : lEntity) {
		if (!entity->GetDestroy()) {
			win->draw(entity->mSprite);
		}
	}


	// dessine les ui apres pour afficher par dessue le reste 
	for (auto ui : lUI) {
		if (!ui->GetDestroy()) {
			//win->draw(ui->mSprite());
		}
	}
}



void Scene::UpdateEntity(float deltaTime) {

	std::vector<Entity*> temp; // liste tempo pour le clear 


	for (auto entity : lEntity) {
		if (!entity->GetDestroy()) {
			entity->UpdateEntity();
			temp.push_back(entity);
		}
		else
		{
			delete entity;
		}
	}
	lEntity = temp;

	for (auto ui : lUI) {
		if (!ui->GetDestroy()) {
			ui->UpdateEntity();
			temp.push_back(ui);
		}
		else {
			delete ui;
		}
	}
	lUI = temp;


}



float Scene::GetDeltaTime() {
	return GameManager::Get()->GetDeltaTime();
}



sf::Vector2i Scene::GetWindowSize() {
	return sf::Vector2i(GameManager::Get()->WindowSize.x, GameManager::Get()->WindowSize.y);
}


void Scene::UpdateList() {

	//ajout et supretion des entity
	for (Entity* entity : lEntityToDestroy) {
		delete entity;
	}
	lEntityToDestroy.clear();

	for (Entity* entity : lEntityToAdd) {
		lEntity.push_back(entity);
	}
	lEntityToAdd.clear();


	//ajout et supretion des ui
	for (Entity* ui : lUIToDestroy) {
		delete ui;
	}
	lUIToDestroy.clear();

	for (Entity* ui : lUIToAdd) {
		lUI.push_back(ui);
	}
	lUIToAdd.clear();
}