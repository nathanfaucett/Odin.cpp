#ifndef PHYS2D_CIRCLE_CPP
#define PHYS2D_CIRCLE_CPP

namespace Odin {
	namespace Phys2D {
		inline Circle::Circle(void) : Shape() {
			p_Constructor();
		}
		inline Circle::~Circle(void) {
			p_Deconstructor();
		}
		
		inline void Circle::p_Constructor(float32 Radius, float32 Density, float32 Friction, float32 Elasticity) {
			p_shapeType = ShapeType::Circle;
			m_radius = Radius;
		}
		
		inline void Circle::p_Deconstructor(void) {
			Shape::p_Constructor();
		}
		
		inline void Circle::SetRadius(float32 radius) {
			m_radius = radius;
			p_ResetMassData();
		}
		inline float32 Circle::GetRadius(void) {
			return m_radius;
		}
		
		inline bool Circle::PointQuery(const Vec2f& point) {
			float32 dx = position.x - point.x,
					dy = position.y - point.y;

            return (dx * dx + dy * dy) <= m_radius * m_radius;
		}
		inline Vec2f& Circle::Centroid(Vec2f& centroid) {
			centroid = p_localPosition;
			
			return centroid;
		}
		inline float32 Circle::Area(void) {
			
			return Mathf.PI * (m_radius * m_radius);
		}
		inline float32 Circle::Inertia(float32 mass) {
			
			return mass * ((m_radius * m_radius * 0.5f) + p_localPosition.LengthSq());
		}
		inline void Circle::Update(const Mat32f& parentMatrix) {
			Shape::Update(parentMatrix);
			aabb.FromCenterSize(position, m_radius);
		}
	}
}

#endif