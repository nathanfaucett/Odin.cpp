#ifndef PHYS2D_BROADPHASE_H
#define PHYS2D_BROADPHASE_H

namespace Odin {
	namespace Phys2D {
		
		class Broadphase {
			
			private:
				
			protected:
				Array<Shape*> p_pairs;
				Space* p_space;
				
				inline void p_Constructor(Space* space);
				inline void p_Deconstructor(void);
	
			public:
	
				inline Broadphase(Space* space);
				inline ~Broadphase(void);
				
				inline bool BodyCheck(Body* bi, Body* bj);
				inline bool ShapeCheck(Shape* si, Shape* sj);
				
				inline Array<Shape*>& GetCollisionPairs(void);
		};
	}
}

#endif