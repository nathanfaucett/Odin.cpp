#ifndef ODIN_OPENGL_SHADER_CPP
#define ODIN_OPENGL_SHADER_CPP

namespace Odin {
	
	inline OpenGLShader::OpenGLShader(OpenGLRenderer* Renderer, std::string& vertex, std::string& fragment) {
		renderer = Renderer;
		program = renderer->CreateProgram(vertex, fragment);
		m_Parse();
	}
	inline OpenGLShader::~OpenGLShader(void) {
		renderer = NULL;
		uniforms.clear();
		attributes.clear();
	}
	
	inline void OpenGLShader::Update(std::string& Vertex, std::string& Fragment) {
		renderer->UpdateProgram(program, Vertex, Fragment);
		uniforms.clear();
		attributes.clear();
		m_Parse();
	}
	
	inline void OpenGLShader::m_AddAttribute(uint32 type, const char* name, int32 location) {
		Attribute* attribute = NULL;
		std::string strName = name;
		
		switch(type) {
			case GL_INT:
				attribute = static_cast<Attribute*>(new Attribute1i(this, strName, type, location));
				break;
			case GL_INT_VEC2:
				attribute = static_cast<Attribute*>(new Attribute2i(this, strName, type, location));
				break;
			case GL_INT_VEC3:
				attribute = static_cast<Attribute*>(new Attribute3i(this, strName, type, location));
				break;
			case GL_INT_VEC4:
				attribute = static_cast<Attribute*>(new Attribute4i(this, strName, type, location));
				break;
			case GL_FLOAT:
				attribute = static_cast<Attribute*>(new Attribute1f(this, strName, type, location));
				break;
			case GL_FLOAT_VEC2:
				attribute = static_cast<Attribute*>(new Attribute2f(this, strName, type, location));
				break;
			case GL_FLOAT_VEC3:
				attribute = static_cast<Attribute*>(new Attribute3f(this, strName, type, location));
				break;
			case GL_FLOAT_VEC4:
				attribute = static_cast<Attribute*>(new Attribute4f(this, strName, type, location));
				break;
			default:
				attribute = NULL;
		}
		
		if (attribute != NULL) attributes[name] = attribute;
	}
	inline void OpenGLShader::m_AddUnifrom(uint32 type, const char* name, int32 location) {
		Uniform* uniform = NULL;
		std::string strName = name;
		
		switch(type) {
			case GL_INT:
				uniform = static_cast<Uniform*>(new Uniform1i(this, strName, type, location));
				break;
			case GL_INT_VEC2:
				uniform = static_cast<Uniform*>(new Uniform2i(this, strName, type, location));
				break;
			case GL_INT_VEC3:
				uniform = static_cast<Uniform*>(new Uniform3i(this, strName, type, location));
				break;
			case GL_INT_VEC4:
				uniform = static_cast<Uniform*>(new Uniform4i(this, strName, type, location));
				break;
			case GL_FLOAT:
				uniform = static_cast<Uniform*>(new Uniform1f(this, strName, type, location));
				break;
			case GL_FLOAT_VEC2:
				uniform = static_cast<Uniform*>(new Uniform2f(this, strName, type, location));
				break;
			case GL_FLOAT_VEC3:
				uniform = static_cast<Uniform*>(new Uniform3f(this, strName, type, location));
				break;
			case GL_FLOAT_VEC4:
				uniform = static_cast<Uniform*>(new Uniform4f(this, strName, type, location));
				break;
			case GL_FLOAT_MAT2:
				uniform = static_cast<Uniform*>(new UniformMatrix2fv(this, strName, type, location));
				break;
			case GL_FLOAT_MAT3:
				uniform = static_cast<Uniform*>(new UniformMatrix3fv(this, strName, type, location));
				break;
			case GL_FLOAT_MAT4:
				uniform = static_cast<Uniform*>(new UniformMatrix4fv(this, strName, type, location));
				break;
			case GL_SAMPLER_2D:
				uniform = static_cast<Uniform*>(new UniformSampler2D(this, strName, type, location));
				break;
			case GL_SAMPLER_CUBE:
				uniform = static_cast<Uniform*>(new UniformSamplerCube(this, strName, type, location));
				break;
			default:
				uniform = NULL;
		}
		
		if (uniform != NULL) uniforms[name] = uniform;
	}
	inline void OpenGLShader::m_Parse(void) {
		int32 uniformsParams = -1,
			  attributesParams = -1,
			  i;

		glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniformsParams);
		glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &attributesParams);
		
		for (i = 0; i < uniformsParams; i++) {
			int32 length, size;
			uint32 type;
			char name[256];
			glGetActiveUniform(program, i, 256, &length, &size, &type, name);
			m_AddUnifrom(type, name, glGetUniformLocation(program, name));
		}
		
		for (i = 0; i < attributesParams; i++) {
			int32 length, size;
			uint32 type;
			char name[256];
			glGetActiveAttrib(program, i, 256, &length, &size, &type, name);
			m_AddAttribute(type, name, glGetAttribLocation(program, name));
		}
	}
}

#endif