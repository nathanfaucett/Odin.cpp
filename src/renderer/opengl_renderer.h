#ifndef ODIN_OPENGL_RENDERER_H
#define ODIN_OPENGL_RENDERER_H


namespace Odin {
	
	class OpenGLShader;
	
	class OpenGLRenderer{
		
		private:
			std::string m_precision;
            Array<uint32> m_extensions;

            float32 m_maxAnisotropy;
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
			SDL_Surface* p_surface;
			
            Array<uint32> p_textures;
            Array<uint32> p_vertexBuffers;
            Array<uint32> p_programs;
            Array<OpenGLShader*> p_shaders;
			
			inline uint32 p_CreateGLShader(uint32 shaderType, const std::string& shaderString);
		public:
			inline OpenGLRenderer(void);
			inline OpenGLRenderer(const OpenGLRenderer&) = default;
			inline OpenGLRenderer(OpenGLRenderer&&) = default;
			inline virtual ~OpenGLRenderer(void);
			
			inline void SetSurface(SDL_Surface* surface);
			inline SDL_Surface* GetSurface(void);

			inline uint32 CreateProgram(std::string& vertexShaderSource, std::string& fragmentShaderSource);
			inline uint32 UpdateProgram(uint32 program, std::string& vertexShaderSource, std::string& fragmentShaderSource);
			
			inline OpenGLShader* CreateShader(std::string& vertexShaderSource, std::string& fragmentShaderSource);
			inline OpenGLShader* UpdateShader(OpenGLShader* openGLShader, std::string& vertexShaderSource, std::string& fragmentShaderSource);
			inline void CreateMaterial(Material* material);
			
			inline void CreateMeshAttributes(Mesh* mesh);
			
			template <typename Type> inline uint32 CreateVertexBuffer(Type items[], int32 size, uint32 type = GL_ARRAY_BUFFER, uint32 draw = GL_STATIC_DRAW);
			template <typename Type> inline uint32 UpdateVertexBuffer(uint32 vertexBuffer, Type items[], int32 size, uint32 type = GL_ARRAY_BUFFER, uint32 draw = GL_STATIC_DRAW);

			inline uint32 CreateTexture(Texture* texture);
			
			inline void DeleteProgram(uint32 program);
			inline void DeleteVertexBuffer(uint32 vertexBuffer);
			inline void DeleteTexture(uint32 texture);
			
			inline void ClearCanvas(bool color = true, bool depth = true, bool stencil = true);
			inline void ClearColor(void);
			inline void ClearDepth(void);
			inline void ClearStencil(void);
			
			inline void EnableAttribute(int32 attribute);
			inline void DisableAttribute(int32 attribute);
			inline void DisableAttributes(void);
			
			inline void BindBuffer(int32 location, uint32 buffer, uint32 arrayType = GL_ARRAY_BUFFER, int32 itemSize = 4, uint32 type = GL_FLOAT, int32 stride = 0, int32 first = 0);
			inline void BindTexture(int32 location, Texture* texture);
			inline void BindMaterial(Material* material, Mat4f& projectionMatrix, Mat4f& viewMatrix, Transform* transform);
			inline void BindMeshAttributes(Material* material, Mesh* mesh);
			
			inline bool GetProgramForce(void);
			
			inline void SetProgram(uint32 program);
			inline void SetViewport(float32 x = 0.0f, float32 y = 0.0f, float32 width = 1.0f, float32 height = 1.0f);
			inline void SetDepthTest(bool depthTest = true);
			inline void SetDepthWrite(bool depthWrite = true);
			inline void SetBlending(Blending blending = Blending::Default);
			inline void SetBlending(bool value);
			inline void SetClearColor(const Colorf& color = Colorf::Black, float32 alpha = 1.0f);
			inline void SetClearDepth(float32 depth = 1.0f);
			inline void SetClearStencil(int32 stencil = 0);
			inline void SetFrontFace(FrontFace mode = FrontFace::CounterClockWise);
			inline void SetCullFace(CullFace mode = CullFace::Back);
			inline void SetCullFace(bool value = true);
			inline void SetLineWidth(float32 width = 1.0f);
			inline void SetScissor(float32 x = 0.0f, float32 y = 0.0f, float32 width = 1.0f, float32 height = 1.0f);
			inline void SetStencilFunction(CullFace cullFace = CullFace::Back, StencilFunction function = StencilFunction::Always, int32 referenceValue = 0, uint32 mask = 1);
			inline void SetStencilFunction(StencilFunction function = StencilFunction::Always, int32 referenceValue = 0, uint32 mask = 1);
	
			inline OpenGLRenderer& operator=(const OpenGLRenderer&)& = default;
			inline OpenGLRenderer& operator=(OpenGLRenderer&&)& = default;
	};
}

#endif