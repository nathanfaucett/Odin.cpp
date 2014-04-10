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

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
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
		uint32 error = glGetError();

		if (error != GL_NO_ERROR) {
			printf("GL Error: %s", gluErrorString(error));

			if (line != -1) {
				printf(" + near line: %i", line);
			}

			printf("\n");
		}

#endif
	}

	inline uint32 CreateShader(uint32 ShaderType, const std::string& sourceString) {
		uint32 shader = glCreateShader(ShaderType);
		const char* source = sourceString.c_str();
		glShaderSource(shader, 1, &source, NULL);

		glCompileShader(shader);

		int32 status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

		if (status == GL_FALSE) {
			int32 infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar* strInfoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

			const char* strShaderType = NULL;

			if (ShaderType == GL_VERTEX_SHADER) {
				strShaderType = "vertex";

			} else if (ShaderType == GL_GEOMETRY_SHADER) {
				strShaderType = "geometry";

			} else if (ShaderType == GL_FRAGMENT_SHADER) {
				strShaderType = "fragment";
			}

			printf(" Compile failure in: %s shader: %s\n", strShaderType, strInfoLog);
			delete[] strInfoLog;
		}

		return shader;
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