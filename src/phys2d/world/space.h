#ifndef PHYS2D_SPACE_H
#define PHYS2D_SPACE_H

namespace Odin {
	namespace Phys2D {
		
		class Space {
			
			private:
				friend class Broadphase;
				friend class Nearphase;
				
				Array<Body*> m_bodies;
				float32 m_time;
				
				Broadphase* m_broadphase;
				Nearphase* m_nearphase;
				
			protected:
				inline void p_Constructor(void);
				inline void p_Deconstructor(void);
	
			public:
				Vec2f gravity;
				bool useGravity;
	
				inline Space(void);
				inline ~Space(void);
				
				inline void AddBody(Body* body);
				inline void RemoveBody(Body* body);
				
				inline void Step(float32 dt = 1.0f / 60.0f);
		};
	}
}

#endif