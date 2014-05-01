#ifndef ODIN_WINDOW_H
#define ODIN_WINDOW_H

namespace Odin {

	class Window {

		private:
			std::string m_title;
			int32 m_x, m_y, m_width, m_height;
			bool m_fullscreen, m_fullscreenDesktop, m_opengl, m_borderless, m_resizable,
				 m_inputGrabbed, m_inputFocus, m_mouseFocus, m_allowHighDPI;

			SDL_Window* m_window;
			SDL_GLContext m_glContext;
			
			inline bool m_Create(int32 x, int32 y, int32 width, int32 height);
		protected:

		public:
			inline Window(void);
			inline Window(std::string title);
			inline ~Window(void);

			inline bool Create(void);
			inline bool Create(int32 x, int32 y, int32 width, int32 height);
			inline Window& Close(void);
			inline Window& Update(const SDL_Event* event);

			inline bool GetGLContext(void);
			inline Window& DeleteGLContext(void);

			inline bool IsOpen(void);
			inline bool IsFullscreen(void);

			inline Window& SetFullscreen(bool value = true);
			inline Window& SetFullscreenDesktop(bool value = true);
			inline Window& ToggleFullscreen(void);
			inline Window& ToggleFullscreenDesktop(void);
			inline Window& SetOpenGL(bool value = true);
			inline Window& SetBorderless(bool value = true);
			inline Window& SetResizable(bool value = true);
			inline Window& SetInputGrabbed(bool value = true);
			inline Window& SetInputFocus(bool value = true);
			inline Window& SetMouseFocus(bool value = true);
			inline Window& SetAllowHighDPI(bool value = true);
			
			inline Window& SetPosition(int32 x, int32 y);
			inline Window& SetSize(int32 width, int32 height);
			inline Window& SetTitle(std::string title);

			inline int32 GetX(void);
			inline int32 GetY(void);
			inline int32 GetWidth(void);
			inline int32 GetHeight(void);

			inline SDL_Window* GetSDLWindow(void);
	};
}

#endif