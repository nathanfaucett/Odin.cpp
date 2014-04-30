#ifndef PHYS2D_SHAPE_H
#define PHYS2D_SHAPE_H

namespace Odin {
	namespace Phys2D {
		
		class Body;
		class Broadphase;
		class Nearphase;
		
		class Shape {
			
			private:
				friend class Body;
				friend class Broadphase;
				friend class Nearphase;
				
				float32 m_density;
	
			protected:
				Vec2f p_localPosition;
				float32 p_localRotation;
				ShapeType p_shapeType;
				Body* p_body;
				
				inline virtual void p_Constructor(float32 Density = 1.0f, float32 Friction = 0.5f, float32 Elasticity = 0.25f);
				inline virtual void p_Deconstructor(void);
				inline void p_ResetMassData(void);
	
			public:
				Vec2f position;
				float32 rotation;
				Mat32f matrix, matrixWorld;
				
				AABB2f aabb;
				float32 friction, elasticity;
				
				bool isTrigger;
				uint32 filterMask, filterGroup;
				
				inline explicit Shape(void);
				inline ~Shape(void);
				
				inline void SetDensity(float32 density);
				inline float32 GetDensity(void);
				
				inline void SetLocalPosition(const Vec2f& position);
				inline Vec2f GetLocalPosition(void);
				
				inline void SetLocalRotation(float32 rotation);
				inline float32 GetLocalRotation(void);
				
				inline virtual bool PointQuery(const Vec2f& point);
				inline virtual Vec2f& Centroid(Vec2f& centroid);
				inline virtual float32 Area(void);
				inline virtual float32 Inertia(float32 mass);
				inline virtual void Update(const Mat32f& parentMatrix);
		};
	}
}

#endif