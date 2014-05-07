#ifndef ODIN_RENDERER_CPP
#define ODIN_RENDERER_CPP

namespace Odin {
	
	inline Renderer::Renderer(void) : OpenGLRenderer() {
		m_spriteBuffersInit = false;
		m_clearColor = true;
		m_clearDepth = true;
		m_clearStencil = true;
		m_width = 1.0f;
		m_height = 1.0f;
		
		m_spriteVertexBuffers = 0;
		m_spriteProgram = 0;
	}
	inline Renderer::~Renderer(void) {
		
	}
	
	inline void Renderer::m_InitSpriteBuffers(void) {
		if (m_spriteBuffersInit) return;
		
		float32 vertexBuffers[12] = {
			-0.5f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			0.5f, -0.5f, 0.0f
		};
		m_spriteVertexBuffers = CreateVertexBuffer<float32>(vertexBuffers, sizeof(vertexBuffers));
		
		float32 uvBuffers[12] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f,
		};
		m_spriteUvBuffers = CreateVertexBuffer<float32>(uvBuffers, sizeof(uvBuffers));
		
		m_spriteProgram = CreateProgram(
			GLSL(330,
				layout(location = 0)in vec3 position;
				layout(location = 1)in vec2 uv;
				
				uniform mat4 projection; 
				uniform mat4 modelView; 
				
				varying vec2 vUv;
				
				void main(void) {
					gl_Position = projection * modelView * vec4(position, 1.0f);
					vUv = uv;
				}
			),
			GLSL(330,
				uniform sampler2D texture;
				out vec4 fragColor;
				
				varying vec2 vUv;
				
				void main(void) {
					fragColor = vec4(texture2D(texture, vUv));
				}
			)
		);
		m_spritePosition = 0;
		m_spriteUv = 1;
		m_spriteTexture = glGetUniformLocation(m_spriteProgram, "texture");
		m_spriteProjection = glGetUniformLocation(m_spriteProgram, "projection");
		m_spriteModelView = glGetUniformLocation(m_spriteProgram, "modelView");
		
		m_spriteBuffersInit = true;
	}
	
	inline void Renderer::m_RenderSprite(Camera* camera, Sprite* sprite, Transform* transform) {
		m_InitSpriteBuffers();
		
		SetProgram(m_spriteProgram);
		
		BindBuffer(m_spritePosition, m_spriteVertexBuffers, GL_ARRAY_BUFFER, 3, GL_FLOAT, 0);
		BindBuffer(m_spriteUv, m_spriteUvBuffers, GL_ARRAY_BUFFER, 2, GL_FLOAT, 0);
		
		glUniformMatrix4fv(m_spriteProjection, 1, false, camera->projection.GetArray());
		glUniformMatrix4fv(m_spriteModelView, 1, false, transform->modelView.GetArray());
		BindTexture(m_spriteTexture, sprite->texture);
		
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
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
		uint32 i, il;
		
		Array<Sprite*>* sprites = scene->GetComponents<Sprite>();
		for (i = 0, il = sprites->Length(); i < il; i++) {
			Sprite* sprite = (*sprites)[i];
			GameObject* gameObject = sprite->GetGameObject();
			Transform* transform = gameObject->GetComponent<Transform>();
			
			transform->UpdateMatrices(camera->view);
			m_RenderSprite(camera, sprite, transform);
		}
	}
}

#endif