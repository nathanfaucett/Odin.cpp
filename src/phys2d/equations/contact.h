#ifndef PHYS2D_CONTACT_H
#define PHYS2D_CONTACT_H

namespace Odin {
	namespace Phys2D {
		
		class Contact : public Equation {
			
			private:
				
			protected:
				inline void p_Constructor(Body* bi, Body* bj);
				inline void p_Deconstructor(void);
	
			public:
				Vec2f point, normal;
				float32 e, u, s;
				
				inline Contact(void);
				inline Contact(Body* bi, Body* bj);
				inline ~Contact(void);
		};
	}
}

#endif