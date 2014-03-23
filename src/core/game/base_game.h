#ifndef _ODIN_BASE_GAME_H_
#define _ODIN_BASE_GAME_H_

namespace Odin {

	class BaseGame : public Object {

		private:
			int32 m_quit;
			uint32 m_width, m_height;
			std::string m_name;

			sf::Window m_window;

			inline void m_Init(void);
			inline void m_InitGL(void);
			inline void m_Update(void);

			inline void m_Deconstructor(void);

		public:
			Renderer renderer;

			inline BaseGame(void);
			inline ~BaseGame(void);
	};
}

#endif