#include "src/odin.cpp"
using namespace Odin;


int main (int argc, char* argv[]) {
	std::cout << "START" << std::endl;
	std::cout.precision(16);

	Init();

	Game game;
	Scene* scene = new Scene();
	
	GameObject* camera = new GameObject();
	camera->AddComponent(new Transform);
	camera->AddComponent(new Camera);
	
	GameObject* sprite = new GameObject();
	camera->AddComponent(new Transform);
	camera->AddComponent(new Sprite);
	
	scene->AddGameObject(camera);
	scene->AddGameObject(sprite);

	game.SetScene(scene);
	game.SetCamera(camera);

	game.Update();
	game.Render();
	
	Clear();
	
	std::cout << "END" << std::endl;
	return 0;
}