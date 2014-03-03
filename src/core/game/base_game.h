#ifndef _ODIN_BASE_GAME_H
#define _ODIN_BASE_GAME_H

namespace Odin {

	class BaseGame {

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

			inline BaseGame(void);
			inline ~BaseGame(void);
	};
}

#endif