#ifndef PHYS2D_H
#define PHYS2D_H

namespace Odin {
	namespace Phys2D {
		
	}
}


/*===============================
 * Headers
 *===============================*/

#include "enums.hpp"

#include "shapes/shape.h"
#include "shapes/circle.h"

#include "objects/body.h"

#include "equations/equation.h"
#include "equations/contact.h"

#include "collisions/broadphase.h"
#include "collisions/nearphase.h"

#include "world/space.h"

/*===============================
 * Source Files
 *===============================*/

#include "shapes/shape.cpp"
#include "shapes/circle.cpp"

#include "objects/body.cpp"

#include "equations/equation.cpp"
#include "equations/contact.cpp"

#include "collisions/broadphase.cpp"
#include "collisions/nearphase.cpp"

#include "world/space.cpp"

#endif