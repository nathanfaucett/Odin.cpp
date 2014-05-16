#ifndef ODIN_ORBIT_CONTROL_HPP
#define ODIN_ORBIT_CONTROL_HPP

namespace Odin {
	
	class OrbitControl : public Component {
		private:
			enum class MotionState : uint32 {
				None = 0, Rotate = 1, Pan = 2
			};
			
			MotionState m_state;
			float32 m_thetaDelta, m_phiDelta, m_scale;
			Vec3f m_pan, m_delta, m_panOffset;
			bool m_update;
			
			inline void m_Pan(void) {
				Transform* transform = GetComponent<Transform>();
				if (transform == NULL) return;
				
				Camera* camera = GetComponent<Camera>();
				if (camera == NULL) return;
				
				Mat4f& matrixWorld = transform->matrixWorld;
				Vec3f& position = transform->position;
				float32 targetDistance = 0.0f;
				
				m_panOffset = position - target;
				targetDistance = m_panOffset.Length();
				
				if (!camera->IsOrthographic()) {
					targetDistance *= tan(Mathf.ToRads(camera->GetFov() * 0.5f));
	
					m_panOffset.Set(matrixWorld[0], matrixWorld[1], matrixWorld[2]);
					m_panOffset *= -2.0f * m_delta.x * targetDistance * camera->GetInvWidth();
					m_pan += m_panOffset;
	
					m_panOffset.Set(matrixWorld[4], matrixWorld[5], matrixWorld[6]);
					m_panOffset *= 2.0f * m_delta.y * targetDistance * camera->GetInvHeight();
					m_pan += m_panOffset;
				} else {
					targetDistance *= camera->GetOrthographicSize() * 0.5f;
	
					m_panOffset.Set(matrixWorld[0], matrixWorld[1], matrixWorld[2]);
					m_panOffset *= -2.0f * m_delta.x * targetDistance * camera->GetInvWidth();
					m_pan += m_panOffset;
	
					m_panOffset.Set(matrixWorld[4], matrixWorld[5], matrixWorld[6]);
					m_panOffset *= 2.0f * m_delta.y * targetDistance * camera->GetInvHeight();
					m_pan += m_panOffset;
				}
			}
			inline void m_UpdateOrbit(void) {
				Transform* transform = GetComponent<Transform>();
				if (transform == NULL) return;
				
				Vec3f& position = transform->position;
				float32 theta = 0.0f, phi = 0.0f, radius = 0.0f;
	
				Vec3f offset = position - target;
				theta = Mathf.Atan2(offset.x, offset.y);
				phi = Mathf.Atan2(Mathf.Sqrt(offset.x * offset.x + offset.y * offset.y), offset.z);
	
				theta += m_thetaDelta;
				phi += m_phiDelta;
	
				phi = Mathf.Max(0.0f, Mathf.Min(Mathf.PI, phi));
				phi = Mathf.Max(Mathf.Epsilon, Mathf.Min(Mathf.PI - Mathf.Epsilon, phi));
	
				radius = offset.Length() * m_scale;
	
				target += m_pan;
	
				offset.x = radius * Mathf.Sin(phi) * Mathf.Sin(theta);
				offset.y = radius * Mathf.Sin(phi) * Mathf.Cos(theta);
				offset.z = radius * Mathf.Cos(phi);
	
				position = target + offset;
				transform->LookAt(target);
	
				m_scale = 1.0f;
				m_thetaDelta = 0.0f;
				m_phiDelta = 0.0f;
				m_pan.Set(0.0f, 0.0f, 0.0f);
				
				m_update = false;
			}
			
		protected:
			inline void p_Start(void) {
				Component::p_Start();
				
				m_UpdateOrbit();
			}

		public:
            float32 speed, zoomSpeed;
            bool allowZoom, allowPan, allowRotate;
            Vec3f target;
			
			inline OrbitControl(void) : Component() {
				speed = 64.0f;
				zoomSpeed = 2.0f;
				
				allowZoom = true;
				allowPan = true;
				allowRotate = true;
				
				m_thetaDelta = 0.0f;
				m_phiDelta = 0.0f;
				m_scale = 1.0f;
				
				m_update = false;
				m_state = MotionState::None;
			}
			inline OrbitControl(const OrbitControl&) = default;
			inline OrbitControl(OrbitControl&&) = default;
			inline ~OrbitControl(void) {
				Clear();
			}

			inline OrbitControl* Clone(void) {
				return &((new OrbitControl())->Copy(*this));
			}
			inline OrbitControl& Copy(const OrbitControl& other) {
				return *this;
			}
			
			inline void Update(void) {
				Camera* camera = GetComponent<Camera>();
				if (camera == NULL) return;
				float32 dt = Time.delta;
				
				if (Input.MouseButton(0) && allowRotate) {
					m_state = MotionState::Rotate;
				} else if (Input.MouseButton(1) && allowPan) {
					m_state = MotionState::Pan;
				} else {
					m_state = MotionState::None;
				}
			
				m_delta.x = -Input.mouseDelta.x * speed * dt;
				m_delta.y = -Input.mouseDelta.y * speed * dt;
				
				if (m_state == MotionState::Rotate) {
					m_thetaDelta += 2.0f * Mathf.PI * m_delta.x * camera->GetInvWidth();
					m_phiDelta -= 2.0f * Mathf.PI * m_delta.y * camera->GetInvHeight();
					
					m_update = true;
				} else if (m_state == MotionState::Pan) {
					m_Pan();
					m_update = true;
				}
				
				if (Input.mouseWheel > 0) {
					m_update = true;
					m_scale *= Mathf.Pow(0.95f, zoomSpeed);
				} else if (Input.mouseWheel < 0) {
					m_update = true;
					m_scale /= Mathf.Pow(0.95f, zoomSpeed);
				}
				
				if (m_update)  m_UpdateOrbit();
			}
			inline void Clear(void) {
				
			}
			
			inline OrbitControl& operator=(const OrbitControl&)& = default;
			inline OrbitControl& operator=(OrbitControl&&)& = default;
	};
}

#endif