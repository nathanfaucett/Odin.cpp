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
	
	inline void Renderer::m_RenderSprite(Camera* camera, Sprite* sprite, Transform* transform) {
		Material* material = sprite->material;
		if (material == NULL) return;
		
		CreateMaterial(material);
		CreateSpriteAttributes();
		SetProgram(material->GetOpenGLShader()->program);
		
		BindMaterial(material, camera->projection, camera->view, transform);
		BindSpriteAttributes(material);
		
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	
	inline void Renderer::m_RenderMeshFilter(Camera* camera, MeshFilter* meshFilter, Transform* transform) {
		Mesh* mesh = meshFilter->mesh;
		Material* material = meshFilter->material;
		if (mesh == NULL || material == NULL) return;
		
		CreateMaterial(material);
		CreateMeshAttributes(mesh);
		SetProgram(material->GetOpenGLShader()->program);
		
		BindMaterial(material, camera->projection, camera->view, transform);
		BindMeshAttributes(material, mesh);
		
		glDrawElements(GL_TRIANGLES, mesh->triangleCount, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
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
		
		if (p_surface == NULL || camera == NULL) return;

		if (m_width != p_surface->w || m_height != p_surface->h) {
			m_width = p_surface->w;
			m_height = p_surface->h;
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
		if (sprites != NULL) {
			for (i = 0, il = sprites->Length(); i < il; i++) {
				Sprite* sprite = (*sprites)[i];
				GameObject* gameObject = sprite->GetGameObject();
				if (gameObject == NULL) continue;
				Transform* transform = gameObject->GetComponent<Transform>();
				if (transform == NULL) continue;
				
				transform->UpdateMatrices(camera->view);
				m_RenderSprite(camera, sprite, transform);
			}
		}
		
		Array<MeshFilter*>* meshFilters = scene->GetComponents<MeshFilter>();
		if (meshFilters != NULL) {
			for (i = 0, il = meshFilters->Length(); i < il; i++) {
				MeshFilter* meshFilter = (*meshFilters)[i];
				GameObject* gameObject = meshFilter->GetGameObject();
				if (gameObject == NULL) continue;
				Transform* transform = gameObject->GetComponent<Transform>();
				if (transform == NULL) continue;
				
				transform->UpdateMatrices(camera->view);
				m_RenderMeshFilter(camera, meshFilter, transform);
			}
		}
	}
}

#endif