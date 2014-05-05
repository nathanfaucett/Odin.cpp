#ifndef ODIN_WINDOW_CPP
#define ODIN_WINDOW_CPP

namespace Odin {

	inline Window::Window(void) {
		m_window = NULL;
		m_glContext = NULL;
		
		m_title = "Window";
		m_fullscreen = false;
		m_fullscreenDesktop = false;
		m_opengl = false;
		m_borderless = false;
		m_resizable = false;
		m_inputGrabbed = false;
		m_inputFocus = false;
		m_mouseFocus = false;
		m_allowHighDPI = false;
	}
	inline Window::Window(std::string title) {
		m_window = NULL;
		m_glContext = NULL;
		
		m_title = title;
		m_fullscreen = false;
		m_fullscreenDesktop = false;
		m_opengl = false;
		m_borderless = false;
		m_resizable = false;
		m_inputGrabbed = false;
		m_inputFocus = false;
		m_mouseFocus = false;
		m_allowHighDPI = false;
	}
	inline Window::~Window(void) {
		Close();
	}

	inline bool Window::m_Create(int32 X, int32 Y, int32 Width, int32 Height) {
		Close();
		uint32 flags = 0;
		
		if (m_fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
		if (m_fullscreenDesktop && !m_fullscreen) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		if (m_opengl) flags |= SDL_WINDOW_OPENGL;
		if (m_borderless) flags |= SDL_WINDOW_BORDERLESS;
		if (m_resizable) flags |= SDL_WINDOW_RESIZABLE;
		if (m_inputGrabbed) flags |= SDL_WINDOW_INPUT_GRABBED;
		if (m_inputFocus) flags |= SDL_WINDOW_INPUT_FOCUS;
		if (m_mouseFocus) flags |= SDL_WINDOW_MOUSE_FOCUS;
		if (m_allowHighDPI) flags |= SDL_WINDOW_ALLOW_HIGHDPI;
		
		x = X;
		y = Y;
		width = Width;
		height = Height;
		m_window = SDL_CreateWindow(m_title.c_str(), x, y, width, height, flags);

		if (m_window == NULL) {
			Log("SDL_CreateWindow Failed", __LINE__);
			return false;
		}

		SDLCheckError(__LINE__);
		return true;
	}

	inline bool Window::Create(void) {
		return m_Create(x, y, width, height);
	}

	inline bool Window::Create(int32 X, int32 Y, int32 Width, int32 Height) {
		return m_Create(X, Y, Width, Height);
	}

	inline Window& Window::Close(void) {
		if (m_window != NULL) {
			SDL_DestroyWindow(m_window);
			m_window = NULL;
		}

		DeleteGLContext();
		return *this;
	}

	inline Window& Window::Update(const SDL_Event* event) {
		if (m_window == NULL) {
			return *this;
		}
		
		if (event->type == SDL_WINDOWEVENT) {
			switch (event->window.event) {
				case SDL_WINDOWEVENT_RESIZED:
					width = event->window.data1;
					height = event->window.data2;
					break;
				
				case SDL_WINDOWEVENT_MOVED:
					x = event->window.data1;
					y = event->window.data2;
					break;
			}
		}
		
		return *this;
	}

	inline Window& Window::Swap(void) {
		if (m_window != NULL && m_glContext != NULL) {
			SDL_GL_SwapWindow(m_window);
		}
		
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
		
		glewExperimental = true;
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
			QuitError("glewInit");
		}
		
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
		m_fullscreen = value;
		
		if (m_window == NULL) {
			return *this;
		}

		if (value) {
			SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);
		} else {
			SDL_SetWindowFullscreen(m_window, 0);
		}

		return *this;
	}
	inline Window& Window::SetFullscreenDesktop(bool value) {
		m_fullscreenDesktop = value;
		
		if (m_window == NULL) {
			return *this;
		}

		if (value) {
			SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		} else {
			SDL_SetWindowFullscreen(m_window, 0);
		}

		return *this;
	}
	inline Window& Window::ToggleFullscreen(void) {
		m_fullscreen = !m_fullscreen;
		SetFullscreen(m_fullscreen);
		return *this;
	}
	inline Window& Window::ToggleFullscreenDesktop(void) {
		m_fullscreenDesktop = !m_fullscreenDesktop;
		SetFullscreenDesktop(m_fullscreenDesktop);
		return *this;
	}
	inline Window& Window::SetOpenGL(bool value) {
		m_opengl = value;
		
		if (m_opengl == value || m_window == NULL) {
			return *this;
		}
		Create();
		return *this;
	}
	inline Window& Window::SetBorderless(bool value) {
		m_borderless = value;
		
		if (m_borderless == value || m_window == NULL) {
			return *this;
		}
		Create();
		return *this;
	}
	inline Window& Window::SetResizable(bool value) {
		m_resizable = value;
		
		if (m_resizable == value || m_window == NULL) {
			return *this;
		}
		Create();
		return *this;
	}
	inline Window& Window::SetInputGrabbed(bool value) {
		m_inputGrabbed = value;
		
		if (m_inputGrabbed == value || m_window == NULL) {
			return *this;
		}
		Create();
		return *this;
	}
	inline Window& Window::SetInputFocus(bool value) {
		m_inputFocus = value;
		
		if (m_inputFocus == value || m_window == NULL) {
			return *this;
		}
		Create();
		return *this;
	}
	inline Window& Window::SetMouseFocus(bool value) {
		m_mouseFocus = value;
		
		if (m_mouseFocus == value || m_window == NULL) {
			return *this;
		}
		Create();
		return *this;
	}
	inline Window& Window::SetAllowHighDPI(bool value) {
		m_allowHighDPI = value;
		
		if (m_allowHighDPI == value || m_window == NULL) {
			return *this;
		}
		Create();
		return *this;
	}

	inline Window& Window::SetSize(int32 Width, int32 Height) {
		width = Width;
		height = Height;
		
		if (m_window == NULL) {
			return *this;
		}
		SDL_SetWindowSize(m_window, width, height);
		return *this;
	}

	inline Window& Window::SetPosition(int32 X, int32 Y) {
		x = X;
		y = Y;
		
		if (m_window == NULL) {
			return *this;
		}
		SDL_SetWindowPosition(m_window, X, Y);
		return *this;
	}

	inline Window& Window::SetRect(int32 X, int32 Y, int32 Width, int32 Height) {
		x = X;
		y = Y;
		width = Width;
		height = Height;
		
		if (m_window == NULL) {
			return *this;
		}
		SDL_SetWindowSize(m_window, width, height);
		SDL_SetWindowPosition(m_window, x, y);
		return *this;
	}

	inline Window& Window::SetTitle(std::string title) {
		m_title = title;
		
		if (m_window == NULL) {
			return *this;
		}
		SDL_SetWindowTitle(m_window, m_title.c_str());
		return *this;
	}

	inline SDL_Window* Window::GetSDLWindow(void) {
		return m_window;
	}
}

#endif