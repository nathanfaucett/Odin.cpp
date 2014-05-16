#ifndef ODIN_OPENGL_UNIFORMS_H
#define ODIN_OPENGL_UNIFORMS_H

namespace Odin {
	
	class OpenGLShader;
	
	class Uniform{
		private:
			friend class OpenGLRenderer;
			friend class OpenGLShader;
		public:
			OpenGLShader* shader;
			std::string name;
			uint32 type;
			int32 location;
			
			inline Uniform(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline virtual ~Uniform(void);
			inline virtual void Set(void);
	};
	class Uniform1i : public Uniform{
		private:
			int32 m_value;
		public:
			inline Uniform1i(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~Uniform1i(void);
			inline void Set(int32 value);
	};
	class Uniform2i : public Uniform{
		private:
			Vec2i m_value;
		public:
			inline Uniform2i(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~Uniform2i(void);
			inline void Set(Vec2i& value);
	};
	class Uniform3i : public Uniform{
		private:
			Vec3i m_value;
		public:
			inline Uniform3i(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~Uniform3i(void);
			inline void Set(Vec3i& value);
	};
	class Uniform4i : public Uniform{
		private:
			Vec4i m_value;
		public:
			inline Uniform4i(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~Uniform4i(void);
			inline void Set(Vec4i& value);
	};
	class Uniform1f : public Uniform{
		private:
			float32 m_value;
		public:
			inline Uniform1f(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~Uniform1f(void);
			inline void Set(float32 value);
	};
	class Uniform2f : public Uniform{
		private:
			Vec2f m_value;
		public:
			inline Uniform2f(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~Uniform2f(void);
			inline void Set(Vec2f& value);
	};
	class Uniform3f : public Uniform{
		private:
			Vec3f m_value;
		public:
			inline Uniform3f(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~Uniform3f(void);
			inline void Set(Vec3f& value);
	};
	class Uniform4f : public Uniform{
		private:
			Vec4f m_value;
		public:
			inline Uniform4f(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~Uniform4f(void);
			inline void Set(Vec4f& value);
	};
	class UniformMatrix2fv : public Uniform{
		private:
			Mat2f m_value;
		public:
			inline UniformMatrix2fv(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~UniformMatrix2fv(void);
			inline void Set(Mat2f& value);
	};
	class UniformMatrix3fv : public Uniform{
		private:
			Mat3f m_value;
		public:
			inline UniformMatrix3fv(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~UniformMatrix3fv(void);
			inline void Set(Mat3f& value);
	};
	class UniformMatrix4fv : public Uniform{
		private:
			Mat4f m_value;
		public:
			inline UniformMatrix4fv(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~UniformMatrix4fv(void);
			inline void Set(Mat4f& value);
	};
	
	class UniformSampler2D : public Uniform{
		public:
			inline UniformSampler2D(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~UniformSampler2D(void);
			inline void Set(Texture* value);
	};
	class UniformSamplerCube : public Uniform{
		public:
			inline UniformSamplerCube(OpenGLShader* Shader, std::string Name, uint32 Type, int32 Location);
			inline ~UniformSamplerCube(void);
			inline void Set(Texture* value);
	};
}

#endif