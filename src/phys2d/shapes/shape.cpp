#ifndef PHYS2D_SHAPE_CPP
#define PHYS2D_SHAPE_CPP

namespace Odin {
	namespace Phys2D {
		
		inline Shape::Shape(void) {
			p_Constructor();
		}
		inline Shape::~Shape(void) {
			p_Deconstructor();
		}
		
		inline void Shape::p_Constructor(float32 Density, float32 Friction, float32 Elasticity) {
			p_shapeType = ShapeType::None;
			
			p_body = NULL;
			m_density = Density;
			friction = Friction;
			elasticity = Elasticity;
			filterGroup = 1;
			filterMask = 1;
		}
		
		inline void Shape::p_Deconstructor(void) {
			p_body = NULL;
		}
		
		inline bool Shape::PointQuery(const Vec2f& point) {
            return position == point;
		}
		inline Vec2f& Shape::Centroid(Vec2f& centroid) {
			return centroid.Set(0.0f, 0.0f);
		}
		inline float32 Shape::Area(void) {
			return 0.0f;
		}
		inline float32 Shape::Inertia(float32 mass) {
			return 0.0f;
		}
		inline void Shape::Update(const Mat32f& parentMatrix) {
			matrix.Compose(p_localPosition, p_localRotation);
			Mat32Mul<float32>(parentMatrix, matrix, matrixWorld);
			
			matrixWorld.GetPosition(position);
			matrixWorld.GetRotation(rotation);
		}
		
		inline void Shape::p_ResetMassData(void) {
			if (p_body != NULL) {
				p_body->p_ResetMassData();
			}
		}
		
		inline void Shape::SetDensity(float32 density) {
			m_density = density;
			p_ResetMassData();
		}
		inline float32 Shape::GetDensity(void) {
			return m_density;
		}
		
		inline void Shape::SetLocalPosition(const Vec2f& position) {
			p_localPosition = position;
			p_ResetMassData();
		}
		inline Vec2f Shape::GetLocalPosition(void) {
			return Vec2f(p_localPosition);
		}
		
		inline void Shape::SetLocalRotation(float32 rotation) {
			p_localRotation = rotation;
			p_ResetMassData();
		}
		inline float32 Shape::GetLocalRotation(void) {
			return p_localRotation;
		}
	}
}

#endif