#ifndef PHYS2D_SPACE_CPP
#define PHYS2D_SPACE_CPP

namespace Odin {
	namespace Phys2D {
		
		inline Space::Space(void) {
			p_Constructor();
		}
		inline Space::~Space(void) {
			p_Deconstructor();
		}
		
		inline void Space::p_Constructor(void) {
			m_broadphase = new Broadphase(this);
			m_nearphase = new Nearphase(this);
			
			useGravity = true;
			gravity.Set(0.0f, -9.801f);
		}
		inline void Space::p_Deconstructor(void) {
			delete m_broadphase;
			delete m_nearphase;
			m_bodies.Clear();
		}

		inline void Space::AddBody(Body* body) {
			int32 index = m_bodies.IndexOf(body);
			
			if (index == -1) {
				m_bodies.Push(body);
				body->m_space = this;
				
				body->p_ResetMassData();
			}
		}
		inline void Space::RemoveBody(Body* body) {
			int32 index = m_bodies.IndexOf(body);
			
			if (index != -1) {
				m_bodies.Splice(index, 1);
				body->m_space = NULL;
				
				body->p_ResetMassData();
			}
		}
		
		inline void Space::Step(float32 dt) {
			uint32 numBodies = m_bodies.Length(), i;
			
			m_time += dt;
			
			if (useGravity) {
				i = numBodies;
				while (i--) {
					Body* body = m_bodies[i];
					if (!body->IsDynamic()) continue;
					
					body->force += gravity * body->m_mass;
				}
			}
			
			Array<Shape*>& collisionPairs = m_broadphase->GetCollisionPairs();
			Array<Contact*>& contacts = m_nearphase->GetCollisions(collisionPairs);
			
			i = numBodies;
			while (i--) m_bodies[i]->Update(dt);
		}
	}
}

#endif