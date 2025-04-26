#include <iostream>
#include "GameManager.h"
#include "SceneDemo.h"

int main()
{
	GameManager* instanceGM = GameManager::Get();
	instanceGM->CreateWindow(800, 600, "demo", 60);
	instanceGM->LaunchScene<SceneDemo>();
	return 0;
}
