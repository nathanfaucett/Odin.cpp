#ifndef ODIN_OPENGL_ATTRIBUTES_CPP
#define ODIN_OPENGL_ATTRIBUTES_CPP

namespace Odin {
	
	inline Attribute::Attribute(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) {
		shader = Shader;
		name = Name;
		type = Type;
		location = Location;
	}
	inline Attribute::~Attribute(void) {
		shader = NULL;
	}
	
	inline Attribute1i::Attribute1i(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Attribute(Shader, Name, Type, Location) {}
	inline Attribute1i::~Attribute1i(void) {}
	
	inline Attribute2i::Attribute2i(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Attribute(Shader, Name, Type, Location) {}
	inline Attribute2i::~Attribute2i(void) {}

	inline Attribute3i::Attribute3i(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Attribute(Shader, Name, Type, Location) {}
	inline Attribute3i::~Attribute3i(void) {}

	inline Attribute4i::Attribute4i(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Attribute(Shader, Name, Type, Location) {}
	inline Attribute4i::~Attribute4i(void) {}

	inline Attribute1f::Attribute1f(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Attribute(Shader, Name, Type, Location) {}
	inline Attribute1f::~Attribute1f(void) {}
	
	inline Attribute2f::Attribute2f(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Attribute(Shader, Name, Type, Location) {}
	inline Attribute2f::~Attribute2f(void) {}

	inline Attribute3f::Attribute3f(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Attribute(Shader, Name, Type, Location) {}
	inline Attribute3f::~Attribute3f(void) {}

	inline Attribute4f::Attribute4f(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location) : Attribute(Shader, Name, Type, Location) {}
	inline Attribute4f::~Attribute4f(void) {}
}

#endif