#include "SceneDemo.h"

void SceneDemo::InitializeScene() {
	mousse = CreateEntity<Entity>();
	mousse->SetScale(0.1, 0.1);
	mousse->SetOrigine(0.5, 0.5);
	mousse->SetPosition(GameManager::Get()->GetWindowSize().x / 2, GameManager::Get()->GetWindowSize().y / 2);
	mousse->AddAABBHitbox();
	mousse->SetHitboxSize(20, 20);

	E1 = CreateEntity<EntityDemo>("img1");
	E1->SetPosition((GameManager::Get()->GetWindowSize().x / 3) * 2, (GameManager::Get()->GetWindowSize().y / 3)*2);
	E1->SetOrigine(0.5, 0.5);
	E1->SetScale(1, 1);
	E1->SetSpeed(2);
	E1->AddAABBHitbox();

	E2 = CreateEntity<EntityDemo>("img2");
	E2->SetOrigine(0.5, 0.5);
	E2->SetPosition(50,50);
	E2->SetScale(1, 1);
	E2->AddAABBHitbox();
}
void SceneDemo::UpdateScene(float deltaTime) {
	sf::Vector2i MPos = sf::Mouse::getPosition(*GameManager::Get()->GetWindow());
	mousse->SetPosition(MPos.x, MPos.y);

}
void SceneDemo::OnEventScene(const sf::Event& event) {

}
void SceneDemo::MoveToPos(sf::Vector2i) {
	
}
