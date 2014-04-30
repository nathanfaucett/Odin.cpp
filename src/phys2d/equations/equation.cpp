#ifndef PHYS2D_EQUATION_CPP
#define PHYS2D_EQUATION_CPP

namespace Odin {
	namespace Phys2D {

		inline Equation::Equation(void) {
			p_Constructor(NULL, NULL);
		}
		inline Equation::Equation(Body* bi, Body* bj) {
			p_Constructor(bi, bj);
		}
		inline Equation::Equation(Body* bi, Body* bj, float32 minForce, float32 maxForce) {
			p_Constructor(bi, bj, minForce, maxForce);
		}
		inline Equation::~Equation(void) {
			p_Deconstructor();
		}

		inline void Equation::p_Constructor(Body* Bi, Body* Bj, float32 MinForce, float32 MaxForce) {
			bi = Bi;
			bj = Bj;
			minForce = MinForce;
			maxForce = MaxForce;
			
			stiffness = 1000000;
			relaxation = 4;
		}
		inline void Equation::p_Deconstructor(void) {
			bi = NULL;
			bj = NULL;
		}
		
		inline void Equation::UpdateConstants(float32 h) {
			a = 4.0f / (h * (1.0f + 4.0f * relaxation));
			b = (4.0f * relaxation) / (1.0f + 4.0f * relaxation);
			epsilon = 4.0f / (h * h * stiffness * (1.0f + 4.0f * relaxation));
		}
	}
}

#endif