#ifndef ODIN_RENDERER_H
#define ODIN_RENDERER_H


namespace Odin {

	class Renderer : public Object {

		private:
			Window* m_window;
			bool m_glInitted;

			uint32 m_clear;

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
			
			inline Renderer& operator =(const Renderer& other);
			inline Renderer& operator =(const Renderer&& other);
	};
}

#endif