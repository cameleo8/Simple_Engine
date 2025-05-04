#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Scene.h"
#include "Utils.h"
#include "Debug.h"

void Entity::Update() {

	float dt = GetDeltaTime();
	float distance = fSpeed * dt;

	sf::Vector2f normalizedDirection = Direction;
	if (Utils::Normalize(normalizedDirection)) {
		sf::Vector2f translation = normalizedDirection * distance;
		mSprite.move(translation);
	}

	// Gestion du déplacement vers une cible
	if (mTarget.isSet) {
		mTarget.distance -= distance;
		if (mTarget.distance <= 0.f) {
			SetPosition(mTarget.position.x, mTarget.position.y);
			Direction = sf::Vector2f(0.f, 0.f);
			mTarget.isSet = false;
		}
	}
	if (bHitbox) {
		DrawHitbox();
		UpdateCollider();
	}
	UpdateEntity();
}
void Entity::Initialize(std::string path) {
	iLife = 0;
	iMaxLife = 0;
	iLayout = 0;
	fSpeed = 0;

	bHaveHitbox = false;
	bToDestroy = false;
	bIsAlive = false;
	bHasBeenHit = false;
	bLayoutLock = false;
	bHide = false;
	mTarget.isSet = false;

	lSprite.clear();
	tTag.clear();

	Position = { 0,0 };
	Direction = { 0,0 };
	Origine = { 0,0 };
	Scale = { 1,1 };

	mSprite.setTexture(GameManager::Get()->GetTexture(path));

	DefaultSize = { mSprite.getGlobalBounds().width,mSprite.getGlobalBounds().height};
	Size = DefaultSize;
	HitboxSize = DefaultSize;
}

void Entity::SetPosition(float pos_x, float pos_y) {
	pos_x -= (Origine.x * Size.x);
	pos_y -= (Origine.y * Size.y);

	mSprite.setPosition(pos_x, pos_y);
}
void Entity::SetDirection(float dir_x, float dir_y) {
	Direction = { dir_x,dir_y };
}

void Entity::SetOrigine(float value_x_pc, float value_y_pc) {
	Origine = { value_x_pc, value_y_pc };
}
void Entity::SetScale(float scal_x_pc, float scal_y_pc) {
	mSprite.setScale(scal_x_pc, scal_y_pc);
	Size = { mSprite.getGlobalBounds().width,mSprite.getGlobalBounds().height };
	Scale = { scal_x_pc,scal_y_pc };
}
void Entity::SetSize(float size_x_px, float size_y_px) {
	float scalx = (Scale.x * size_x_px) / mSprite.getGlobalBounds().width;
	float scaly = (Scale.y * size_y_px) / mSprite.getGlobalBounds().height;

	SetScale(scalx, scaly);
}



float Entity::GetDistanceTo(Entity* _Entity) {
	float dx = GetPosition().x - _Entity->GetPosition().x;
	float dy = GetPosition().y - _Entity->GetPosition().y;
	float distanceSquared = dx * dx + dy * dy;

	return distanceSquared;
}
float Entity::GetDistanceTo(float _x, float _y) {
	float dx = GetPosition().x - _x;
	float dy = GetPosition().y - _y;
	float distanceSquared = dx * dx + dy * dy;

	return distanceSquared;
}

bool Entity::GoToDirection(float x, float y, float speed) {
	

	fSpeed = speed;
	sf::Vector2f position = GetPosition();
	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);

	bool success = Utils::Normalize(direction);
	if (!success) {
		return false;
	}

	Direction = direction;
	return true;
}
bool Entity::GoToPosition(int x, int y, float speed)
{
	sf::Vector2f pos = GetPosition();
	sf::Vector2f toTarget = sf::Vector2f(x - pos.x, y - pos.y);

	int distance = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);

	if (distance < 1) {
		SetPosition(x, y);
		return false;
	}

	if (Utils::Normalize(toTarget)) {
		sf::Vector2f movement = toTarget * speed * GetDeltaTime();

		if (std::sqrt(movement.x * movement.x + movement.y * movement.y) > distance) {
			SetPosition(x, y);
			return false;
		}

		sf::Vector2f newPosition = pos + movement;
		SetPosition(newPosition.x, newPosition.y);
		return true;
	}

	return false;
}

