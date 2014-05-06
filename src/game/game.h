#ifndef ODIN_GAME_H
#define ODIN_GAME_H

namespace Odin {

	class Game : public BaseGame {

		private:
			bool m_play;
			Renderer* m_renderer;
			Window* m_window;

		protected:
			SDL_Event p_event;
			Camera* p_camera;

			inline virtual void p_Init(void); 
			inline virtual void p_Loop(void);

		public:
			inline Game(void);
			inline Game(std::string name);
			inline ~Game(void);

			inline virtual Game& SetCamera(GameObject* gameObject);

			inline virtual void Init(void);
			inline virtual void Update(void);
			inline virtual void Clear(void);   

			inline Window* GetWindow(void);
			inline Game& SetWindow(Window* m_window);
	};
}

#endif