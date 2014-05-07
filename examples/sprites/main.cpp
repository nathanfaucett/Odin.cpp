#include "../../src/odin.cpp"
using namespace Odin;


class Mover : public Component {
	public:
		inline Mover(void) {}
		inline Mover(const Mover&) = default;
		inline Mover(Mover&&) = default;
		inline ~Mover(void) {}

		inline Mover* Clone(void) {
			return &((new Mover())->Copy(*this));
		}
		inline Mover& Copy(const Mover& other) {
			return *this;
		}
		
		inline void Update(void) {
			Transform* transform = GetComponent<Transform>();
			if (transform == NULL) return;
			
			transform->position.x = Mathf.Sin(Time.time);
		}
		inline void Clear(void) {
			
		}
		
		inline Mover& operator=(const Mover&)& = default;
		inline Mover& operator=(Mover&&)& = default;
};


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
	cameraTransform->position.Set(0.0f, 0.0f, 0.0f);
	cameraObject->AddComponent(cameraTransform);
	cameraObject->AddComponent(new Camera());
	scene->AddGameObject(cameraObject);

	for (uint32 i = 0, il = 100; i < il; i++) {
		GameObject* spriteObject = new GameObject();
		Transform* spriteTransform = new Transform();
		spriteTransform->position.Set(Mathf.RandFloat(-1.0f, 1.0f), Mathf.RandFloat(-1.0f, 1.0f), Mathf.RandFloat(-5.0f, -2.0f));
		spriteObject->AddComponent(spriteTransform);
		Sprite* sprite = new Sprite();
		sprite->texture = Assets.Get<Texture>("face");
		spriteObject->AddComponent(sprite);
		spriteObject->AddComponent(new Mover());
		scene->AddGameObject(spriteObject);
	}
	
	game->SetCamera(cameraObject);
	
	game->Init();
	
	delete game;
	Clear();
	
	std::cout << "END" << std::endl;
	return 0;
}