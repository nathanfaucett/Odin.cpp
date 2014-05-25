#include "../../src/odin.cpp"
using namespace Odin;

class Mover : public Component {
	private:
		Quatf m_rotation;
		Vec3f m_direction;
	public:
		float32 speed;
		Vec3f velocity;
		
		inline Mover(void) : Component() {
			speed = 2.0f;
		}
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

			GameObject* cameraObject = static_cast<Game*>(GetScene()->GetGame())->GetCamera();
			if (cameraObject == NULL) return;
			Transform* cameraTransform = cameraObject->GetComponent<Transform>();
			if (cameraTransform == NULL) return;
			
			Quatf& rotation = cameraTransform->rotation;
			m_rotation.FromAxisAngle(Vec3f(0.0f, 0.0f, 1.0f), rotation.GetRotationZ());
			
			float32 horizontal = Input.Axis("Horizontal");
			float32 vertical = Input.Axis("Vertical");
			
			velocity.x = speed * horizontal;
			velocity.y = speed * vertical;
			velocity *= Time.delta;
			velocity *= m_rotation;

			transform->position += velocity;
		}
		
		inline Mover& operator=(const Mover&)& = default;
		inline Mover& operator=(Mover&&)& = default;
};
class Rotator : public Component {
	public:
		float32 speed;
		
		inline Rotator(void) : Component() {
			speed = Mathf.RandFloat(-1.0f, 1.0f);
		}
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
			float32 dt = Mathf.PI * 0.5f * Time.delta * speed;
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
	
	Mesh* loadedMesh = new Mesh("loadedMesh", "../assets/mesh/mesh.obj");
	Assets.Add(loadedMesh);
	
	Mesh* plane = Mesh::Plane("plane", 1.0f, 1.0f, 1, 1);
	Assets.Add(plane);
	
	Mesh* sphere = Mesh::Sphere("sphere", 0.5, 16, 8);
	Assets.Add(sphere);
	
	Mesh* cube = Mesh::Cube("cube", 1.0f, 1.0f, 1.0f, 1, 1, 1);
	Assets.Add(cube);
	
	
	Material* material = new Material("material");
	material->vertex = GLSL(110,
		attribute vec3 position;
		attribute vec3 color;
		attribute vec3 normal;
		attribute vec4 tangent;
		attribute vec2 uv;
		
		uniform mat4 projection;
		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 modelView;
		uniform mat3 normalMatrix;
		
		varying vec4 vWorldPosition;
		varying vec3 vWorldNormal;
		varying vec3 vColor;
		varying vec3 vNormal;
		varying vec2 vUv;
		
		void main(void) {
			vWorldPosition = model * vec4(position, 1.0f);
			
			gl_Position = projection * view * vWorldPosition;
			vColor = color;
			vWorldNormal = (model * vec4(normal, 0.0)).xyz;
			vNormal = normal;
			vUv = uv;
		}
	);
	material->fragment = GLSL(110,
		out vec4 fragColor;
		
		uniform vec3 diffuseColor;
		uniform sampler2D texture;
		
		varying vec4 vWorldPosition;
		varying vec3 vWorldNormal;
		varying vec3 vColor;
		varying vec3 vNormal;
		varying vec2 vUv;
		
		void main(void) {
			fragColor = texture2D(texture, vUv);
			fragColor.xyz *= normalize(vWorldNormal); 
		}
	);
	//material->SetSide(Side::FrontAndBack);
	material->uniforms["texture"] = new MaterialUniformSampler2D(Assets.Get<Texture>("face"));
	static_cast<MaterialUniform3f*>(material->uniforms["diffuseColor"])->value.Set(1.0f, 1.0f, 1.0f);
	
	Assets.Add(material);
	
	Assets.Load();

	Scene* scene = new Scene();

	GameObject* cameraObject = new GameObject();
	Transform* cameraTransform = new Transform();
	cameraTransform->position.Set(0.0f, 5.0f, 5.0f);
	cameraObject->AddComponent(cameraTransform);
	cameraObject->AddComponent(new Camera());
	cameraObject->AddComponent(new OrbitControl());
	scene->AddGameObject(cameraObject);

	GameObject* spriteObject = new GameObject();
	spriteObject->AddComponent(new Transform());
	Sprite* sprite = new Sprite();
	sprite->material = Assets.Get<Material>("material");
	spriteObject->AddComponent(sprite);
	spriteObject->AddComponent(new Mover());
	scene->AddGameObject(spriteObject);

	GameObject* lastObject = NULL;
	for (uint32 i = 0, il = 10; i < il; i++) {
		GameObject* meshObject = new GameObject();
		Transform* meshTransform = new Transform();
		meshTransform->position.Set(Mathf.RandFloat(-5.0f, 5.0f), Mathf.RandFloat(-5.0f, 5.0f), Mathf.RandFloat(-5.0f, 5.0f));
		meshObject->AddComponent(meshTransform);
		MeshFilter* meshFilter = new MeshFilter();

		if (lastObject != NULL && Mathf.Random() > 0.5f) {
			lastObject->GetComponent<Transform>()->AddChild(meshObject->GetComponent<Transform>());
		}
		
		float32 num = Mathf.Random();
		if (num < (1.0f / 4.0f)) {
			meshFilter->mesh = Assets.Get<Mesh>("cube");
		} else if (num >= (1.0f / 4.0f) && num <= (2.0f / 4.0f)) {
			meshFilter->mesh = Assets.Get<Mesh>("sphere");
		} else if (num >= (2.0f / 4.0f) && num <= (3.0f / 4.0f)) {
			meshFilter->mesh = Assets.Get<Mesh>("plane");
		} else {
			meshFilter->mesh = Assets.Get<Mesh>("loadedMesh");
		}

		meshFilter->material = Assets.Get<Material>("material");
		meshObject->AddComponent(meshFilter);
		meshObject->AddComponent<Rotator>();
		scene->AddGameObject(meshObject);
		
		lastObject = meshObject;
	}
	lastObject = NULL;

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