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

Game* game = new Game();

void loop() {
	game->Update();
	game->Render();
}

int main (int argc, char* argv[]) {
	std::cout << "START" << std::endl;
	
	Init();
	
	Assets.Add(new Texture("face", "../assets/images/face.png"));
	
	Mesh* plane = new Mesh("plane");
	
	plane->vertices.Push(new Vec3f(0.5f, 0.5f, 0.0f));
	plane->vertices.Push(new Vec3f(-0.5f, 0.5f, 0.0f));
	plane->vertices.Push(new Vec3f(-0.5f, -0.5f, 0.0f));
	plane->vertices.Push(new Vec3f(0.5f, -0.5f, 0.0f));
	
	plane->normals.Push(new Vec3f(0.0f, 0.0f, 1.0f));
	plane->normals.Push(new Vec3f(0.0f, 0.0f, 1.0f));
	plane->normals.Push(new Vec3f(0.0f, 0.0f, 1.0f));
	plane->normals.Push(new Vec3f(0.0f, 0.0f, 1.0f));
	
	plane->uv.Push(new Vec2f(1.0f, 0.0f));
	plane->uv.Push(new Vec2f(0.0f, 0.0f));
	plane->uv.Push(new Vec2f(0.0f, 1.0f));
	plane->uv.Push(new Vec2f(1.0f, 1.0f));
	
	plane->triangles = new uint32[6]{
		0, 1, 2,
		0, 2, 3,
	};
	plane->triangleCount = 6;
	
	Assets.Add(plane);
	
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
	static_cast<MaterialUniform3f*>(material->uniforms["diffuseColor"])->value.Set(1.0f, 0.5f, 0.25f);
	
	Assets.Add(material);
	
	Assets.Load();

	Scene* scene = new Scene();
	game->SetScene(scene);

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
		sprite->texture = Assets.Get<Texture>("face");
		spriteObject->AddComponent(sprite);
		spriteObject->AddComponent(new Mover());
		scene->AddGameObject(spriteObject);
	}
	
	for (uint32 i = 0, il = 10; i < il; i++) {
		GameObject* meshObject = new GameObject();
		Transform* meshTransform = new Transform();
		meshTransform->position.Set(Mathf.RandFloat(-1.0f, 1.0f), Mathf.RandFloat(-1.0f, 1.0f), Mathf.RandFloat(-1.0f, 1.0f));
		meshObject->AddComponent(meshTransform);
		MeshFilter* meshFilter = new MeshFilter();
		meshFilter->mesh = Assets.Get<Mesh>("plane");
		meshFilter->material = Assets.Get<Material>("material");
		meshObject->AddComponent(meshFilter);
		scene->AddGameObject(meshObject);
	}
	
	game->SetCamera(cameraObject);
	
	Window* window = new Window("Sprites Test");
	window->SetOpenGL();
	window->SetResizable();
	window->Create(0, 0, 960, 640);
	window->GetGLContext();
	
	game->SetWindow(window);
	
	GameConfig.fps = 60;
	
	#ifdef EMSCRIPTEN
	emscripten_set_main_loop(loop, GameConfig.fps, 1);
	#else
	float64 LAST_TIME = Time.Now64(),
			TARGET_TIME = 1.0 / GameConfig.fps,
			FRAME_TIME = 0.0,
			DELAY_TIME = 0.0;
			
	uint32 FRAME = 0,
		   TARGET_FPS = GameConfig.fps;

	while(game->IsRunning()) {
		FRAME++;
		if (Time.Now64() - LAST_TIME >= 1.0) {
			LAST_TIME = Time.Now64();
			FRAME_TIME = 1.0 / (FRAME - TARGET_FPS);
			
			DELAY_TIME = Mathf.Clamp(0.0, TARGET_TIME, TARGET_TIME - FRAME_TIME);
			std::cout << DELAY_TIME << " " << Time.fps << std::endl;
			FRAME = 0;
		}
		loop();
		Delay(DELAY_TIME);
	}
	#endif
	
	delete game;
	delete window;

	Clear();
	
	std::cout << "END" << std::endl;
	return 0;
}