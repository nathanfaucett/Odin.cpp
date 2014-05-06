#include "../../src/odin.cpp"
using namespace Odin;


int main (int argc, char* argv[]) {
	std::cout << "START" << std::endl;

	Init();
	
	Game* game = new Game();

	Assets.Add(new Texture("face", "../assets/images/face.png"));
	Assets.Load();
	
	Window* window = game->GetWindow();
	window->SetRect(0, 0, 960, 640);
	window->SetResizable();

	Scene* scene = new Scene();
	game->SetScene(scene);

	GameObject* cameraObject = new GameObject();
	Transform* cameraTransform = new Transform();
	cameraTransform->position.Set(0.0f, 0.0f -5.0f);
	cameraObject->AddComponent(cameraTransform);
	cameraObject->AddComponent(new Camera());
	scene->AddGameObject(cameraObject);

	GameObject* spriteObject = new GameObject();
	spriteObject->AddComponent(new Transform());
	Sprite* sprite = new Sprite();
	sprite->texture = Assets.Get<Texture>("face");
	spriteObject->AddComponent(sprite);
	scene->AddGameObject(spriteObject);
	
	game->SetCamera(cameraObject);
	
	game->Init();
	
	delete game;
	Clear();
	
	std::cout << "END" << std::endl;
	return 0;
}