void Entity::StopMove() {
	Direction = { 0,0 };
	mTarget.isSet = false;
}

void Entity::HealLife(int heal) {
	iLife += heal;
	if (iLife > iMaxLife)
		iLife = iMaxLife;
}
void Entity::DamageLife(int Damage) {
	iLife -= Damage;
	if (iLife < 0)
		iLife = 0;
}

int Entity::GetTag(int nOfTag) {
	return tTag[nOfTag];
}
bool Entity::HaveTag(int nOfTag) {
	for (auto t : tTag) {
		if (t == nOfTag)
			return true;
	}
	return false;
}
sf::Vector2f Entity::GetPosition() {
	sf::Vector2f position = mSprite.getPosition();

	position.x += (Origine.x * Size.x);
	position.y += (Origine.y * Size.y);

	return position;
}


Scene* Entity::GetScene() const {
	return GameManager::Get()->GetScene();
}

float Entity::GetDeltaTime() const {
	return GameManager::Get()->GetDeltaTime();
}

void Entity::AddAABBHitbox() {
	mHitbox = new AABBCollider();
	if (mHitbox) {
		auto* aabbCollider = dynamic_cast<AABBCollider*>(mHitbox);
		if (aabbCollider) {
			sf::Vector2f position = GetPosition();

			int halfOffsetWidth = HitboxSize.x / 2;
			int halfOffsetHeight = HitboxSize.y / 2;

			aabbCollider->xMin = position.x - halfOffsetWidth;
			aabbCollider->yMin = position.y - halfOffsetHeight;
			aabbCollider->xMax = position.x + halfOffsetWidth;
			aabbCollider->yMax = position.y + halfOffsetHeight;
		}
	}
	bHitbox = true;
}
void Entity::SolidHitbox(bool etat) {
	mHitbox->Solid = etat;
}
void Entity::SetHitboxSize(float x, float y) {
	if (auto* aabbCollider = dynamic_cast<AABBCollider*>(mHitbox)) {
		HitboxSize = { x, y };
	}
}
void Entity::UpdateCollider() {
	if (auto* aabbCollider = dynamic_cast<AABBCollider*>(mHitbox)) {
		sf::Vector2f centerPosition = GetPosition();

		aabbCollider->xMin = centerPosition.x - Origine.x * Size.x;
		aabbCollider->yMin = centerPosition.y - Origine.y * Size.y;
		aabbCollider->xMax = centerPosition.x + HitboxSize.x - Origine.x * Size.x;
		aabbCollider->yMax = centerPosition.y + HitboxSize.y - Origine.y * Size.y;

		aabbCollider->xSize = aabbCollider->xMax - aabbCollider->xMin;
		aabbCollider->ySize = aabbCollider->yMax - aabbCollider->yMin;
	}
}
void Entity::DrawHitbox() {
	if (auto* aabbCollider = dynamic_cast<AABBCollider*>(mHitbox)) {
		UpdateCollider(); 
		Debug::DrawRectangle(
			aabbCollider->xMin,
			aabbCollider->yMin,
			aabbCollider->xSize,
			aabbCollider->ySize,
			sf::Color::Red
		);
	}
}
bool Entity::IsColliding(Entity* other) const {
	if (!mHitbox || !other->mHitbox)
		return false;
	if (mHitbox->IsColliding(other->mHitbox)) {
		return mHitbox->IsColliding(other->mHitbox);
	}

	return false;
}

void Entity::SetImage(std::string path) {
	mSprite.setTexture(GameManager::Get()->GetTexture(path));
}