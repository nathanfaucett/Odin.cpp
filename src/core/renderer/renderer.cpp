#ifndef _ODIN_RENDERER_CPP_
#define _ODIN_RENDERER_CPP_

namespace Odin {

	inline void Renderer::m_InitGL() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glClearDepth(1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
	}

	inline Renderer::Renderer(void) : Object() {

	}

	inline Renderer::~Renderer(void) {

	}

	inline void Renderer::Init() {
		m_InitGL();
	}

	inline void Renderer::Render(void) {

	}
}

#endif