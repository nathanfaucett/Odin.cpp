#ifndef ODIN_H
#define ODIN_H

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cfloat>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "base/os.h"
#include "base/object.h"
#include "base/time.h"
#include "base/util.h"

#include "math/mathf.h"
#include "math/color.h"
#include "math/mat2.h"
#include "math/mat3.h"
#include "math/mat32.h"
#include "math/mat4.h"
#include "math/quat.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec4.h"


#include "base/object.cpp"

#include "math/color.cpp"
#include "math/mat2.cpp"
#include "math/mat3.cpp"
#include "math/mat32.cpp"
#include "math/mat4.cpp"
#include "math/quat.cpp"
#include "math/vec2.cpp"
#include "math/vec3.cpp"
#include "math/vec4.cpp"

#include "core/components/component.h"

#include "core/game_object.h"
#include "core/scene.h"

#include "core/components/component.cpp"

namespace Odin {

	void init() {
		std::srand(std::time(0));
		std::cout.precision(16);
	}
}

#endif