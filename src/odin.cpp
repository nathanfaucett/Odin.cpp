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
		SDL_Delay(static_cast<uint32>(abs(s) * 1000));
	}
	inline void Delay(int32 s) {
		SDL_Delay(static_cast<uint32>(abs(s) * 1000));
	}
	inline void Delay(int64 s) {
		SDL_Delay(static_cast<uint32>(abs(s) * 1000));
	}
	inline void Delay(float32 s) {
		SDL_Delay(static_cast<uint32>(fabs(s) * 1000));
	}
	inline void Delay(float64 s) {
		SDL_Delay(static_cast<uint32>(fabs(s) * 1000));
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

	
	inline std::pair<double, double> __RUN_BENCHMARK__(std::function<void()> func, uint32 times) {
		float64 start = 0.0,
				time = 0.0;

		for (uint32 j = 0; j < times; j++) {
			start = Time.Now64();
			func();
			time += Time.Now64() - start;
		}
		
        return std::make_pair((times / time), (time / times));
	}
	inline void Benchmark(std::string name, std::function<void()> func, uint32 times) {
		float64 ops_sec = 0.0,
				avg_time = 0.0;

		for (uint32 j = 0; j < times; j++) {
			std::pair<double, double> values = __RUN_BENCHMARK__(func, times);
			ops_sec += values.first;
			avg_time += values.second;
		}
		
		std::cout << std::endl << "===== Benchmark =====" << std::endl << name << ":" << std::endl;
        std::cout << "\t" << (ops_sec / times) << "(ops/sec)" << std::endl;
		std::cout << "\t" << (avg_time / times) << "(average time/call)" << std::endl;
		std::cout << "===== Benchmark =====" << std::endl << std::endl;
	}
}

#endif