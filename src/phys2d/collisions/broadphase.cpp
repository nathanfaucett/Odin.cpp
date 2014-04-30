#ifndef PHYS2D_BROADPHASE_CPP
#define PHYS2D_BROADPHASE_CPP

namespace Odin {
	namespace Phys2D {

		inline Broadphase::Broadphase(Space* space) {
			p_Constructor(space);
		}
		inline Broadphase::~Broadphase(void) {
			p_Deconstructor();
		}
		
		inline void Broadphase::p_Constructor(Space* space) {
			p_space = space;
		}
		inline void Broadphase::p_Deconstructor(void) {
			p_space = NULL;
			p_pairs.Clear();
		}
		
		inline bool Broadphase::BodyCheck(Body* bi, Body* bj) {
			
			if ((bi->IsStatic() || bi->IsKinematic()) && (bj->IsStatic() || bj->IsKinematic())) return false;
			if (bi->IsSleeping() && bj->IsSleeping()) return false;
			if ((bi->IsStatic() && bj->IsSleeping()) || (bj->IsStatic() && bi->IsSleeping())) return false;
			
			return bi->aabb.Intersects(bj->aabb);
		}
		inline bool Broadphase::ShapeCheck(Shape* si, Shape* sj) {

			if ((si->filterGroup & sj->filterMask) == 0 || (sj->filterGroup & si->filterMask) == 0) return false;

			return si->aabb.Intersects(sj->aabb);
		}
		
		inline Array<Shape*>& Broadphase::GetCollisionPairs(void) {
			
			for (uint32 i = 0, il = p_space->m_bodies.Length(); i < il; i++) {
				for (uint32 j = 0; j < i; j++) {
					Body* bi = p_space->m_bodies[i];
					Body* bj = p_space->m_bodies[j];
					
					if (BodyCheck(bi, bj)) {
						for (uint32 shapesk = bi->m_shapes.Length(), shapesl = bj->m_shapes.Length(), k = 0; k < shapesk; k++) {
							for (uint32 l = 0; l < shapesl; l++) {
								Shape* si = bi->m_shapes[k];
								Shape* sj = bj->m_shapes[l];
								
								if (ShapeCheck(si, sj)) {
									p_pairs.Push(si);
									p_pairs.Push(sj);
								}
							}
						}
					}
				}
			}
			
			return p_pairs;
		}
	}
}

#endif