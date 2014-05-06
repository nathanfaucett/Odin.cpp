#ifndef ODIN_RENDERER_H
#define ODIN_RENDERER_H

namespace Odin {
	
	class Renderer : public OpenGLRenderer{
		
		private:
			SDL_Surface* m_screenSurface;
			
			bool m_clearColor, m_clearDepth, m_clearStencil;
			float32 m_width, m_height;
			
			bool m_spriteBuffersInit;
			uint32 m_spriteVertexBuffers, m_spriteUvBuffers, m_spriteShader;
			
			inline void m_InitSpriteBuffers(void);
			inline void m_RenderSprite(Camera* camera, Sprite* sprite);
		protected:

		public:
			inline Renderer(void);
			inline ~Renderer(void);
			
			inline void UseClearColor(bool value = true);
			inline void UseClearDepth(bool value = true);
			inline void UseClearStencil(bool value = true);
			
			inline void Render(Camera* camera, Scene* scene);
	};
}

#endif