#ifndef ODIN_RENDERER_CPP
#define ODIN_RENDERER_CPP

namespace Odin {

	inline Renderer::Renderer(void) : Object() {
		m_glInitted = false;
	}
	
	inline Renderer::Renderer(const Renderer& other) : Object() {
		Copy(other);
	}
	
	inline Renderer::Renderer(const Renderer&& other) : Object() {
		Move(std::move(other));
	}

	inline Renderer::Renderer(Window* window) : Object() {
		m_glInitted = false;
		SetWindow(window);
	}

	inline Renderer::~Renderer(void) {
		m_window = NULL;
	}
	
	inline Renderer& Renderer::Copy(const Renderer& other) {
		Object::Copy(static_cast<Object>(other));
		
		m_window = other.m_window;
		m_glInitted = other.m_glInitted;
		
		return *this;
	}
	
	inline Renderer& Renderer::Move(const Renderer&& other) {
		Object::Move(std::move(static_cast<Object>(other)));
		
		m_window = std::move(other.m_window);
		m_glInitted = std::move(other.m_glInitted);
		
		return *this;
	}

	inline void Renderer::m_InitGL(void) {
		m_glInitted = false;

		if (m_window == NULL) {
			return;
		}

		if (!m_window->GetGLContext()) {
			Log("Renderer::m_InitGL Window::GetGLContext Failed", __LINE__);
			return;
		}

		GLCheckError(__LINE__);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		m_clear = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
		glClear(m_clear);

		GLCheckError(__LINE__);
		m_glInitted = true;

		m_window->Update();
	}

	inline Renderer& Renderer::SetWindow(Window* window) {
		if (m_window == window) {
			return *this;
		}

		m_window = window;
		m_InitGL();

		return *this;
	}

	inline void Renderer::Render(Camera* camera, Scene* scene) {
		if (m_window == NULL || !m_glInitted) {
			return;
		}
		Array<Sprite*>* sprites = scene->GetComponents<Sprite>();
		Sprite* sprite = NULL;
		
		Transform* transform = NULL;
		uint32 i, length;

		glClear(m_clear);
		
		for (i = 0, length = sprites->Length(); i < length; i++) {
			sprite = (*sprites)[i];
			transform = sprite->GetGameObject()->GetComponent<Transform>();
			
			if (transform == NULL) continue;
			
			transform->UpdateMatrices(camera->view);
			m_RenderSprite(sprite, transform, camera);
		}
		
		m_window->Update();
	}
	
	inline void Renderer::m_RenderSprite(Sprite* sprite, Transform* transform, Camera* camera) {
		
	}
	
	inline Renderer& Renderer::operator =(const Renderer& other) {
		return Copy(other);
	}
	
	inline Renderer& Renderer::operator =(const Renderer&& other) {
		return Move(std::move(other));
	}
}

#endif