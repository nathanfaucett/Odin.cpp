#ifndef _ODIN_H
#define _ODIN_H

#include <chrono>
#include <cmath>
#include <cfloat>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <string>
#include <functional>
#include <assert.h>

#include <SFML/Window.hpp>

/*===============================
 * Headers
 *===============================*/

#include "base/typedefs.hpp"

#include "base/os.hpp"
#include "base/time.hpp"
#include "base/util.hpp"

#include "base/array.h"
#include "base/object.h"

#include "math/mathf.hpp"
#include "math/color.h"
#include "math/mat2.h"
#include "math/mat3.h"
#include "math/mat32.h"
#include "math/mat4.h"
#include "math/quat.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/vec4.h"
#include "math/aabb2.h"
#include "math/aabb3.h"

#include "core/game/base_game.h"

#include "core/renderer/renderer.h"

#include "core/game_object.h"


/*===============================
 * Source Files
 *===============================*/

#include "base/array.cpp"
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
#include "math/aabb2.cpp"
#include "math/aabb3.cpp"

#include "core/game/base_game.cpp"

#include "core/renderer/renderer.cpp"

#include "core/game_object.cpp"

namespace Odin {

	void Init() {
		Mathf.Init();
	}
}

#endif