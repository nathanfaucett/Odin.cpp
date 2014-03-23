#ifndef _ODIN_H_
#define _ODIN_H_

/*===============================
 * Lib
 *===============================*/

#include <chrono>
#include <cmath>
#include <climits>
#include <cfloat>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <string>
#include <functional>
#include <assert.h>
#include <unordered_map>

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

#include "core/renderer/renderer.h"

#include "core/game/base_game.h"

#include "core/components/component.h"
#include "core/components/transform.h"

#include "core/game_object.h"
#include "core/scene.h"


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

#include "core/renderer/renderer.cpp"

#include "core/game/base_game.cpp"

#include "core/components/component.cpp"
#include "core/components/transform.cpp"

#include "core/game_object.cpp"
#include "core/scene.cpp"


namespace Odin {

	inline void Init() {
		Mathf.Init();
	}

	inline float32 Benchmark(std::function<void()> func, int32 times = 1000) {
		float32 start = 0.0f, avg = 0.0f,
		        d = 1.0f / float32(times);

		for (int32 i = 0; i < times; i++) {
			start = Time.Now();
			func();
			avg += Time.Now() - start;
		}

		return (avg * d);
	}
}

#endif