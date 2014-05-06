#ifndef ODIN_H
#define ODIN_H

#ifdef EMSCRIPTEN
	#include "emscripten.h"
#endif

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#if OPENGL_ES
	#include <SDL2/SDL_opengles.h>
#else
	#include <SDL2/SDL_opengl.h>
#endif

#include "core/core.hpp"

namespace Odin {

	inline void Init();
	inline void Clear();

	inline void Log(std::string msg, int32 line = -1);
	inline void LogError(std::string msg, int32 line = -1);

	inline void Delay(int16 s);
	inline void Delay(int32 s);
	inline void Delay(int64 s);
	inline void Delay(float32 s);
	inline void Delay(float64 s);

	inline void QuitError(std::string msg);
	inline void GlewQuitError(std::string msg);
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

#include "assets/asset.h"
#include "assets/texture.h"
#include "assets/assets.h"

#include "scene_graph/components/component.h"
#include "scene_graph/components/transform.h"
#include "scene_graph/components/camera.h"
#include "scene_graph/components/sprite.h"

#include "scene_graph/game_object.h"
#include "scene_graph/scene.h"

#include "renderer/window.h"
#include "renderer/opengl_renderer.h"
#include "renderer/renderer.h"

#include "game/base_game.h"
#include "game/game.h"


/*===============================
 * Source Files
 *===============================*/

#include "assets/asset.cpp"
#include "assets/texture.cpp"
#include "assets/assets.cpp"

#include "scene_graph/components/component.cpp"
#include "scene_graph/components/transform.cpp"
#include "scene_graph/components/camera.cpp"
#include "scene_graph/components/sprite.cpp"

#include "scene_graph/game_object.cpp"
#include "scene_graph/scene.cpp"

#include "renderer/window.cpp"
#include "renderer/opengl_renderer.cpp"
#include "renderer/renderer.cpp"

#include "game/base_game.cpp"
#include "game/game.cpp"

#endif