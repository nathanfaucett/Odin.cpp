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
			inline void p_Clear(void);

			inline void p_Init(void);
			inline void p_Start(void);
			inline void p_Update(void);

			inline void p_Sort(void);

		public:
			Mat4f projection, view;
			Colorf background;

			inline Camera(void);
			inline Camera(std::string Name);
			inline Camera(const Camera& other);
			inline Camera(const Camera&& other);
			inline ~Camera(void);

			inline virtual Camera& Copy(const Camera& other);
			inline virtual Camera& Move(const Camera&& other);

			inline Vec3f ToWorld(const Vec2f& v);
			inline Vec2f ToScreen(const Vec3f& v);

			inline Camera& Set(int32 width, int32 height);
			inline Camera& SetWidth(int32 width);
			inline Camera& SetHeight(int32 height);

			inline Camera& SetActive(bool value);
			
			inline Camera& SetFov(float32 fov);
			inline Camera& SetNear(float32 near);
			inline Camera& SetFar(float32 far);

			inline Camera& SetOrthographic(bool value);
			inline Camera& ToggleOrthographic(void);
			
			inline Camera& operator =(const Camera& other);
			inline Camera& operator =(const Camera&& other);
	};
}

#endif