#ifndef ODIN_CPP
#define ODIN_CPP

#include "odin.h"

namespace Odin {

	inline void Init() {
		Mathf.Init();

		if (SDL_Init(
			SDL_INIT_TIMER |
			SDL_INIT_AUDIO |
			SDL_INIT_VIDEO |
			SDL_INIT_EVENTS |
			SDL_INIT_NOPARACHUTE
		) != 0) {
			SDLQuitError("SDL_Init");
		}
		SDLCheckError(__LINE__);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDLCheckError(__LINE__);
	}

	inline void Clear() {
		SDL_Quit();
	}

	inline void Log(std::string msg, int32 line) {
		#ifndef NDEBUG
		printf("%s", msg.c_str());

		if (line != -1) {
			printf(" + near line: %i", line);
		}

		printf("\n");
		#endif
	}
	inline void LogError(std::string msg, int32 line) {
		printf("Error: %s", msg.c_str());

		if (line != -1) {
			printf(" + near line: %i", line);
		}

		printf("\n");
	}

	inline void Delay(int16 s) {
		SDL_Delay(s * 1000);
	}
	inline void Delay(int32 s) {
		SDL_Delay(s * 1000);
	}
	inline void Delay(int64 s) {
		SDL_Delay(s * 1000);
	}
	inline void Delay(float32 s) {
		SDL_Delay(s * 1000.0f);
	}
	inline void Delay(float64 s) {
		SDL_Delay(s * 1000.0);
	}

	inline void SDLQuitError(std::string msg) {
		printf("%s Force Quit Error: %s\n", msg.c_str(), SDL_GetError());
		SDL_ClearError();
		Clear();
		exit(1);
	}

	inline void QuitError(std::string msg) {
		printf("Force Quit Error: %s\n", msg.c_str());
		Clear();
		exit(1);
	}

	inline void SDLCheckError(int32 line) {
		#ifndef NDEBUG
		const char* error = SDL_GetError();

		if (*error != '\0') {
			printf("SDL Error: %s", error);

			if (line != -1) {
				printf(" + near line: %i", line);
			}

			printf("\n");
			SDL_ClearError();
		}
		#endif
	}

	inline void GLCheckError(int32 line) {
		#ifndef NDEBUG
		GLenum error = glGetError();

		if (error != GL_NO_ERROR) {
			printf("GL Error: %s", gluErrorString(error));

			if (line != -1) {
				printf(" + near line: %i", line);
			}

			printf("\n");
		}
		#endif
	}

	inline float32 Benchmark(std::function<void()> func, int32 times) {
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