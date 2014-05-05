#include "../../src/odin.cpp"
using namespace Odin;


int main (int argc, char* argv[]) {
	std::cout << "START" << std::endl;
	std::cout.precision(16);

	Init();
	
	Game game;

	Window* window = game.GetWindow();
	window->SetRect(0, 0, 960, 640);
	window->SetResizable();

	Scene* scene = new Scene();
	game.SetScene(scene);

	GameObject* cameraObject = new GameObject();
	Transform* cameraTransform = new Transform();
	cameraTransform->position.Set(0.0f, 0.0f -5.0f);
	cameraObject->AddComponent(cameraTransform);
	cameraObject->AddComponent(new Camera());
	scene->AddGameObject(cameraObject);

	GameObject* spriteObject = new GameObject();
	spriteObject->AddComponent(new Transform());
	spriteObject->AddComponent(new Sprite());
	scene->AddGameObject(spriteObject);
	
	game.SetCamera(cameraObject);
	
	game.Init();
	
	std::cout << "END" << std::endl;
	return 0;
}