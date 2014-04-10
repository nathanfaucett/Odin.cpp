#ifndef ODIN_CAMERA_CPP
#define ODIN_CAMERA_CPP

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

	inline Camera::Camera(std::string Name) : Component(Name) {
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

	inline Camera::Camera(const Camera& other) : Component() {
		Copy(other);
	}
	
	inline Camera::Camera(const Camera&& other) : Component() {
		Move(std::move(other));
	}

	inline Camera::~Camera(void) {
		p_Clear();
	}

	inline Camera& Camera::Copy(const Camera& other) {
		Component::Copy(static_cast<Component>(other));
		m_needsUpdate = true;
		
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

	inline Camera& Camera::Move(const Camera&& other) {
		Component::Move(std::move(static_cast<Component>(other)));
		m_needsUpdate = true;
		
		m_width = std::move(other.m_width);
		m_height = std::move(other.m_height);
		m_invWidth = std::move(other.m_invWidth);
		m_invHeight = std::move(other.m_invHeight);

		background = std::move(other.background);

		m_aspect = std::move(other.m_aspect);
		m_fov = std::move(other.m_fov);

		m_near = std::move(other.m_near);
		m_far = std::move(other.m_far);

		m_orthographic = std::move(other.m_orthographic);
		m_orthographicSize = std::move(other.m_orthographicSize);

		m_minOrthographicSize = std::move(other.m_minOrthographicSize);
		m_maxOrthographicSize = std::move(other.m_maxOrthographicSize);
		
		return *this;
	}

	inline void Camera::p_Clear(void) {
		Component::p_Clear();
	}

	inline void Camera::p_Init(void) {

	}

	inline void Camera::p_Start(void) {

	}

	inline void Camera::p_Update(void) {
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

	inline void Camera::p_Sort(void) {
		p_order = m_active ? 0.0f : 1.0f;
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

	inline Camera& Camera::Set(int32 width, int32 height) {
		m_width = width;
		m_height = height;
		m_invWidth = 1.0f / m_width;
		m_invHeight = 1.0f / m_height;

		m_aspect = m_width / m_height;

		m_needsUpdate = true;
		return *this;
	}
	inline Camera& Camera::SetWidth(int32 width) {
		m_width = width;
		m_invWidth = 1.0f / m_width;
		m_aspect = m_width / m_height;

		m_needsUpdate = true;
		return *this;
	}
	inline Camera& Camera::SetHeight(int32 height) {
		m_height = height;
		m_invHeight = 1.0f / m_height;
		m_aspect = m_width / m_height;

		m_needsUpdate = true;
		return *this;
	}

	inline Camera& Camera::SetActive(bool value) {
		m_active = value;

		m_needsUpdate = true;
		return *this;
	}

	inline Camera& Camera::SetFov(float32 fov) {
		m_fov = fov;
		m_needsUpdate = true;
		return *this;
	}
	inline Camera& Camera::SetNear(float32 near) {
		m_near = near;
		m_needsUpdate = true;
		return *this;
	}
	inline Camera& Camera::SetFar(float32 far) {
		m_far = far;
		m_needsUpdate = true;
		return *this;
	}

	inline Camera& Camera::SetOrthographic(bool value) {
		m_orthographic = value;
		m_needsUpdate = true;
		return *this;
	}
	inline Camera& Camera::ToggleOrthographic(void) {
		m_orthographic = !m_orthographic;
		m_needsUpdate = true;
		return *this;
	}

	inline Camera& Camera::operator =(const Camera& other) {
		return Copy(other);
	}
	
	inline Camera& Camera::operator =(const Camera&& other) {
		return Move(std::move(other));
	}
}

#endif