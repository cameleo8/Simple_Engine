#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Collider.h"

class Scene;

class Entity
{
	struct PosTarget
	{
		sf::Vector2i position;
		float distance;
		bool isSet;
	};

	int iLife;
	int iMaxLife;
	int iLayout;

	float fSpeed;
	float fTimer; // a voir pour la definition selon les besouin 

	bool bHaveHitbox;
	bool bToDestroy;
	bool bIsAlive;
	bool bHasBeenHit;
	bool bLayoutLock;
	bool bHide;
	bool bHitbox;

	PosTarget mTarget;

	Collider* mHitbox;

	sf::Sprite mSprite;

	std::vector<sf::Sprite> lSprite;
	
	std::vector<int> tTag;

	sf::Vector2f Position;
	sf::Vector2f Direction;
	sf::Vector2f Scale;
	sf::Vector2f Size;
	sf::Vector2f DefaultSize;
	sf::Vector2f HitboxSize;
	sf::Vector2f Origine;

public :
	inline bool GetDestroy() { return bToDestroy; }
	inline void Destroy() { bToDestroy = true; }

	inline void SetMaxLife(int maxLife) { iMaxLife = maxLife; }
	inline int GetMaxLife() { return iMaxLife; }
	inline void SetLife(int life) { iLife = life; }
	inline int GetLife() { return iLife; }
	inline void ResetLife() { iLife = iMaxLife; }
	inline void ResetLife(int newMaxLife) { iMaxLife = newMaxLife; iLife = newMaxLife; }

	inline void SetLayout(int Layout) { iLayout = Layout; }
	inline int GetLayout() { return iLayout; }
	inline void SetLockLayout(bool etat) { bLayoutLock = etat; }
	inline bool GetLockLayout() { return bLayoutLock; }

	inline void SetSpeed(float speed) { fSpeed = speed; }
	inline float GetSpeed() { return fSpeed; }

	inline void SetHitbox(bool etat) { bHaveHitbox = etat; }
	inline bool HaveHitbox() { return bHaveHitbox; }

	inline void SetHaveHit(bool etat) { bHasBeenHit = etat; }
	inline bool HaveHit() { return bHasBeenHit; }

	inline void SetAlive(bool etat) { bIsAlive = etat; }
	inline bool GetAlive() { return bIsAlive; }

	inline void SetHide(bool etat) { bHide = etat; }
	inline bool GetHide() { return bHide; }

	inline void AddTag(int tag) { tTag.push_back(tag); }

	void SetPosition(float pos_x, float pos_y, float ratio_x = 0.5f, float ratio_y = 0.5f);
	sf::Vector2f GetPosition();
	void SetDirection(float dir_x, float dir_y);
	inline sf::Vector2f GetDirection() { return Direction; }

	void SetOrigine(float value_x_pc, float value_y_pc);
	void SetScale(float scal_x_pc, float scal_y_pc);
	void SetSize(float size_x_px, float size_y_px);
	inline sf::Vector2f GetSize() { return Size; }

	

	float GetDistanceTo(Entity* _Entity);
	float GetDistanceTo(float _x, float _y);

	void StopMove();

	void HealLife(int heal);
	void DamageLife(int Damage);

	int GetTag(int nOfTag);
	bool HaveTag(int nOfTag);

	void AddAABBHitbox();
	void SolidHitbox(bool etat);
	void SetHitboxSize(float x, float y);
	void UpdateCollider();
	void DrawHitbox();
	bool IsColliding(Entity* other) const;

	template<typename T>
	T* GetScene() const;

	Scene* GetScene() const;
	float GetDeltaTime() const;

	template<typename T>
	T* CreateEntity(float radius, const sf::Color& color);
	template<typename T>
	T* CreateEntity(std::string path);

protected:
	Entity() = default;
	~Entity() = default;

	virtual void UpdateEntity() {};
	virtual void OnCollision(Entity* collidedWith) {};
	virtual void OnInitialize() {};

	void SetImage(std::string path);

private :
	void Update();
	void Initialize(std::string path);

	friend class GameManager;
	friend Scene;
};

#include "Entity.inl"