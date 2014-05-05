#ifndef ODIN_RENDERER_CPP
#define ODIN_RENDERER_CPP

namespace Odin {
	
	inline Renderer::Renderer(void) : OpenGLRenderer() {
		m_clearColor = true;
		m_clearDepth = true;
		m_clearStencil = true;
		m_width = 1.0f;
		m_height = 1.0f;
	}
	inline Renderer::~Renderer(void) {
		
	}
	
	inline void Renderer::UseClearColor(bool value) {
		m_clearColor = value;
	}
	inline void Renderer::UseClearDepth(bool value) {
		m_clearDepth = value;
	}
	inline void Renderer::UseClearStencil(bool value) {
		m_clearStencil = value;
	}
	
	inline void Renderer::Render(Camera* camera, Scene* scene) {
		if (p_window == NULL || camera == NULL) return;
		
		if (m_width != p_window->width || m_height != p_window->height) {
			m_width = p_window->width;
			m_height = p_window->height;
			SetViewport(0.0f, 0.0f, m_width, m_height);
			
			if (camera->autoUpdate) {
				camera->Set(m_width, m_height);
				camera->Update();
			}
		}
		
		SetClearColor(camera->background, 1.0f);
		ClearCanvas(m_clearColor, m_clearDepth, m_clearStencil);
		
		if (scene == NULL) return;
		
		
	}
	
	inline void Renderer::m_RenderSprite(Camera* camera, Sprite* sprite) {
		
	}
}

#endif