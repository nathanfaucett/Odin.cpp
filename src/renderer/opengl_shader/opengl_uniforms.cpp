#ifndef ODIN_OPENGL_UNIFORMS_CPP
#define ODIN_OPENGL_UNIFORMS_CPP

namespace Odin {

	inline Uniform::Uniform(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) {
		shader = Shader;
		name = Name;
		type = Type;
		location = Location;
	}
	inline Uniform::~Uniform(void) {
		shader = NULL;
	}
	inline void Uniform::Set(void) {
		
	}

	inline Uniform1i::Uniform1i(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Uniform(Shader, Name, Type, Location) {}
	inline Uniform1i::~Uniform1i(void) {}
	inline void Uniform1i::Set(int32 value) {
		if (shader->renderer->GetProgramForce() || m_value != value) {
			glUniform1i(location, value);
			m_value = value;
		}
	}
	
	inline Uniform2i::Uniform2i(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Uniform(Shader, Name, Type, Location) {}
	inline Uniform2i::~Uniform2i(void) {}
	inline void Uniform2i::Set(Vec2i& value) {
		if (shader->renderer->GetProgramForce() || m_value != value) {
			glUniform2i(location, value.x, value.y);
			m_value = value;
		}
	}
	
	inline Uniform3i::Uniform3i(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Uniform(Shader, Name, Type, Location) {}
	inline Uniform3i::~Uniform3i(void) {}
	inline void Uniform3i::Set(Vec3i& value) {
		if (shader->renderer->GetProgramForce() || m_value != value) {
			glUniform3i(location, value.x, value.y, value.z);
			m_value = value;
		}
	}
	
	inline Uniform4i::Uniform4i(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Uniform(Shader, Name, Type, Location) {}
	inline Uniform4i::~Uniform4i(void) {}
	inline void Uniform4i::Set(Vec4i& value) {
		if (shader->renderer->GetProgramForce() || m_value != value) {
			glUniform4i(location, value.x, value.y, value.z, value.w);
			m_value = value;
		}
	}

	inline Uniform1f::Uniform1f(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Uniform(Shader, Name, Type, Location) {}
	inline Uniform1f::~Uniform1f(void) {}
	inline void Uniform1f::Set(float32 value) {
		if (shader->renderer->GetProgramForce() || m_value != value) {
			glUniform1f(location, value);
			m_value = value;
		}
	}
	
	inline Uniform2f::Uniform2f(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Uniform(Shader, Name, Type, Location) {}
	inline Uniform2f::~Uniform2f(void) {}
	inline void Uniform2f::Set(Vec2f& value) {
		if (shader->renderer->GetProgramForce() || m_value != value) {
			glUniform2f(location, value.x, value.y);
			m_value = value;
		}
	}
	
	inline Uniform3f::Uniform3f(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Uniform(Shader, Name, Type, Location) {}
	inline Uniform3f::~Uniform3f(void) {}
	inline void Uniform3f::Set(Vec3f& value) {
		if (shader->renderer->GetProgramForce() || m_value != value) {
			glUniform3f(location, value.x, value.y, value.z);
			m_value = value;
		}
	}
	
	inline Uniform4f::Uniform4f(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Uniform(Shader, Name, Type, Location) {}
	inline Uniform4f::~Uniform4f(void) {}
	inline void Uniform4f::Set(Vec4f& value) {
		if (shader->renderer->GetProgramForce() || m_value != value) {
			glUniform4f(location, value.x, value.y, value.z, value.w);
			m_value = value;
		}
	}
	
	inline UniformMatrix2fv::UniformMatrix2fv(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Uniform(Shader, Name, Type, Location) {}
	inline UniformMatrix2fv::~UniformMatrix2fv(void) {}
	inline void UniformMatrix2fv::Set(Mat2f& value) {
		if (shader->renderer->GetProgramForce() || m_value != value) {
			glUniformMatrix2fv(location, 1, false, value.GetArray());
			m_value = value;
		}
	}
	
	inline UniformMatrix3fv::UniformMatrix3fv(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Uniform(Shader, Name, Type, Location) {}
	inline UniformMatrix3fv::~UniformMatrix3fv(void) {}
	inline void UniformMatrix3fv::Set(Mat3f& value) {
		if (shader->renderer->GetProgramForce() || m_value != value) {
			glUniformMatrix3fv(location, 1, false, value.GetArray());
			m_value = value;
		}
	}
	
	inline UniformMatrix4fv::UniformMatrix4fv(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Uniform(Shader, Name, Type, Location) {}
	inline UniformMatrix4fv::~UniformMatrix4fv(void) {}
	inline void UniformMatrix4fv::Set(Mat4f& value) {
		if (shader->renderer->GetProgramForce() || m_value != value) {
			glUniformMatrix4fv(location, 1, false, value.GetArray());
			m_value = value;
		}
	}
	
	inline UniformSampler2D::UniformSampler2D(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Uniform(Shader, Name, Type, Location) {}
	inline UniformSampler2D::~UniformSampler2D(void) {}
	inline void UniformSampler2D::Set(Texture* value) {
		shader->renderer->BindTexture(location, value);
	}
	
	inline UniformSamplerCube::UniformSamplerCube(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Uniform(Shader, Name, Type, Location) {}
	inline UniformSamplerCube::~UniformSamplerCube(void) {}
	inline void UniformSamplerCube::Set(Texture* value) {
		shader->renderer->BindTexture(location, value);
	}
}

#endif