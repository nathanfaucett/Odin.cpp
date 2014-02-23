#ifndef ODIN_CAMERA_H
#define ODIN_CAMERA_H

namespace Odin {

	class Camera : public Component {

		private:
			bool m_needsUpdate, m_active;
			float m_width, m_height, m_invWidth, m_invHeight;

			Color m_background;

			float m_aspect, m_fov;
			float m_near, m_far;

			bool m_orthographic;
			float m_orthographicSize;
			float m_minOrthographicSize, m_maxOrthographicSize;

			Mat4 m_projection, m_view;

		protected:

		public:

			inline explicit Camera(void);

			inline ~Camera(void);

			inline void Deconstructor(void);

			inline void Update(void);

			inline void Destroy(void);
	};
}

#endif