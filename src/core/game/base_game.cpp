#ifndef _ODIN_BASE_GAME_CPP
#define _ODIN_BASE_GAME_CPP

namespace Odin {

	inline void BaseGame::m_Init(void) {
		
		m_window.Create(sf::VideoMode(m_width, m_height, 32), m_name);
		m_window.SetActive();
		m_InitGL();
		
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
			
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(0.0f, 0.0f, -200.0f);
			glRotatef(Time.delta * 50, 1.0f, 0.0f, 0.0f);
			glRotatef(Time.delta * 30, 0.0f, 1.0f, 0.0f);
			glRotatef(Time.delta * 90, 0.0f, 0.0f, 1.0f);
			
			glBegin(GL_QUADS);
			
				glVertex3f(-50.0f, -50.0f, -50.0f);
				glVertex3f(-50.0f,  50.0f, -50.0f);
				glVertex3f( 50.0f,  50.0f, -50.0f);
				glVertex3f( 50.0f, -50.0f, -50.0f);
			
				glVertex3f(-50.0f, -50.0f, 50.0f);
				glVertex3f(-50.0f,  50.0f, 50.0f);
				glVertex3f( 50.0f,  50.0f, 50.0f);
				glVertex3f( 50.0f, -50.0f, 50.0f);
			
				glVertex3f(-50.0f, -50.0f, -50.0f);
				glVertex3f(-50.0f,  50.0f, -50.0f);
				glVertex3f(-50.0f,  50.0f,  50.0f);
				glVertex3f(-50.0f, -50.0f,  50.0f);
			
				glVertex3f(50.0f, -50.0f, -50.0f);
				glVertex3f(50.0f,  50.0f, -50.0f);
				glVertex3f(50.0f,  50.0f,  50.0f);
				glVertex3f(50.0f, -50.0f,  50.0f);
			
				glVertex3f(-50.0f, -50.0f,  50.0f);
				glVertex3f(-50.0f, -50.0f, -50.0f);
				glVertex3f( 50.0f, -50.0f, -50.0f);
				glVertex3f( 50.0f, -50.0f,  50.0f);
			
				glVertex3f(-50.0f, 50.0f,  50.0f);
				glVertex3f(-50.0f, 50.0f, -50.0f);
				glVertex3f( 50.0f, 50.0f, -50.0f);
				glVertex3f( 50.0f, 50.0f,  50.0f);
			
			glEnd();
			
			m_window.Display();
		}
	}

	inline void BaseGame::m_InitGL(void) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glClearDepth(1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90.0f, 1.0f, 1.0f, 500.0f);
	}

	inline void BaseGame::m_Update(void) {
		
	}

	inline void BaseGame::m_Deconstructor(void) {

	}

	inline BaseGame::BaseGame(void) {
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