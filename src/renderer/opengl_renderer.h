#ifndef ODIN_OPENGL_RENDERER_H
#define ODIN_OPENGL_RENDERER_H

#define GLSL(version, src) (version >= 330 ? "#version " #version " core\n" #src : "#version " #version "\n" #src)

namespace Odin {
	
	class OpenGLRenderer{
		
		class OpenGLShader{
			
			class Uniform{
				private:
					friend class OpenGLShader;
					OpenGLShader* m_shader;
					std::string m_name;
					int32 m_location;
				public:
					inline Uniform(OpenGLShader* shader, std::string name, uint32 location) {
						m_shader = shader;
						m_name = name;
						m_location = location;
					}
					inline virtual ~Uniform(void) {
						m_shader = NULL;
					}
					inline virtual void Set(void) = 0;
			};
			class Uniform1i : public Uniform{
				private:
					int32 m_value;
				public:
					inline Uniform1i(OpenGLShader* shader, std::string name, uint32 location) : Uniform(shader, name, location) {}
					inline ~Uniform1i(void) {}
					inline void Set(int32 value) {
						if (m_shader->m_renderer->m_programForce || m_value != value) {
							glUniform1i(m_location, value);
							m_value = value;
						}
					}
			};
			class Uniform1f : public Uniform{
				private:
					float32 m_value;
				public:
					inline Uniform1f(OpenGLShader* shader, std::string name, uint32 location) : Uniform(shader, name, location) {}
					inline ~Uniform1f(void) {}
					inline void Set(float32 value) {
						if (m_shader->m_renderer->m_programForce || m_value != value) {
							glUniform1f(m_location, value);
							m_value = value;
						}
					}
			};
			class Uniform2f : public Uniform{
				private:
					Vec2f m_value;
				public:
					inline Uniform2f(OpenGLShader* shader, std::string name, uint32 location) : Uniform(shader, name, location) {}
					inline ~Uniform2f(void) {}
					inline void Set(Vec2f& value) {
						if (m_shader->m_renderer->m_programForce || m_value != value) {
							glUniform2f(m_location, value.x, value.y);
							m_value = value;
						}
					}
			};
			class Uniform3f : public Uniform{
				private:
					Vec3f m_value;
				public:
					inline Uniform3f(OpenGLShader* shader, std::string name, uint32 location) : Uniform(shader, name, location) {}
					inline ~Uniform3f(void) {}
					inline void Set(Vec3f& value) {
						if (m_shader->m_renderer->m_programForce || m_value != value) {
							glUniform3f(m_location, value.x, value.y, value.z);
							m_value = value;
						}
					}
			};
			class Uniform4f : public Uniform{
				private:
					Vec4f m_value;
				public:
					inline Uniform4f(OpenGLShader* shader, std::string name, uint32 location) : Uniform(shader, name, location) {}
					inline ~Uniform4f(void) {}
					inline void Set(Vec4f& value) {
						if (m_shader->m_renderer->m_programForce || m_value != value) {
							glUniform4f(m_location, value.x, value.y, value.z, value.w);
							m_value = value;
						}
					}
			};
			class UniformMatrix2fv : public Uniform{
				private:
					Mat2f m_value;
				public:
					inline UniformMatrix2fv(OpenGLShader* shader, std::string name, uint32 location) : Uniform(shader, name, location) {}
					inline ~UniformMatrix2fv(void) {}
					inline void Set(Mat2f& value) {
						if (m_shader->m_renderer->m_programForce || m_value != value) {
							glUniformMatrix2fv(m_location, 1, false, value.GetArray());
							m_value = value;
						}
					}
			};
			class UniformMatrix3fv : public Uniform{
				private:
					Mat3f m_value;
				public:
					inline UniformMatrix3fv(OpenGLShader* shader, std::string name, uint32 location) : Uniform(shader, name, location) {}
					inline ~UniformMatrix3fv(void) {}
					inline void Set(Mat3f& value) {
						if (m_shader->m_renderer->m_programForce || m_value != value) {
							glUniformMatrix3fv(m_location, 1, false, value.GetArray());
							m_value = value;
						}
					}
			};
			class UniformMatrix4fv : public Uniform{
				private:
					Mat4f m_value;
				public:
					inline UniformMatrix4fv(OpenGLShader* shader, std::string name, uint32 location) : Uniform(shader, name, location) {}
					inline ~UniformMatrix4fv(void) {}
					inline void Set(Mat4f& value) {
						if (m_shader->m_renderer->m_programForce || m_value != value) {
							glUniformMatrix4fv(m_location, 1, false, value.GetArray());
							m_value = value;
						}
					}
			};
			
