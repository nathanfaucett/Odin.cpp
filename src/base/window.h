#ifndef ODIN_WINDOW_H
#define ODIN_WINDOW_H

namespace Odin {

	class Window : public Object {

		private:
			bool m_fullscreen;
			int32 m_x, m_y, m_width, m_height;
			uint32 m_windowFlags;

			SDL_Window* m_window;
			SDL_GLContext m_glContext;

		protected:

		public:
			inline Window(void);
			inline Window(std::string Name);
			inline Window(const Window& other);
			inline Window(const Window&& other);
			inline ~Window(void);

			inline virtual Window& Copy(const Window& other);
			inline virtual Window& Move(const Window&& other);

			inline bool Create(int32 x, int32 y, int32 width, int32 height, bool fullscreen = false, uint32 m_windowFlags = SDL_WINDOW_OPENGL);
			inline Window& Close(void);
			inline Window& Update(void);

			inline bool GetGLContext(void);
			inline Window& DeleteGLContext(void);

			inline bool IsOpen(void);
			inline bool IsFullscreen(void);

			inline Window& SetFullscreen(bool value = true);
			inline Window& ToggleFullscreen(void);
			inline Window& SetPosition(int32 x, int32 y);
			inline Window& SetSize(int32 width, int32 height);
			inline Window& SetTitle(std::string Name);

			inline int32 X(void);
			inline int32 Y(void);
			inline int32 Width(void);
			inline int32 Height(void);

			inline SDL_Window* GetSDLWindow(void);
			
			inline Window& operator =(const Window& other);
			inline Window& operator =(const Window&& other);
	};
}

#endif