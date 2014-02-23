#include <iostream>
#include "src/odin.h"
using namespace Odin;

int sort(const int* a, const int* b) {
	
	return *b - *a;
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

	while(1) {
		Time.Update();
		
		for (i = times; i-- > 0;) {
			scene->Update();
		}
		
		std::cout << Time.fps << std::endl;
	}
	
	return 0;
}