#ifndef ODIN_H
#define ODIN_H

/*===============================
 * Lib
 *===============================*/

#include <iostream>
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

/*===============================
 * Base
 *===============================*/

#include "base/typedefs.hpp"

#include "base/os.hpp"
#include "base/time.hpp"
#include "base/util.hpp"

#include <GL/glew.h>

#ifdef WINDOWS
#include <SDL.h>
#include <SDL_opengl.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#endif

#include <GL/glu.h>

namespace Odin {

	inline void Init();
	inline void Clear();

	inline void Log(std::string msg, int32 line = -1);

	inline void Delay(int16 s);
	inline void Delay(int32 s);
	inline void Delay(int64 s);
	inline void Delay(float32 s);
	inline void Delay(float64 s);

	inline void SDLQuitError(std::string msg);
	inline void SDLCheckError(int32 line = -1);

	inline void GLCheckError(int32 line = -1);

	inline uint32 CreateShader(uint32 ShaderType, const std::string& sourceString);

	inline float32 Benchmark(std::function<void()> func, int32 times = 1000);
}

/*===============================
 * Headers
 *===============================*/

#include "base/enums.hpp"
#include "base/array.h"
#include "base/object.h"
#include "base/window.h"

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

#include "core/components/component.h"
#include "core/components/transform.h"
#include "core/components/camera.h"
#include "core/components/sprite.h"

#include "core/game_object.h"
#include "core/scene.h"

#include "core/renderer/renderer.h"

#include "core/game/base_game.h"
#include "core/game/game.h"


/*===============================
 * Source Files
 *===============================*/

#include "base/array.cpp"
#include "base/object.cpp"
#include "base/window.cpp"

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

#include "core/components/component.cpp"
#include "core/components/transform.cpp"
#include "core/components/camera.cpp"
#include "core/components/sprite.cpp"

#include "core/game_object.cpp"
#include "core/scene.cpp"

#include "core/renderer/renderer.cpp"

#include "core/game/base_game.cpp"
#include "core/game/game.cpp"

#endif