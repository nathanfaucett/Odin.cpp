#ifndef ODIN_GAME_H
#define ODIN_GAME_H

namespace Odin {

	class Game : public BaseGame {

		private:
			Window m_window;
			Renderer m_renderer;

			Scene* m_scene;
			Camera* m_camera;

		protected:
			inline void p_Init(void);
			inline void p_Update(void);
			inline void p_Clear(void);

		public:
			inline Game(void);
			inline Game(std::string Name);
			inline Game(const Game& other);
			inline Game(const Game&& other);
			inline ~Game(void);

			inline virtual Game& Copy(const Game& other);
			inline virtual Game& Move(const Game&& other);

			inline Game& SetScene(Scene* scene);
			inline Game& SetCamera(GameObject* gameObject);
			
			inline Game& Update(void);
			inline Game& Render(void);
			
			inline Game& operator =(const Game& other);
			inline Game& operator =(const Game&& other);
	};
}

#endif