			class Attribute{
				private:
					friend class OpenGLShader;
					OpenGLShader* m_shader;
					std::string m_name;
					int32 m_location;
				public:
					inline Attribute(OpenGLShader* shader, std::string name, uint32 location) {
						m_shader = shader;
						m_name = name;
						m_location = location;
					}
					inline virtual ~Attribute(void) {
						m_shader = NULL;
					}
					inline virtual void Set(void) = 0;
			};
			class Attribute1i : public Attribute{
				public:
					inline Attribute1i(OpenGLShader* shader, std::string name, uint32 location) : Attribute(shader, name, location) {}
					inline ~Attribute1i(void) {}
					inline void Set(int32 buffer) {
						m_shader->m_renderer->BindBuffer(m_location, buffer, GL_ARRAY_BUFFER, 1, GL_SHORT, 0);
					}
			};
			class Attribute1f : public Attribute{
				public:
					inline Attribute1f(OpenGLShader* shader, std::string name, uint32 location) : Attribute(shader, name, location) {}
					inline ~Attribute1f(void) {}
					inline void Set(int32 buffer) {
						m_shader->m_renderer->BindBuffer(m_location, buffer, GL_ARRAY_BUFFER, 1, GL_FLOAT, 0);
					}
			};
			class Attribute2f : public Attribute{
				public:
					inline Attribute2f(OpenGLShader* shader, std::string name, uint32 location) : Attribute(shader, name, location) {}
					inline ~Attribute2f(void) {}
					inline void Set(int32 buffer) {
						m_shader->m_renderer->BindBuffer(m_location, buffer, GL_ARRAY_BUFFER, 2, GL_FLOAT, 0);
					}
			};
			class Attribute3f : public Attribute{
				public:
					inline Attribute3f(OpenGLShader* shader, std::string name, uint32 location) : Attribute(shader, name, location) {}
					inline ~Attribute3f(void) {}
					inline void Set(int32 buffer) {
						m_shader->m_renderer->BindBuffer(m_location, buffer, GL_ARRAY_BUFFER, 3, GL_FLOAT, 0);
					}
			};
			class Attribute4f : public Attribute{
				public:
					inline Attribute4f(OpenGLShader* shader, std::string name, uint32 location) : Attribute(shader, name, location) {}
					inline ~Attribute4f(void) {}
					inline void Set(int32 buffer) {
						m_shader->m_renderer->BindBuffer(m_location, buffer, GL_ARRAY_BUFFER, 4, GL_FLOAT, 0);
					}
			};
			
			private:
				friend class OpenGLRenderer;
				OpenGLRenderer* m_renderer;
				uint32 m_program;
				Array<Uniform*> m_uniforms;
				Array<Attribute*> m_attributes;
	
			protected:
				
			public:
				inline OpenGLShader(OpenGLRenderer* renderer, std::string vertex, std::string fragment);
				inline ~OpenGLShader(void);
		};
		
		private:
			std::string m_precision;
            Array<uint32> m_extensions;

            int32 m_maxAnisotropy;
            int32 m_maxTextures;
            int32 m_maxVertexTextures;
            int32 m_maxTextureSize;
            int32 m_maxCubeTextureSize;
            int32 m_maxRenderBufferSize;

            int32 m_maxUniforms;
            int32 m_maxVaryings;
            int32 m_maxAttributes;

