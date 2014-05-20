#include "../../src/odin.cpp"
using namespace Odin;

class Mover : public Component {
	public:
		Vec2f velocity;
		
		inline Mover(void) : Component() {}
		inline Mover(const Mover&) = default;
		inline Mover(Mover&&) = default;
		inline ~Mover(void) {}

		inline Mover* Clone(void) {
			return &((new Mover())->Copy(*this));
		}
		inline Mover& Copy(const Mover& other) {
			Component::Copy(static_cast<Component>(other));
			return *this;
		}
		
		inline void Update(void) {
			Transform* transform = GetComponent<Transform>();
			if (transform == NULL) return;
			
			float32 horizontal = Input.Axis("Horizontal");
			float32 vertical = Input.Axis("Vertical");
			
			velocity.x += 5.0f * horizontal;
			velocity.y += 5.0f * vertical;
			velocity *= Time.delta;
			
			transform->position += velocity;
			transform->rotation.RotateZ(Mathf.PI * 0.5f * Time.delta);
		}
		
		inline Mover& operator=(const Mover&)& = default;
		inline Mover& operator=(Mover&&)& = default;
};
class Rotator : public Component {
	public:
		Vec2f velocity;
		
		inline Rotator(void) : Component() {}
		inline Rotator(const Rotator&) = default;
		inline Rotator(Rotator&&) = default;
		inline ~Rotator(void) {}

		inline Rotator* Clone(void) {
			return &((new Rotator())->Copy(*this));
		}
		inline Rotator& Copy(const Rotator& other) {
			Component::Copy(static_cast<Component>(other));
			return *this;
		}
		
		inline void Update(void) {
			Transform* transform = GetComponent<Transform>();
			if (transform == NULL) return;
			float32 dt = Mathf.PI * 0.5f * Time.delta;
			transform->rotation.Rotate(dt, dt, dt);
		}
		
		inline Rotator& operator=(const Rotator&)& = default;
		inline Rotator& operator=(Rotator&&)& = default;
};

Game* game = new Game();

void loop() {
	game->Update();
	game->Render();
}

int main (int argc, char* argv[]) {
	std::cout << "START" << std::endl;
	
	Init();
	
	Texture* face = new Texture("face", "../assets/images/face.png");
	Assets.Add(face);
	
	Mesh* plane = Mesh::Plane("plane", 1.0f, 1.0f, 1, 1);
	Assets.Add(plane);
	
	Mesh* cube = Mesh::Cube("cube", 1.0f, 1.0f, 1.0f, 1, 1, 1);
	Assets.Add(cube);
	
	
	Material* material = new Material("material");
	material->vertex = GLSL(110,
		in vec3 position;
		in vec3 normal;
		in vec2 uv;
		
		uniform mat4 projection;
		uniform mat4 modelView;
		uniform mat3 normalMatrix;
		
		varying vec2 vUv;
		
		void main(void) {
			gl_Position = projection * modelView * vec4(position, 1.0f);
			vUv = uv;
		}
	);
	material->fragment = GLSL(110,
		out vec4 fragColor;
		
		uniform vec3 diffuseColor;
		uniform sampler2D texture;
		
		varying vec2 vUv;
		
		void main(void) {
			fragColor = texture2D(texture, vUv);
			fragColor.xyz *= diffuseColor;
		}
	);
	material->SetSide(Side::FrontAndBack);
	material->uniforms["texture"] = new MaterialUniformSampler2D(Assets.Get<Texture>("face"));
	static_cast<MaterialUniform3f*>(material->uniforms["diffuseColor"])->value.Set(1.0f, 1.0f, 1.0f);
	
	Assets.Add(material);
	
	Assets.Load();

	Scene* scene = new Scene();

	GameObject* cameraObject = new GameObject();
	Transform* cameraTransform = new Transform();
	cameraTransform->position.Set(0.0f, -5.0f, 5.0f);
	cameraObject->AddComponent(cameraTransform);
	cameraObject->AddComponent(new Camera());
	cameraObject->AddComponent(new OrbitControl());
	scene->AddGameObject(cameraObject);
	
	for (uint32 i = 0, il = 10; i < il; i++) {
		GameObject* spriteObject = new GameObject();
		Transform* spriteTransform = new Transform();
		spriteTransform->position.Set(Mathf.RandFloat(-1.0f, 1.0f), Mathf.RandFloat(-1.0f, 1.0f), Mathf.RandFloat(-5.0f, -2.0f));
		spriteObject->AddComponent(spriteTransform);
		Sprite* sprite = new Sprite();
		sprite->material = Assets.Get<Material>("material");
		spriteObject->AddComponent(sprite);
		spriteObject->AddComponent(new Mover());
		scene->AddGameObject(spriteObject);
	}
	
	for (uint32 i = 0, il = 10; i < il; i++) {
		GameObject* meshObject = new GameObject();
		Transform* meshTransform = new Transform();
		meshTransform->position.Set(Mathf.RandFloat(-5.0f, 5.0f), Mathf.RandFloat(-5.0f, 5.0f), Mathf.RandFloat(-5.0f, 5.0f));
		meshObject->AddComponent(meshTransform);
		MeshFilter* meshFilter = new MeshFilter();
		meshFilter->mesh = Mathf.Random() >= 0.5f ? Assets.Get<Mesh>("cube") : Assets.Get<Mesh>("plane");
		meshFilter->material = Assets.Get<Material>("material");
		meshObject->AddComponent(meshFilter);
		meshObject->AddComponent<Rotator>();
		scene->AddGameObject(meshObject);
	}
	
	Window* window = new Window("Sprites Test");
	window->SetOpenGL();
	window->SetResizable();
	window->Create(0, 0, 960, 640);
	window->GetGLContext();
	
	game->SetWindow(window);
	
	game->SetScene(scene);
	game->SetCamera(cameraObject);
	
	GameConfig.fps = 60;
	
	#ifdef EMSCRIPTEN
	emscripten_set_main_loop(loop, GameConfig.fps, 1);
	#else
	uint32 CURRENT_TICKS = SDL_GetTicks(),
		   LAST_TICKS = CURRENT_TICKS,
		   DELTA = 0,
		   LAST = CURRENT_TICKS,
		   GAME_TICKS = (1.0f / GameConfig.fps) * 1000;

	while(game->IsRunning()) {
		loop();
		
		CURRENT_TICKS = SDL_GetTicks();
		DELTA = CURRENT_TICKS - LAST_TICKS;
		LAST_TICKS = CURRENT_TICKS;
		
		LAST += DELTA;
		if (LAST > 1000) {
			std::cout << Time.fps << std::endl;
			LAST = 0;
		}
		
		if (DELTA <= GAME_TICKS) SDL_Delay(Mathf.Clamp(0, GAME_TICKS, DELTA - GAME_TICKS));
	}
	#endif
	
	delete game;
	delete window;

	Clear();
	
	std::cout << "END" << std::endl;
	return 0;
}