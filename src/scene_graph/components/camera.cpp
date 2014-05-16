#ifndef ODIN_CAMERA_CPP
#define ODIN_CAMERA_CPP

namespace Odin {

	inline Camera::Camera(void) : Component() {
		m_needsUpdate = true;
		autoUpdate = true;

		m_width = 960.0f;
		m_height = 640.0f;
		m_invWidth = 1.0f / m_width;
		m_invHeight = 1.0f / m_height;

		background.Set(0.5f, 0.5f, 0.5f);

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
		Clear();
	}
	
	inline Camera* Camera::Clone(void) {
		return &((new Camera())->Copy(*this));
	}

	inline Camera& Camera::Copy(const Camera& other) {
		
		m_needsUpdate = true;
		autoUpdate = other.autoUpdate;
		
		m_width = other.m_width;
		m_height = other.m_height;
		m_invWidth = other.m_invWidth;
		m_invHeight = other.m_invHeight;

		background = other.background;

		m_aspect = other.m_aspect;
		m_fov = other.m_fov;

		m_near = other.m_near;
		m_far = other.m_far;

		m_orthographic = other.m_orthographic;
		m_orthographicSize = other.m_orthographicSize;

		m_minOrthographicSize = other.m_minOrthographicSize;
		m_maxOrthographicSize = other.m_maxOrthographicSize;
		
		return *this;
	}

	inline void Camera::Update(void) {
		if (!m_active) {
			return;
		}

		if (p_gameObject == NULL) {
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

		Transform* transform = p_gameObject->GetComponent<Transform>();

		if (transform == NULL) {
			return;
		}

		view.Inverse(transform->matrixWorld);
	}

	inline void Camera::Clear(void) {
		m_needsUpdate = true;
		autoUpdate = true;

		m_width = 960.0f;
		m_height = 640.0f;
		m_invWidth = 1.0f / m_width;
		m_invHeight = 1.0f / m_height;

		background.Set(0.5f, 0.5f, 0.5f);

		m_aspect = m_width / m_height;
		m_fov = 35.0f;

		m_near = 0.0625f;
		m_far = 16384.0f;

		m_orthographic = false;
		m_orthographicSize = 2.0f;

		m_minOrthographicSize = Mathf.Epsilon;
		m_maxOrthographicSize = 1024.0f;
	}

	inline Vec3f Camera::ToWorld(const Vec2f& v) {
		Mat4f mat;
		Vec3f out;

		out.x = 2.0f * (v.x * m_invWidth) - 1.0f;
		out.y = -2.0f * (v.y * m_invHeight) + 1.0f;
		out *= Mat4Mul<float32>(projection, view, mat).Inverse();
		out.z = m_near;

		return out;
	}
	inline Vec2f Camera::ToScreen(const Vec3f& v) {
		Vec3f tmp(v);
		Vec2f out;

		tmp *= projection * view;

		out.x = ((tmp.x + 1.0f) * 0.5f) * m_width;
		out.y = ((1.0f - tmp.y) * 0.5f) * m_height;

		return v;
	}

	inline Camera& Camera::Set(float32 width, float32 height) {
		m_width = width;
		m_height = height;
		m_invWidth = 1.0f / m_width;
		m_invHeight = 1.0f / m_height;

		m_aspect = m_width / m_height;

		m_needsUpdate = true;
		return *this;
	}
	inline Camera& Camera::SetWidth(float32 width) {
		m_width = width;
		m_invWidth = 1.0f / m_width;
		m_aspect = m_width / m_height;

		m_needsUpdate = true;
		return *this;
	}
	inline float32 Camera::GetWidth(void) {
		return m_width;
	}
	inline float32 Camera::GetInvWidth(void) {
		return m_invWidth;
	}
	inline Camera& Camera::SetHeight(float32 height) {
		m_height = height;
		m_invHeight = 1.0f / m_height;
		m_aspect = m_width / m_height;

		m_needsUpdate = true;
		return *this;
	}
	inline float32 Camera::GetHeight(void) {
		return m_height;
	}
	inline float32 Camera::GetInvHeight(void) {
		return m_invHeight;
	}
	inline float32 Camera::GetAspect(void) {
		return m_aspect;
	}

	inline Camera& Camera::SetActive(bool value) {
		m_active = value;

		m_needsUpdate = true;
		return *this;
	}inline bool Camera::IsActive(void) {
		return m_active;
	}

	inline Camera& Camera::SetFov(float32 fov) {
		m_fov = fov;
		m_needsUpdate = true;
		return *this;
	}
	inline float32 Camera::GetFov(void) {
		return m_fov;
	}
	inline Camera& Camera::SetNear(float32 near) {
		m_near = near;
		m_needsUpdate = true;
		return *this;
	}
	inline float32 Camera::GetNear(void) {
		return m_near;
	}
	inline Camera& Camera::SetFar(float32 far) {
		m_far = far;
		m_needsUpdate = true;
		return *this;
	}
	inline float32 Camera::GetFar(void) {
		return m_far;
	}

	inline Camera& Camera::SetOrthographic(bool value) {
		m_orthographic = value;
		m_needsUpdate = true;
		return *this;
	}
	inline bool Camera::IsOrthographic(void) {
		return m_orthographic;
	}
	inline Camera& Camera::ToggleOrthographic(void) {
		m_orthographic = !m_orthographic;
		m_needsUpdate = true;
		return *this;
	}
	
	inline Camera& Camera::SetOrthographicSize(float32 orthographicSize) {
		m_orthographicSize = orthographicSize;
		m_needsUpdate = true;
		return *this;
	}
	inline float32 Camera::GetOrthographicSize(void) {
		return m_orthographicSize;
	}
}

#endif