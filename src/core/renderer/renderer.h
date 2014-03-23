#ifndef _ODIN_RENDERER_H_
#define _ODIN_RENDERER_H_


namespace Odin {

	class Renderer : public Object {

		private:
			inline void m_InitGL();

		public:
			inline Renderer(void);
			inline ~Renderer(void);

			inline void Init();

			inline void Render(void);
	};
}

#endif