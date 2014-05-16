#ifndef ODIN_GAME_H
#define ODIN_GAME_H

namespace Odin {

	class Game : public BaseGame {

		private:
			bool m_play;
			Renderer* m_renderer;
			Window* m_window;
			SDL_Surface* m_surface;

		protected:
			SDL_Event p_event;
			Camera* p_camera;

		public:
			inline Game(void);
			inline Game(std::string name);
			inline Game(const Game&) = default;
			inline Game(Game&&) = default;
			inline ~Game(void);

			inline virtual Game& SetCamera(GameObject* gameObject);

			inline virtual void Update(void);
			inline virtual void Render(void);
			inline virtual void Clear(void);   

			inline Game& SetWindow(Window* window);
			inline Game& SetSurface(SDL_Surface* surface);
			
			inline Game& operator=(const Game&)& = default;
			inline Game& operator=(Game&&)& = default;
	};
}

#endif