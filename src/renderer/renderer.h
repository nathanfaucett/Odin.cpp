#ifndef ODIN_RENDERER_H
#define ODIN_RENDERER_H

namespace Odin {
	
	class Renderer : public OpenGLRenderer{
		
		private:
			bool m_clearColor, m_clearDepth, m_clearStencil;
			float32 m_width, m_height;
			
			bool m_spriteBuffersInit;
			uint32 m_spriteVertexBuffers, m_spriteUvBuffers, m_spriteProgram;
			int32 m_spritePosition, m_spriteUv, m_spriteProjection, m_spriteModelView, m_spriteTexture;
			
			inline void m_InitSpriteBuffers(void);
			inline void m_RenderSprite(Camera* camera, Sprite* sprite, Transform* transform);
			inline void m_RenderMeshFilter(Camera* camera, MeshFilter* meshFilter, Transform* transform);
		protected:

		public:
			inline Renderer(void);
			inline Renderer(const Renderer&) = default;
			inline Renderer(Renderer&&) = default;
			inline ~Renderer(void);
			
			inline void UseClearColor(bool value = true);
			inline void UseClearDepth(bool value = true);
			inline void UseClearStencil(bool value = true);
			
			inline void Render(Camera* camera, Scene* scene);
			
			inline Renderer& operator=(const Renderer&)& = default;
			inline Renderer& operator=(Renderer&&)& = default;
	};
}

#endif