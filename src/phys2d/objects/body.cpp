#ifndef PHYS2D_BODY_CPP
#define PHYS2D_BODY_CPP

namespace Odin {
	namespace Phys2D {
		
		inline Body::Body(void) {
			p_Constructor();
		}
		inline Body::~Body(void) {
			m_shapes.Clear();
			m_space = NULL;
		}
		
		inline void Body::p_Constructor(float32 LinearDamping, float32 AngularDamping) {
			linearDamping = LinearDamping;
			angularDamping = AngularDamping;
			
			m_sleepState = SleepState::Awake;
			m_motionState = MotionState::Static;
			
			m_space = NULL;
		}
		
		inline void Body::p_ResetMassData(void) {
			uint32 i = m_shapes.Length();
			Vec2f totalCentroid, centroid;
			float32 totalMass, totalInertia;
			
			while(i--) {
				Shape* shape = m_shapes[i];
				
				shape->Centroid(centroid);
				float32 mass = shape->Area() * shape->m_density;
				float32 inertia = shape->Inertia(mass);
				
				centroid *= mass;
				totalCentroid += centroid;
                totalMass += mass;
                totalInertia += inertia;
			}
			
			totalCentroid /= totalMass;
			SetMass(totalMass);
			SetInertia(totalInertia - totalMass * totalCentroid.LengthSq());
		}

		inline void Body::Update(float32 dt) {
			if (m_motionState == MotionState::Static) return;
			
			velocity += force * m_invMass * dt;
			velocity *= Mathf.Pow(1.0f - linearDamping, dt);
			
			angularVelocity += torque * m_invInertia * dt;
			angularVelocity *= Mathf.Pow(1.0f - angularDamping, dt);
			
			force.Set(0.0f, 0.0f);
			torque = 0.0f;
			
			if (m_sleepState != SleepState::Sleeping) {
				position += velocity * dt;
				rotation += angularVelocity * dt;
				
				matrix.Compose(position, rotation);
				aabb.Clear();
				
                for (uint32 i = 0, il = m_shapes.Length(); i < il; i++) {
                    Shape* shape = m_shapes[i];
                    shape->Update(matrix);
                    aabb += shape->aabb;
                }
			}
		}
	
		inline void Body::AddShape(Shape* shape) {
			int32 index = m_shapes.IndexOf(shape);
			
			if (index == -1) {
				m_shapes.Push(shape);
				shape->p_body = this;
				
				if (m_space == NULL) {
					p_ResetMassData();
				}
				aabb.Clear();
                for (uint32 i = 0, il = m_shapes.Length(); i < il; i++) {
                    Shape* shape = m_shapes[i];
                    shape->Update(matrix);
                    aabb += shape->aabb;
                }
			}
		}
		inline void Body::RemoveShape(Shape* shape) {
			int32 index = m_shapes.IndexOf(shape);
			
			if (index != -1) {
				m_shapes.Splice(index, 1);
				shape->p_body = NULL;
				
				if (m_space == NULL) {
					p_ResetMassData();
				}
				aabb.Clear();
                for (uint32 i = 0, il = m_shapes.Length(); i < il; i++) {
                    Shape* shape = m_shapes[i];
                    shape->Update(matrix);
                    aabb += shape->aabb;
                }
			}
		}

		inline void Body::SetMotionState(MotionState motionState) {
			if (m_motionState == motionState) return;
			
			m_motionState = motionState;
			
			velocity.Set(0.0f, 0.0f);
			force.Set(0.0f, 0.0f);
			
			angularVelocity = 0.0f;
			torque = 0.0f;
			
			Wake();
		}
		
		inline bool Body::IsAwake(void) {
			return m_sleepState == SleepState::Awake;
		}
		inline bool Body::IsSleepy(void) {
			return m_sleepState == SleepState::Sleepy;
		}
		inline bool Body::IsSleeping(void) {
			return m_sleepState == SleepState::Sleeping;
		}
		
		inline bool Body::IsStatic(void) {
			return m_motionState == MotionState::Static;
		}
		inline bool Body::IsDynamic(void) {
			return m_motionState == MotionState::Dynamic;
		}
		inline bool Body::IsKinematic(void) {
			return m_motionState == MotionState::Kinematic;
		}
		
		inline void Body::Wake(void) {
			if (m_sleepState == SleepState::Awake) return;
			m_sleepState = SleepState::Awake;
		}
		inline void Body::Sleep(void) {
			if (m_sleepState == SleepState::Sleeping) return;
			m_sleepState = SleepState::Sleeping;
		}
	
		inline void Body::SetUserData(void* data) {
			m_userData = data;
		}
		inline void* Body::GetUserData(void) {
			return m_userData;
		}
		
		inline void Body::SetMass(float32 mass) {
			m_mass = mass;
			m_invMass = 1.0f / mass;
		}
		inline float32 Body::GetMass(void) {
			return m_mass;
		}
		
		inline void Body::SetInertia(float32 inertia) {
			m_inertia = inertia;
			m_invInertia = 1.0f / inertia;
		}
		inline float32 Body::GetInertia(void) {
			return m_inertia;
		}
	}
}

#endif