#ifndef ODIN_BASE_GAME_H
#define ODIN_BASE_GAME_H

namespace Odin {

	class BaseGame {

		private:
			
		protected:
			std::string p_name;
			
			bool p_quit;
			SDL_Event p_event;
			Scene* p_scene;
		public:
			inline BaseGame(void);
			inline BaseGame(std::string name);
			inline BaseGame(const BaseGame&) = default;
			inline BaseGame(BaseGame&&) = default;
			inline virtual ~BaseGame(void);
			
			inline virtual void Update(void);
			inline virtual void Clear(void);
			
			inline void Quit(void);
			inline bool IsRunning(void);
			
			inline virtual BaseGame& SetScene(Scene* scene);
			inline virtual Scene* GetScene(void);
			
			inline BaseGame& operator=(const BaseGame&)& = default;
			inline BaseGame& operator=(BaseGame&&)& = default;
	};
}

#endif