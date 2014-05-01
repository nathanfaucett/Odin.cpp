#ifndef ODIN_H
#define ODIN_H

#include <GL/glew.h>

#include <SDL2/SDL.h>
#if OPENGL_ES
	#include <SDL2/SDL_opengles.h>
#else
	#include <SDL2/SDL_opengl.h>
#endif

#include <GL/glu.h>

#include "base/base.hpp"

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

	inline float32 Benchmark(std::function<void()> func, int32 times = 1000);
}

/*===============================
 * Headers
 *===============================*/

#include "mathf/mathf.hpp"
#include "phys2d/phys2d.h"

#include "core/components/component.h"
#include "core/components/transform.h"
#include "core/components/camera.h"
#include "core/components/sprite.h"

#include "core/game_object.h"
#include "core/scene.h"

#include "core/renderer/window.h"

#include "core/game/base_game.h"
#include "core/game/game.h"


/*===============================
 * Source Files
 *===============================*/

#include "core/components/component.cpp"
#include "core/components/transform.cpp"
#include "core/components/camera.cpp"
#include "core/components/sprite.cpp"

#include "core/game_object.cpp"
#include "core/scene.cpp"

#include "core/renderer/window.cpp"

#include "core/game/base_game.cpp"
#include "core/game/game.cpp"

#endif