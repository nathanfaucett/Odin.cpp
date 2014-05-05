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
			inline void p_Init(void);
			inline void p_Start(void);
			inline void p_Clear(void);

			inline void p_Sort(void);

		public:
			bool autoUpdate;
			Mat4f projection, view;
			Colorf background;

			inline Camera(void);
			inline Camera(std::string name);
			inline Camera(const Camera& other);
			inline Camera(const Camera&& other);
			inline ~Camera(void);
			
			inline virtual Camera* Clone(void);
			inline virtual Camera& Copy(const Camera& other);
			inline virtual Camera& Move(const Camera&& other);
			
			inline void Update(void);

			inline Vec3f ToWorld(const Vec2f& v);
			inline Vec2f ToScreen(const Vec3f& v);

			inline Camera& Set(float32 width, float32 height);
			inline Camera& SetWidth(float32 width);
			inline float32 GetWidth(void);
			inline Camera& SetHeight(float32 height);
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
			
			inline Camera& operator =(const Camera& other);
			inline Camera& operator =(const Camera&& other);
	};
}

#endif