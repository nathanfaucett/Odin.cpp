#include <iostream>
#include "src/odin.h"
using namespace Odin;

int sort(const int* a, const int* b) {
	
	return *b - *a;
}

int main(void) {

	Init();

	Time.update();

	Vec2 a(10.f, 5.f);
	Vec2 b(10.f, 5.f);
	
	Vec2 c = a + b;
	
	Scene* scene = new Scene();
	GameObject* gameObject1 = new GameObject();
	GameObject* gameObject2 = new GameObject();
	
	gameObject1->AddChild(gameObject2);
	
	scene->AddGameObject(gameObject1);
	
	gameObject1->DetachChildren();
	
	Array<int*> array(0);
	int n1 = 124,
		n2 = 23,
		n3 = 245,
		n4 = 51;
	
	array.Push(&n1);
	array.Push(&n2);
	array.Push(&n3);
	array.Push(&n4);
	
	array.Sort(sort);

	for (unsigned int i = 0, il = array.Length(); i < il; i++) {
		std::cout << *array[i] << std::endl;
	}
	
	return 0;
}