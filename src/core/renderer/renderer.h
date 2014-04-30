#ifndef ODIN_RENDERER_H
#define ODIN_RENDERER_H


namespace Odin {

	class Renderer : public Object {

		private:
			Window* m_window;
			bool m_glInitted;

			inline void m_Init(void);
			inline void m_InitGL(void);
			inline void m_RenderSprite(Sprite* sprite, Transform* transform, Camera* camera);

		protected:

		public:
			inline Renderer(void);
			inline Renderer(const Renderer& other);
			inline Renderer(const Renderer&& other);
			inline Renderer(Window* window);
			inline ~Renderer(void);
			
			inline virtual Renderer& Copy(const Renderer& other);
			inline virtual Renderer& Move(const Renderer&& other);

			inline Renderer& SetWindow(Window* window);
			
			inline void Render(Camera* camera, Scene* scene);
			
			inline void SetClearColor(const Colorf& color = Colorf::Black, const float32 alpha = 1.0f);
			#ifndef OPENGL_ES
			inline void SetPointSize(const float32 size = 1.0f);
			#endif
			inline void SetLineWidth(const float32 width = 1.0f);
			
			inline Renderer& operator =(const Renderer& other);
			inline Renderer& operator =(const Renderer&& other);
	};
}

#endif