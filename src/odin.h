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

	inline std::pair<double, double> __RUN_BENCHMARK__(std::function<void()> func, uint32 times);
	inline void Benchmark(std::string name, std::function<void()> func, uint32 times = 100);
}

/*===============================
 * Headers
 *===============================*/

#include "mathf/mathf.hpp"
#include "phys2d/phys2d.h"

#include "input/input_button.hpp"
#include "input/input_buttons.hpp"
#include "input/input_touch.hpp"
#include "input/input_touches.hpp"
#include "input/input_axis.hpp"
#include "input/input_axes.hpp"
#include "input/input.hpp"

#include "config/game_config.hpp"
#include "game/window.h"

#include "assets/asset.h"
#include "assets/texture.h"
#include "assets/material.h"
#include "assets/mesh.h"
#include "assets/assets.h"

#include "scene_graph/components/component.h"
#include "scene_graph/components/transform.h"
#include "scene_graph/components/camera.h"
#include "scene_graph/components/mesh_filter.h"
#include "scene_graph/components/sprite.h"
#include "scene_graph/components/orbit_control.hpp"

#include "scene_graph/game_object.h"
#include "scene_graph/scene.h"

#include "renderer/opengl_renderer.h"
#include "renderer/opengl_shader/opengl_attributes.h"
#include "renderer/opengl_shader/opengl_uniforms.h"
#include "renderer/opengl_shader/opengl_shader.h"
#include "renderer/renderer.h"

#include "game/base_game.h"
#include "game/game.h"


/*===============================
 * Source Files
 *===============================*/

#include "assets/asset.cpp"
#include "assets/texture.cpp"
#include "assets/material.cpp"
#include "assets/mesh.cpp"
#include "assets/assets.cpp"

#include "game/window.cpp"

#include "scene_graph/components/component.cpp"
#include "scene_graph/components/transform.cpp"
#include "scene_graph/components/camera.cpp"
#include "scene_graph/components/mesh_filter.cpp"
#include "scene_graph/components/sprite.cpp"

#include "scene_graph/game_object.cpp"
#include "scene_graph/scene.cpp"

#include "renderer/opengl_renderer.cpp"
#include "renderer/opengl_shader/opengl_attributes.cpp"
#include "renderer/opengl_shader/opengl_uniforms.cpp"
#include "renderer/opengl_shader/opengl_shader.cpp"
#include "renderer/renderer.cpp"

#include "game/base_game.cpp"
#include "game/game.cpp"

#endif