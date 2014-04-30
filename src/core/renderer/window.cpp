#ifndef ODIN_WINDOW_CPP
#define ODIN_WINDOW_CPP

namespace Odin {

	inline Window::Window(void) : Object() {
		m_window = NULL;
		m_glContext = NULL;
	}

	inline Window::Window(std::string Name) : Object(Name) {
		m_window = NULL;
		m_glContext = NULL;
	}

	inline Window::Window(const Window& other) : Object() {
		Copy(other);
	}
	
	inline Window::Window(const Window&& other) : Object() {
		Move(std::move(other));
	}

	inline Window::~Window(void) {
		Close();
	}

	inline Window& Window::Copy(const Window& other) {
		Object::Copy(static_cast<Object>(other));
		
		m_window = other.m_window;
		m_glContext = other.m_glContext;
		
		m_fullscreen = other.m_fullscreen;
		
		m_x = other.m_x;
		m_y = other.m_y;
		m_width = other.m_width;
		m_height = other.m_height;
		
		m_windowFlags = other.m_windowFlags;
		
		return *this;
	}
	
	inline Window& Window::Move(const Window&& other) {
		Object::Move(std::move(static_cast<Object>(other)));
		
		m_window = std::move(other.m_window);
		m_glContext = std::move(other.m_glContext);
		
		m_fullscreen = std::move(other.m_fullscreen);
		
		m_x = std::move(other.m_x);
		m_y = std::move(other.m_y);
		m_width = std::move(other.m_width);
		m_height = std::move(other.m_height);
		
		m_windowFlags = std::move(other.m_windowFlags);
		
		return *this;
	}

	inline bool Window::Create(int32 x, int32 y, int32 width, int32 height, bool fullscreen, uint32 windowFlags) {
		Close();

		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;
		m_windowFlags = windowFlags;

		m_window = SDL_CreateWindow(
		               name.c_str(),
		               m_x,
		               m_y,
		               m_width,
		               m_height,
		               m_windowFlags
		           );

		SetFullscreen(fullscreen);

		if (m_window == NULL) {
			Log("SDL_CreateWindow Failed", __LINE__);
			return false;
		}

		SDLCheckError(__LINE__);
		return true;
	}

	inline Window& Window::Close(void) {
		if (m_window != NULL) {
			SDL_DestroyWindow(m_window);
			m_window = NULL;
		}

		DeleteGLContext();
		return *this;
	}

	inline Window& Window::Update(void) {
		if (m_glContext == NULL || m_window == NULL) {
			return *this;
		}

		SDL_GL_SwapWindow(m_window);
		return *this;
	}

	inline bool Window::GetGLContext(void) {
		DeleteGLContext();

		m_glContext = SDL_GL_CreateContext(m_window);

		if (m_glContext == NULL) {
			Log("SDL_GL_CreateContext Failed", __LINE__);
			return false;
		}

		SDLCheckError(__LINE__);

		if (SDL_GL_SetSwapInterval(1) < 0) {
			Log("SDL_GL_SetSwapInterval Failed", __LINE__);
			return false;
		}

		SDLCheckError(__LINE__);

		return true;
	}

	inline Window& Window::DeleteGLContext(void) {
		if (m_glContext != NULL) {
			SDL_GL_DeleteContext(m_glContext);
			m_glContext = NULL;
		}

		return *this;
	}

	inline bool Window::IsOpen(void) {
		return (m_window != NULL);
	}

	inline bool Window::IsFullscreen(void) {
		return m_fullscreen;
	}

	inline Window& Window::SetFullscreen(bool value) {
		if (m_window == NULL) {
			return *this;
		}

		m_fullscreen = value;

		if (value) {
			SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);

			if ((m_windowFlags & SDL_WINDOW_FULLSCREEN) != SDL_WINDOW_FULLSCREEN) {
				m_windowFlags |= SDL_WINDOW_FULLSCREEN;
			}

		} else {
			SDL_SetWindowFullscreen(m_window, 0);

			if ((m_windowFlags & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN) {
				m_windowFlags ^= SDL_WINDOW_FULLSCREEN;
			}
		}

		return *this;
	}

	inline Window& Window::ToggleFullscreen(void) {
		m_fullscreen = !m_fullscreen;
		SetFullscreen(m_fullscreen);
		return *this;
	}

	inline Window& Window::SetSize(int32 width, int32 height) {
		if (m_window == NULL) {
			return *this;
		}

		m_width = width;
		m_height = height;

		SDL_SetWindowSize(m_window, m_width, m_height);
		return *this;
	}

	inline Window& Window::SetPosition(int32 x, int32 y) {
		if (m_window == NULL) {
			return *this;
		}

		m_x = x;
		m_y = y;

		SDL_SetWindowPosition(m_window, m_x, m_y);
		return *this;
	}

	inline Window& Window::SetTitle(std::string Name) {
		if (m_window == NULL) {
			return *this;
		}

		name = Name;
		SDL_SetWindowTitle(m_window, name.c_str());
		return *this;
	}

	inline int32 Window::X(void) {
		return m_x;
	}

	inline int32 Window::Y(void) {
		return m_y;
	}

	inline int32 Window::Width(void) {
		return m_width;
	}

	inline int32 Window::Height(void) {
		return m_height;
	}

	inline SDL_Window* Window::GetSDLWindow(void) {
		return m_window;
	}

	inline Window& Window::operator =(const Window& other) {
		return Copy(other);
	}
	
	inline Window& Window::operator =(const Window&& other) {
		return Move(std::move(other));
	}
}

#endif