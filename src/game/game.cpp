#ifndef ODIN_GAME_CPP
#define ODIN_GAME_CPP

namespace Odin {

	inline Game::Game(void) : BaseGame() {
		p_camera = NULL;
		m_play = true;
		
		m_renderer = new Renderer();
		m_window = new Window(p_name);
	}
	inline Game::Game(std::string name) : BaseGame(name) {
		p_camera = NULL;
		m_play = true;
		
		m_renderer = new Renderer();
		m_window = new Window(p_name);
	}
	inline Game::~Game(void) {
		delete m_renderer;
		delete m_window;
		
		if (p_scene != NULL) {
			delete p_scene;
		} else {
			if (p_camera != NULL) delete p_camera;
		}
	}

	inline void Game::p_Init(void) {
		m_window->SetOpenGL();
		m_window->Create();
		m_window->GetGLContext();
		m_renderer->SetWindow(m_window);
		
		BaseGame::p_Init();
	}
	inline void Game::p_Loop(void) {
		
		while(SDL_PollEvent(&p_event)) {
			m_window->Update(&p_event);
			
			switch(p_event.type) {
				case SDL_QUIT:
					Quit();
					break;
			}
		}
		
		m_window->Swap();
		Update();
	}

	inline Game& Game::SetCamera(GameObject* gameObject) {
		
		if (gameObject == NULL) {
			Log("Game::SetCamera: GameObject can't be null", __LINE__);
			return *this;
		}

		if (p_scene == NULL) {
			Log("Game::SetCamera: can't set camera without an active scene, use Game::SetScene first", __LINE__);
			return *this;
		}

		Camera* lastCamera = p_camera;

		if (p_scene->IndexOf(gameObject) == -1) {
			Log("Game::SetCamera: GameObject is not a member of the active Scene, adding it...", __LINE__);
			p_scene->AddGameObject(gameObject);
		}

		p_camera = gameObject->GetComponent<Camera>();

		if (p_camera != NULL) {
			p_camera->SetActive(true);

			if (lastCamera != NULL) {
				lastCamera->SetActive(false);
			}
		} else {
			Log("Game::SetCamera: GameObject does't have a Camera or a Camera2D Component", __LINE__);
			p_camera = lastCamera;
		}

		return *this;
	}
	
	inline void Game::Init(void) {
		p_Init();
	}
	inline void Game::Update(void) {
		BaseGame::Update();
		
		if (p_scene != NULL) {
			p_scene->Update();
		}
		
		m_renderer->Render(p_camera, p_scene);
	}
	inline void Game::Clear(void) {
		BaseGame::Clear();
		p_camera = NULL;
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