            uint32* m_enabledAttributes;
			
			uint32 m_program;
			bool m_programForce;
			int32 m_textureIndex;
			uint32 m_activeTexture;
			int32 m_activeTextureLocation;
			float32 m_viewportX, m_viewportY, m_viewportWidth, m_viewportHeight;
			bool m_depthTest;
			bool m_depthWrite;
			bool m_blendingDisabled;
			Blending m_blending;
			Colorf m_clearColor;
			float32 m_clearAlpha;
			float32 m_clearDepth;
			int32 m_clearStencil;
			FrontFace m_frontFace;
			bool m_cullFaceDisabled;
			CullFace m_cullFace;
			float32 m_lineWidth;
			StencilFunction m_stencilFunction;
			int32 m_stencilReferenceValue;
			uint32 m_stencilMask;
			
			inline void m_ClearGL(void);
			inline void m_InitGL(void);

		protected:
			Window* p_window;
			SDL_Surface* p_screenSurface;
			
            Array<uint32> p_textures;
            Array<uint32> p_vertexBuffers;
            Array<uint32> p_programs;
			
		public:
			inline OpenGLRenderer(void);
			inline virtual ~OpenGLRenderer(void);
			
			inline void SetWindow(Window* window);
			inline Window* GetWindow(Window* window);

			inline uint32 CreateShader(uint32 shaderType, const std::string& shaderString);
			inline uint32 CreateProgram(uint32 vertexShader, uint32 fragmentShader);
			inline uint32 CreateProgram(std::string vertexShaderSource, std::string fragmentShaderSource);
			inline uint32 CreateProgram(Array<uint32>& shaderList);
			
			template <typename Type> inline uint32 CreateVertexBuffer(Type items[], int32 size, uint32 type = GL_ARRAY_BUFFER, uint32 draw = GL_STATIC_DRAW);
			inline uint32 CreateTexture(Texture* texture);
			
			inline void DeleteProgram(uint32 program);
			inline void DeleteVertexBuffer(uint32 vertexBuffer);
			inline void DeleteTexture(uint32 texture);
			
			inline void ClearCanvas(bool color = true, bool depth = true, bool stencil = true);
			inline void ClearColor(void);
			inline void ClearDepth(void);
			inline void ClearStencil(void);
			
			inline void EnableAttribute(uint32 attribute);
			inline void DisableAttribute(uint32 attribute);
			inline void DisableAttributes(void);
			
			inline void BindBuffer(int32 location, uint32 buffer, uint32 arrayType = GL_ARRAY_BUFFER, int32 itemSize = 4, uint32 type = GL_FLOAT, const void* first = (void*)0);
			inline void BindTexture(int32 location, Texture* texture);
			
			inline void SetProgram(uint32 program);
			inline void SetViewport(float32 x = 0.0f, float32 y = 0.0f, float32 width = 1.0f, float32 height = 1.0f);
			inline void SetDepthTest(bool depthTest = true);
			inline void SetDepthWrite(bool depthWrite = true);
			inline void SetBlending(Blending blending = Blending::Default);
			inline void SetClearColor(const Colorf& color = Colorf::Black, float32 alpha = 1.0f);
			inline void SetClearDepth(float32 depth = 1.0f);
			inline void SetClearStencil(int32 stencil = 0);
			inline void SetFrontFace(FrontFace mode = FrontFace::CounterClockWise);
			inline void SetCullFace(CullFace mode = CullFace::Back);
			inline void SetLineWidth(float32 width = 1.0f);
			inline void SetScissor(float32 x = 0.0f, float32 y = 0.0f, float32 width = 1.0f, float32 height = 1.0f);
			inline void SetStencilFunction(CullFace cullFace = CullFace::Back, StencilFunction function = StencilFunction::Always, int32 referenceValue = 0, uint32 mask = 1);
			inline void SetStencilFunction(StencilFunction function = StencilFunction::Always, int32 referenceValue = 0, uint32 mask = 1);
	};
}

#endif