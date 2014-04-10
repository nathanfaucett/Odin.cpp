#ifndef ODIN_GAME_CPP
#define ODIN_GAME_CPP

namespace Odin {

	inline Game::Game(void) : BaseGame() {
		p_Init();
		m_scene = NULL;
		m_camera = NULL;
	}

	inline Game::Game(const Game& other) : BaseGame() {
		Copy(other);
	}
	
	inline Game::Game(const Game&& other) : BaseGame() {
		Move(std::move(other));
	}

	inline Game::Game(std::string Name) : BaseGame(Name) {
		p_Init();
		m_scene = NULL;
		m_camera = NULL;
	}

	inline Game::~Game(void) {
		p_Clear();
	}

	inline Game& Game::Copy(const Game& other) {
		BaseGame::Copy(static_cast<BaseGame>(other));
	
		m_window = other.m_window;
		m_renderer = other.m_renderer;

		m_scene = other.m_scene;
		m_camera = other.m_camera;
		
		return *this;
	}

	inline Game& Game::Move(const Game&& other) {
		BaseGame::Move(std::move(static_cast<BaseGame>(other)));
		
		m_window = std::move(other.m_window);
		m_renderer = std::move(other.m_renderer);

		m_scene = std::move(other.m_scene);
		m_camera = std::move(other.m_camera);
		
		return *this;
	}

	inline void Game::p_Init(void) {
		m_window.name = name;
		m_window.Create(0, 0, 960, 640, false, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		m_renderer.SetWindow(&m_window);
	}

	inline void Game::p_Update(void) {
		BaseGame::p_Update();
		
		if (m_scene != NULL) {
			m_scene->p_Update();
		}
	}

	inline void Game::p_Clear(void) {
		BaseGame::p_Clear();
		
		m_scene = NULL;
		m_camera = NULL;
	}

	inline Game& Game::SetScene(Scene* scene) {
		if (scene == NULL) {
			Log("Game::SetScene: Scene can't be null", __LINE__);
			return *this;
		}
		
		m_scene = scene;
		scene->m_game = this;

		scene->p_Init();
		scene->p_Start();

		return *this;
	}

	inline Game& Game::SetCamera(GameObject* gameObject) {
		
		if (gameObject == NULL) {
			Log("Game::SetCamera: GameObject can't be null", __LINE__);
			return *this;
		}

		if (m_scene == NULL) {
			Log("Game::SetCamera: can't set camera without an active scene, use Game::SetScene first", __LINE__);
			return *this;
		}

		Camera* lastCamera = m_camera;

		if (m_scene->IndexOf(gameObject) == -1) {
			Log("Game::SetCamera: GameObject is not a member of the active Scene, adding it...", __LINE__);
			m_scene->AddGameObject(gameObject);
		}

		m_camera = gameObject->GetComponent<Camera>();

		if (m_camera != NULL) {
			m_camera->SetActive(true);

			if (lastCamera != NULL) {
				lastCamera->SetActive(false);
			}

		} else {
			Log("Game::SetCamera: GameObject does't have a Camera or a Camera2D Component", __LINE__);
			m_camera = lastCamera;
		}

		return *this;
	}

	inline Game& Game::Update(void) {
		p_Update();
		return *this;
	}

	inline Game& Game::Render(void) {
		if (m_scene == NULL) {
			Log("Game::Render: can't render scene without an active scene, use Game::SetScene first", __LINE__);
			return *this;
		}
		if (m_camera == NULL) {
			Log("Game::Render: can't render scene without an active camera, use Game::SetCamera first", __LINE__);
			return *this;
		}
		
		m_renderer.Render(m_camera, m_scene);

		return *this;
	}

	inline Game& Game::operator =(const Game& other) {
		return Copy(other);
	}
	
	inline Game& Game::operator =(const Game&& other) {
		return Move(std::move(other));
	}
}

#endif