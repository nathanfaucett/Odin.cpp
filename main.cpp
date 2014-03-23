#include <iostream>
#include "src/odin.hpp"
using namespace Odin;


int main (int argc, char* argv[]) {
	std::cout << "START" << std::endl;
	std::cout.precision(16);

	Init();

	Scene* scene = new Scene();

	GameObject* gameObject0 = new GameObject();
	GameObject* gameObject1 = new GameObject();

	scene->AddGameObject(gameObject0);
	scene->AddGameObject(gameObject1);

	gameObject0->AddComponent(new Transform());
	gameObject1->AddComponent(new Transform());

	scene->Update();

	Transform* transform = gameObject0->GetComponent<Transform>();
	transform->position.Set(10.0f, 5.0f, 7.0f);
	transform->rotation.Rotate(10.0f, 5.0f, 7.0f);

	transform->AddChild(gameObject1->GetComponent<Transform>());

	scene->Update();

	std::cout << transform->GetDepth() << std::endl;

	std::cout << transform->matrixWorld.ToString() << std::endl;

	return 0;
}