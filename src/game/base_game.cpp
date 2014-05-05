#ifndef ODIN_BASE_GAME_CPP
#define ODIN_BASE_GAME_CPP

namespace Odin {

	inline BaseGame::BaseGame(void) {
		p_name = "Odin Game";
		p_scene = NULL;
		
		p_quit = false;
		p_running = false;
	}

	inline BaseGame::BaseGame(std::string name) {
		p_name = name;
		p_scene = NULL;
		
		p_quit = false;
		p_running = false;
	}

	inline BaseGame::~BaseGame(void) {
		p_Clear();
	}

	inline void BaseGame::p_Init(void) {
		Resume();
	}
	inline void BaseGame::p_Clear(void) {
		p_scene = NULL;
	}
	inline void BaseGame::p_StartLoop(void) {
		#ifdef EMSCRIPTEN
			if (p_resumed) {
				p_resumed = false;
				emscripten_resume_main_loop(p_Loop, 60, 1);
			} else {
				emscripten_set_main_loop(p_Loop, 60, 1);
			}
		#else
			p_resumed = false;
			while(!p_quit) {
				while(p_running) {
					p_Loop();
				}
			}
		#endif
	}
	inline void BaseGame::p_Loop(void) {
		
	}

	inline void BaseGame::Update(void) {
		Time.Update();
	}
	
	inline void BaseGame::Pause(void) {
		if (p_running == false) return;
		p_running = false;
		
		#ifdef EMSCRIPTEN
			emscripten_pause_main_loop(p_Loop, 60, 1);
		#endif
	}
	inline void BaseGame::Resume(void) {
		if (p_running == true) return;
		p_running = true;
		p_resumed = true;
		
		p_StartLoop();
	}
	inline void BaseGame::Quit(void) {
		p_running = false;
		p_quit = true;
		
		#ifdef EMSCRIPTEN
			emscripten_pause_main_loop(p_Loop, 60, 1);
		#endif
	}
	inline bool BaseGame::IsPaused(void) {
		return !p_running;
	}
	inline bool BaseGame::IsRunning(void) {
		return p_running;
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