#ifndef PHYS2D_CONTACT_CPP
#define PHYS2D_CONTACT_CPP

namespace Odin {
	namespace Phys2D {
		
		inline Contact::Contact(void) : Equation() {
			p_Constructor(NULL, NULL);
		}
		inline Contact::Contact(Body* bi, Body* bj) : Equation(bi, bj, 0.0f, MAX_FLOAT32) {
			p_Constructor(bi, bj);
		}
		inline Contact::~Contact(void) {
			p_Deconstructor();
		}

		inline void Contact::p_Constructor(Body* bi, Body* bj) {
			e = 0.5f;
			u = 0.25f;
			s = 0.0f;
		}
		inline void Contact::p_Deconstructor(void) {
			Equation::p_Deconstructor();
		}
	}
}

#endif