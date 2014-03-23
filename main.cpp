#include <iostream>
#include "src/odin.hpp"
using namespace Odin;


int main (int argc, char* argv[]) {
	std::cout << "START" << std::endl;
	std::cout.precision(16);

	Init();

	Scene* scene = new Scene();

	GameObject* gameObject0 = new GameObject();
	Transform* transform0 = new Transform();

	GameObject* gameObject1 = new GameObject();
	Transform* transform1 = new Transform();

	scene->AddGameObject(gameObject0);
	scene->AddGameObject(gameObject1);

	gameObject0->AddComponent(transform0);
	gameObject1->AddComponent(transform1);

	scene->Update();

	Transform* transform = gameObject0->GetComponent<Transform>();
	transform->position.Set(10.0f, 5.0f, 7.0f);
	transform->rotation.Rotate(10.0f, 5.0f, 7.0f);

	transform->AddChild(transform1);

	scene->Update();

	std::cout << transform->GetDepth() << std::endl;
	std::cout << transform1->GetDepth() << std::endl;

	std::cout << transform1->matrixWorld.ToString() << std::endl;

	return 0;
}