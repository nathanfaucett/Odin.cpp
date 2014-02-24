#include <iostream>
#include "src/odin.h"
using namespace Odin;

float sort(Vec3* a, Vec3* b) {
	
	return a->LengthSq() - b->LengthSq();
}

int main(void) {

	Init();

	Scene* scene = new Scene();
	GameObject* gameObject1 = new GameObject();
	GameObject* gameObject2 = new GameObject();
	
	gameObject1->AddChild(gameObject2);

	scene->AddGameObject(gameObject1);

	Camera* camera = new Camera();

	unsigned int times = 100000,
		i;
	while(true) {
		Time.Update();
		
		for (i = 0; i < times; i++) {
			scene->Update();
		}
		
		std::cout << Time.fps << std::endl;
	}
	
	return 0;
}