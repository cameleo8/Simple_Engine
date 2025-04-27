#include "EntityDemo.h"

void EntityDemo::UpdateEntity() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && target != nullptr) {
		target->GoToPosition(GetPosition().x, GetPosition().y, 2);
	}
	
}
void EntityDemo::OnCollision(Entity* collidedWith) {
	target = collidedWith;
	std::cout << "colide with :" << collidedWith << std::endl;
}
