#ifndef ODIN_BASE_GAME_H
#define ODIN_BASE_GAME_H

namespace Odin {

	class BaseGame {

		private:
			
		protected:
			std::string p_name;
			
			bool p_quit, p_resumed, p_running;
			SDL_Event p_event;
			Scene* p_scene;
			
			inline virtual void p_Init(void);
			inline virtual void p_Loop(void);
			inline void p_StartLoop(void);

		public:
			inline BaseGame(void);
			inline BaseGame(std::string name);
			inline virtual ~BaseGame(void);
			
			inline virtual void Update(void);
			inline virtual void Clear(void);
			
			inline void Pause(void);
			inline void Resume(void);
			inline void Quit(void);
			inline bool IsPaused(void);
			inline bool IsRunning(void);
			
			inline virtual BaseGame& SetScene(Scene* scene);
	};
}

#endif