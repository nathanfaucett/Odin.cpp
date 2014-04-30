#ifndef PHYS2D_NEARPHASE_H
#define PHYS2D_NEARPHASE_H

namespace Odin {
	namespace Phys2D {

		class Nearphase {

			private:
				ObjectPool<Contact> m_contactPool;
				Array<Contact*> m_contacts;
				Space* m_space;

			protected:
				inline void p_Constructor(Space* space);
				inline void p_Deconstructor(void);

				inline void p_CreateContact(Shape* si, Shape* sj, Body* bi, Body* bj, float32 nx, float32 ny, float32 px, float32 py, float32 s);
				inline void p_CheckContact(Shape* si, Shape* sj);
				
				inline void p_CircleCircle(Circle* si, Circle* sj);

			public:

				inline Nearphase(Space* space);
				inline ~Nearphase(void);

				inline Array<Contact*>& GetCollisions(Array<Shape*>& collisionPairs);
		};
	}
}

#endif