#ifndef ODIN_OPENGL_SHADER_H
#define ODIN_OPENGL_SHADER_H

namespace Odin {
	
	class OpenGLShader{
		
		private:
			inline void m_AddAttribute(uint32 type, const char* name, int32 location);
			inline void m_AddUnifrom(uint32 type, const char* name, int32 location);
			inline void m_Parse(void);
			
		public:
			OpenGLRenderer* renderer;
			uint32 program;
			
			std::unordered_map<std::string, Uniform*> uniforms;
			std::unordered_map<std::string, Attribute*> attributes;
			
			inline OpenGLShader(OpenGLRenderer* Renderer, std::string& Vertex, std::string& Fragment);
			inline OpenGLShader(const OpenGLShader&) = default;
			inline OpenGLShader(OpenGLShader&&) = default;
			inline ~OpenGLShader(void);
			
			inline void Update(std::string& Vertex, std::string& Fragment);
			
			inline OpenGLShader& operator=(const OpenGLShader&)& = default;
			inline OpenGLShader& operator=(OpenGLShader&&)& = default;
			
	};
}

#endif