#ifndef PHYS2D_EQUATION_H
#define PHYS2D_EQUATION_H

namespace Odin {
	namespace Phys2D {
		
		class Equation {
			
			private:
				
			protected:
				inline virtual void p_Constructor(Body* bi, Body* bj, float32 minForce = -MAX_FLOAT32, float32 maxForce = MAX_FLOAT32);
				inline virtual void p_Deconstructor(void);
	
			public:
				Body* bi;
				Body* bj;
				float32 minForce, maxForce,
						stiffness, relaxation,
						a, b, epsilon;
				
				inline Equation(void);
				inline Equation(Body* bi, Body* bj);
				inline Equation(Body* bi, Body* bj, float32 minForce = -MAX_FLOAT32, float32 maxForce = MAX_FLOAT32);
				inline ~Equation(void);
				
				inline void UpdateConstants(float32 h = 1.0f / 60.0f);
		};
	}
}

#endif