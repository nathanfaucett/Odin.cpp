#ifndef ODIN_GAME_H
#define ODIN_GAME_H

namespace Odin {

	class Game : public BaseGame {

		private:
			SDL_Event m_event;
			bool m_play;
			Window* m_window;

			Scene* m_scene;
			Camera* m_camera;

		protected:
			inline virtual void p_Init(void);
			inline virtual void p_Clear(void);

		public:
			inline Game(void);
			inline Game(std::string name);
			inline ~Game(void);

			inline virtual Game& SetScene(Scene* scene);
			inline virtual Game& SetCamera(GameObject* gameObject);
	
			inline virtual void Init(void);
			inline virtual void Update(void);

			inline Window* GetWindow(void);
			inline Game& SetWindow(Window* m_window);
	};
}

#endif