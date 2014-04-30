#ifndef PHYS2D_BODY_H
#define PHYS2D_BODY_H

namespace Odin {
	namespace Phys2D {
		
		class Space;
		
		class Body {
			
			private:
				friend class Shape;
				friend class Space;
				friend class Broadphase;
				friend class Nearphase;
				
				Array<Shape*> m_shapes;
				float32 m_mass, m_invMass;
				float32 m_inertia, m_invInertia;

				bool m_allowSleep;
	
				Space* m_space;
	
				MotionState m_motionState;
				SleepState m_sleepState;
	
				void* m_userData;
			
			protected:
				inline void p_Constructor(float32 LinearDamping = 0.01f, float32 AngularDamping = 0.01f);
				inline void p_ResetMassData(void);
	
			public:
				Vec2f position, velocity, force;
				float32 rotation, angularVelocity, torque;
				Mat32f matrix;

				AABB2f aabb;
				float32 linearDamping, angularDamping;
				
				inline Body(void);
				inline ~Body(void);
				
				inline void Update(float32 dt = 1.0f / 60.0f);
	
				inline void AddShape(Shape* shape);
				inline void RemoveShape(Shape* shape);
	
				inline void SetMotionState(MotionState motionState);
				
				inline bool IsAwake(void);
				inline bool IsSleepy(void);
				inline bool IsSleeping(void);
				
				inline bool IsStatic(void);
				inline bool IsDynamic(void);
				inline bool IsKinematic(void);
				
				inline void Wake(void);
				inline void Sleep(void);
	
				inline void SetMass(float32 mass = 1.0f);
				inline float32 GetMass(void);
	
				inline void SetInertia(float32 inertia = 1.0f);
				inline float32 GetInertia(void);
	
				inline void SetUserData(void* data);
				inline void* GetUserData(void);
		};
	}
}

#endif