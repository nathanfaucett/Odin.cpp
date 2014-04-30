#ifndef PHYS2D_CPP
#define PHYS2D_CPP

namespace Odin {
	namespace Phys2D {
		
		enum class ShapeType : uint32 {
			None = 1 << 0, Circle = 1 << 1,  Convex = 1 << 2, Capsule = 1 << 3, Particle = 1 << 4
		};
		
		enum class MotionState : uint32{
			Dynamic = 1 << 0, Kinematic = 1 << 1, Static = 1 << 2
		};
		
		enum class SleepState : uint32{
			Awake = 1 << 0, Sleepy = 1 << 1, Sleeping = 1 << 2
		};
	}
}

#endif