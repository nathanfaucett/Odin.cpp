#ifndef _ODIN_BASE_GAME_CPP_
#define _ODIN_BASE_GAME_CPP_

namespace Odin {

	inline void BaseGame::m_Init(void) {

		m_window.Create(sf::VideoMode(m_width, m_height, 32), m_name);
		m_window.SetActive();

		renderer.Init();

		while (m_window.IsOpened()) {
			sf::Event event;

			while (m_window.GetEvent(event)) {

				if (event.Type == sf::Event::Closed) {
					m_window.Close();

				} else if (event.Type == sf::Event::Resized) {
					glViewport(0, 0, event.Size.Width, event.Size.Height);
				}
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			m_window.Display();

			m_Update();
		}
	}

	inline void BaseGame::m_Update(void) {
		Time.Update();

		renderer.Render();
	}

	inline void BaseGame::m_Deconstructor(void) {

	}

	inline BaseGame::BaseGame(void) : Object() {
		m_width = 960;
		m_height = 640;
		m_name = "Odin Window";

		m_Init();
	}

	inline BaseGame::~BaseGame(void) {
		m_Deconstructor();
	}
}

#endif