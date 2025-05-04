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

	std::vector<Entity*> tempE; // liste tempo pour le clear 


	for (auto entity : lEntity) {
		if (!entity->GetDestroy()) {
			entity->Update();
			tempE.push_back(entity);
		}
		else
		{
			delete entity;
		}
	}
	lEntity = tempE;

	std::vector<Entity*> tempU;

	for (auto ui : lUI) {
		if (!ui->GetDestroy()) {
			ui->Update();
			tempU.push_back(ui);
		}
		else {
			delete ui;
		}
	}
	lUI = tempU;

	for (auto it1 = lEntity.begin(); it1 != lEntity.end(); ++it1) {
		for (auto it2 = std::next(it1); it2 != lEntity.end(); ++it2) {
			//if ((*it1)->isHide || (*it2)->isHide)
				//continue;

			if ((*it1)->IsColliding(*it2)) {
				(*it1)->OnCollision(*it2);
				(*it2)->OnCollision(*it1);
			}
		}
	}


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