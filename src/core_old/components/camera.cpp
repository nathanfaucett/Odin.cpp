#ifndef _ODIN_CAMERA_CPP
#define _ODIN_CAMERA_CPP

namespace Odin {

	inline Camera::Camera(void) : Component() {

		m_width = 960.0f;
		m_height = 640.0f;
		m_invWidth = 1.0f / m_width;
		m_invHeight = 1.0f / m_height;

		m_aspect = 1.5f,
		m_fov = 35.0f;

		m_near = 0.0625f;
		m_far = 16384.0f;

		m_orthographic = false;
		m_orthographicSize = 2.0f;
		m_minOrthographicSize = Mathf.Epsilon;
		m_maxOrthographicSize = 1024.0f;

		m_needsUpdate = true;
	}

	inline Camera::~Camera(void) {
		Deconstructor();
	}

	inline void Camera::Deconstructor(void) {

	}

	inline void Camera::Update(void) {
		if (!m_active) {
			return;
		}

		if (m_needsUpdate) {

			if (!m_orthographic) {
				m_projection.Perspective(Mathf.ToRads(m_fov), m_aspect, m_near, m_far);

			} else {
				m_orthographicSize = Mathf.Clamp(m_orthographicSize, m_minOrthographicSize, m_maxOrthographicSize);

				float32 orthographicSize = m_orthographicSize,
				      right = orthographicSize * m_aspect,
				      left = -right,
				      top = orthographicSize,
				      bottom = -top;

				m_projection.Orthographic(left, right, top, bottom, m_near, m_far);
			}

			m_needsUpdate = false;
		}

		m_view.Inverse(GetGameObject()->matrixWorld);
	}
}

#endif