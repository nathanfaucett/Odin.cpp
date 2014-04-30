#ifndef PHYS2D_NEARPHASE_CPP
#define PHYS2D_NEARPHASE_CPP

namespace Odin {
	namespace Phys2D {

		inline Nearphase::Nearphase(Space* space) {
			p_Constructor(space);
		}
		inline Nearphase::~Nearphase(void) {
			p_Deconstructor();
		}
		
		inline void Nearphase::p_Constructor(Space* space) {
			m_space = space;
		}
		inline void Nearphase::p_Deconstructor(void) {
			m_space = NULL;
			m_contacts.Clear();
			m_contactPool.Clear();
		}
		
		inline void Nearphase::p_CreateContact(Shape* si, Shape* sj, Body* bi, Body* bj, float32 nx, float32 ny, float32 px, float32 py, float32 s) {
			Contact* contact = m_contactPool.Create();
			contact->bi = bi;
			contact->bj = bj;
			
			contact->e = Mathf.Min(si->elasticity, sj->elasticity);
			contact->u = Mathf.Min(si->friction, sj->friction);
			
			contact->normal.Set(nx, ny);
			contact->point.Set(px, py);
			contact->s = s;
			
			m_contacts.Push(contact);
		}
		
		inline void Nearphase::p_CheckContact(Shape* si, Shape* sj) {
			if (si->p_shapeType == ShapeType::Circle) {
				if (sj->p_shapeType == ShapeType::Circle) {
					p_CircleCircle(static_cast<Circle*>(si), static_cast<Circle*>(sj));
				}
			}
		}

		inline void Nearphase::p_CircleCircle(Circle* si, Circle* sj) {
			Vec2f& xi = si->position,
				   xj = sj->position;
				
			float32 dx = xj.x - xi.x,
					dy = xj.y - xi.y,
					dist = dx * dx + dy * dy,
					invDist, separation = 0.0f,
					ri = si->GetRadius(),
					rj = sj->GetRadius(),
					r = ri + rj,
					nx, ny;

            if (dist > r * r) return;

            if (dist < Mathf.Epsilon) {
                nx = 0.0f;
                ny = 1.0f;
                invDist = 0.0f;
                separation = -r;
            } else {
                dist = sqrtf(dist);
                invDist = 1.0f / dist;

                nx = dx * invDist;
                ny = dy * invDist;

                separation = dist - r;
            }
			
            p_CreateContact(
                si,
                sj,
                si->p_body,
                sj->p_body,
                nx,
                ny,
                xj.x - rj * nx,
                xj.y - rj * ny,
                separation
            );
		}
		
		inline Array<Contact*>& Nearphase::GetCollisions(Array<Shape*>& collisionPairs) {
			m_contactPool.PoolAll();
			
			for (uint32 i = 0, il = collisionPairs.Length(); i < il; i += 2) {
				p_CheckContact(collisionPairs[i], collisionPairs[i + 1]);
			}
			
			return m_contacts;
		}
	}
}

#endif