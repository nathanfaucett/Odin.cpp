#ifndef ODIN_CAMERA_H
#define ODIN_CAMERA_H

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

		public:
			bool autoUpdate;
			Mat4f projection, view;
			Colorf background;

			inline Camera(void);
			inline Camera(const Camera&) = default;
			inline Camera(Camera&&) = default;
			inline ~Camera(void);
			
			inline Camera* Clone(void);
			inline Camera& Copy(const Camera& other);
			
			inline void Update(void);
			inline void Clear(void);

			inline Vec3f ToWorld(const Vec2f& v);
			inline Vec2f ToScreen(const Vec3f& v);

			inline Camera& Set(float32 width, float32 height);
			inline Camera& SetWidth(float32 width);
			inline float32 GetWidth(void);
			inline float32 GetInvWidth(void);
			inline Camera& SetHeight(float32 height);
			inline float32 GetInvHeight(void);
			inline float32 GetHeight(void);
			inline float32 GetAspect(void);

			inline Camera& SetActive(bool value);
			inline bool IsActive(void);
			
			inline Camera& SetFov(float32 fov);
			inline float32 GetFov(void);
			inline Camera& SetNear(float32 near);
			inline float32 GetNear(void);
			inline Camera& SetFar(float32 far);
			inline float32 GetFar(void);

			inline Camera& SetOrthographic(bool value);
			inline bool IsOrthographic(void);
			inline Camera& ToggleOrthographic(void);
			
			inline Camera& SetOrthographicSize(float32 orthographicSize);
			inline float32 GetOrthographicSize(void);
			
			inline Camera& operator=(const Camera&)& = default;
			inline Camera& operator=(Camera&&)& = default;
	};
}

#endif