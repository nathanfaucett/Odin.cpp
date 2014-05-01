#ifndef ODIN_GAME_CPP
#define ODIN_GAME_CPP

namespace Odin {

	inline Game::Game(void) : BaseGame() {
		m_scene = NULL;
		m_camera = NULL;
		m_play = true;
		
		m_window = new Window;
		m_window->Create();
	}
	inline Game::Game(std::string name) : BaseGame(name) {
		m_scene = NULL;
		m_camera = NULL;
		m_play = true;
		
		m_window = new Window;
		m_window->Create();
	}
	inline Game::~Game(void) {
		BaseGame::p_Clear();
		p_Clear();
		delete m_window;
	}

	inline void Game::p_Init(void) {
		m_window->SetTitle(p_name);
		m_window->SetOpenGL();
	}
	inline void Game::p_Clear(void) {
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
	
	inline void Game::Init(void) {
		p_Init();
		
		while(m_play) {
			Update();

			while(SDL_PollEvent(&m_event)) {
				m_window->Update(&m_event);
				
				switch(m_event.type) {
					case SDL_QUIT:
						m_play = false;
						break;
				}
			}
		}
	}
	inline void Game::Update(void) {
		BaseGame::Update();
		
		if (m_scene != NULL) {
			m_scene->Update();
		}
	}
	
	inline Window* Game::GetWindow(void) {
		return m_window;
	}
	inline Game& Game::SetWindow(Window* window) {
		if (window == NULL || window == m_window) {
			return *this;
		}
		m_window = window;
		return *this;
	}
}

#endif