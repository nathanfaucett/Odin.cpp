#ifndef _ODIN_CAMERA_CPP_
#define _ODIN_CAMERA_CPP_

namespace Odin {

	inline Camera::Camera(void) : Component() {
		m_needsUpdate = true;
		
		m_width = 960.0f;
		m_height = 640.0f;
		m_invWidth = 1.0f / m_width;
		m_invHeight = 1.0f / m_height;

		background.Set(0.5, 0.5, 0.5);

		m_aspect = m_width / m_height;
		m_fov = 35.0f;

		m_near = 0.0625f;
		m_far = 16384.0f;

		m_orthographic = false;
		m_orthographicSize = 2.0f;

		m_minOrthographicSize = Mathf.Epsilon;
		m_maxOrthographicSize = 1024.0f;
	}

	inline Camera::~Camera(void) {
		p_Clear();
	}

	inline void Camera::p_Clear(void) {
		Component::p_Clear();
	}

	inline void Camera::p_Init(void) {

	}

	inline void Camera::p_Start(void) {

	}

	inline void Camera::p_Update(void) {
		if (!m_active) return;
		if (p_gameObject == NULL) {
			return;
		}
		
		Transform* transform = p_gameObject->GetComponent<Transform>();
		if (transform == NULL) {
			return;
		}

		if (m_needsUpdate) {

			if (!m_orthographic) {
				projection.Perspective(Mathf.ToRads(m_fov), m_aspect, m_near, m_far);
			} else {
				m_orthographicSize = Mathf.Clamp(m_orthographicSize, m_minOrthographicSize, m_maxOrthographicSize);

				float32 right = m_orthographicSize * m_aspect,
						left = -right,
						top = m_orthographicSize,
						bottom = -top;

				projection.Orthographic(left, right, top, bottom, m_near, m_far);
			}

			m_needsUpdate = false;
		}
		
		view.Inverse(transform->matrixWorld);
	}

	inline void Camera::p_Sort(void) {
		p_order = m_active ? 0.0f : 1.0f;
	}
}

#endif