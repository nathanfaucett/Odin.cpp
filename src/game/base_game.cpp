#ifndef ODIN_BASE_GAME_CPP
#define ODIN_BASE_GAME_CPP

namespace Odin {

	inline BaseGame::BaseGame(void) {
		p_name = "Odin Game";
		p_scene = NULL;
		
		p_quit = false;
	}

	inline BaseGame::BaseGame(std::string name) {
		p_name = name;
		p_scene = NULL;
		
		p_quit = false;
	}

	inline BaseGame::~BaseGame(void) {
		
	}

	inline void BaseGame::Update(void) {
		Time.Update();
		Input.mouseWheel = 0;
	}
	inline void BaseGame::Clear(void) {
		p_scene = NULL;
	}
	
	inline void BaseGame::Quit(void) {
		p_quit = true;
	}
	inline bool BaseGame::IsRunning(void) {
		return p_quit == false;
	}

	inline BaseGame& BaseGame::SetScene(Scene* scene) {
		if (scene == NULL) {
			Log("Game::SetScene: Scene can't be null", __LINE__);
			return *this;
		}
		
		p_scene = scene;
		scene->m_game = this;

		scene->p_Init();
		scene->p_Start();

		return *this;
	}
}

#endif