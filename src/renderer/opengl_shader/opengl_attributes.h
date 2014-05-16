#ifndef ODIN_OPENGL_ATTRIBUTES_H
#define ODIN_OPENGL_ATTRIBUTES_H

namespace Odin {
	
	class OpenGLShader;
	
	class Attribute{
		public:
			OpenGLShader* shader;
			std::string name;
			uint32 type;
			int32 location;
			
			inline Attribute(OpenGLShader* Shader, std::string Name, uint32 type, int32 Location);
			inline virtual ~Attribute(void);
	};
	
	class Attribute1i : public Attribute{
		public:
			inline Attribute1i(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~Attribute1i(void);
	};
	
	class Attribute2i : public Attribute{
		public:
			inline Attribute2i(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~Attribute2i(void);
	};
	
	class Attribute3i : public Attribute{
		public:
			inline Attribute3i(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~Attribute3i(void);
	};
	
	class Attribute4i : public Attribute{
		public:
			inline Attribute4i(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~Attribute4i(void);
	};
	
	class Attribute1f : public Attribute{
		public:
			inline Attribute1f(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~Attribute1f(void);
	};
	
	class Attribute2f : public Attribute{
		public:
			inline Attribute2f(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~Attribute2f(void);
	};
	
	class Attribute3f : public Attribute{
		public:
			inline Attribute3f(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~Attribute3f(void);
	};
	
	class Attribute4f : public Attribute{
		public:
			inline Attribute4f(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~Attribute4f(void);
	};
}

#endif