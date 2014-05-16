#ifndef ODIN_GAME_CPP
#define ODIN_GAME_CPP

namespace Odin {

	inline Game::Game(void) : BaseGame() {
		p_camera = NULL;
		m_play = true;
		
		m_renderer = new Renderer();
		m_surface = NULL;
	}
	inline Game::Game(std::string name) : BaseGame(name) {
		p_camera = NULL;
		m_play = true;
		
		m_renderer = new Renderer();
		m_surface = NULL;
	}
	inline Game::~Game(void) {
		if (p_scene != NULL) delete p_scene;
		p_camera = NULL;
		m_surface = NULL;
		
		delete m_renderer;
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
	
	inline void Game::Update(void) {
		BaseGame::Update();
		bool WINDOW = m_window != NULL;
		
		while(SDL_PollEvent(&p_event)) {
			if (p_event.type == SDL_QUIT) Quit();
			
			if (WINDOW) m_window->Update(&p_event);
			Input.HandleEvents(&p_event);
		}
		
		Input.Update();
		
		if (p_scene != NULL) {
			p_scene->Update();
		}
	}
	inline void Game::Render(void) {
		m_renderer->Render(p_camera, p_scene);
		if (m_window != NULL) m_window->Swap();
	}
	inline void Game::Clear(void) {
		BaseGame::Clear();
		p_camera = NULL;
	}
	
	inline Game& Game::SetWindow(Window* window) {
		if (window == NULL || window == m_window) {
			return *this;
		}
		m_window = window;
		SetSurface(window->GetSDLSurface());
		return *this;
	}
	inline Game& Game::SetSurface(SDL_Surface* surface) {
		if (surface == NULL || surface == m_surface) {
			return *this;
		}
		m_surface = surface;
		m_renderer->SetSurface(m_surface);
		return *this;
	}
}

#endif