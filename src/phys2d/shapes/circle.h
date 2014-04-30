#ifndef PHYS2D_CIRCLE_H
#define PHYS2D_CIRCLE_H

namespace Odin {
	namespace Phys2D {
		
		class Circle : public Shape {
			
			private:
				float32 m_radius;

			protected:
				inline void p_Constructor(float32 Radius = 0.5f, float32 Density = 1.0f, float32 Friction = 0.5f, float32 Elasticity = 0.25f);
				inline void p_Deconstructor(void);

			public:

				inline explicit Circle(void);
				inline ~Circle(void);

				inline void SetRadius(float32 radius);
				inline float32 GetRadius(void);

				inline bool PointQuery(const Vec2f& point);
				inline Vec2f& Centroid(Vec2f& centroid);
				inline float32 Area(void);
				inline float32 Inertia(float32 mass);
				inline void Update(const Mat32f& parentMatrix);
		};
	}
}

#endif