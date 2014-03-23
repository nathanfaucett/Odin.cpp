#ifndef _ODIN_CAMERA_H_
#define _ODIN_CAMERA_H_

namespace Odin {

	class Camera : public Component {

		private:
			bool m_active, m_needsUpdate;
			
			float32 m_width, m_height;
			float32 m_invWidth, m_invHeight;
	
			float32 m_aspect, m_fov;
	
			float32 m_near, m_far;
	
			bool m_orthographic;
			float32 m_orthographicSize;
	
			float32 m_minOrthographicSize;
			float32 m_maxOrthographicSize;
			
		protected:
			inline void p_Clear(void);

			inline void p_Init(void);
			inline void p_Start(void);
			inline void p_Update(void);

			inline void p_Sort(void);

		public:
			Colorf background;
			Mat4f projection, view;

			inline Camera(void);
			inline ~Camera(void);
	};
}

#endif