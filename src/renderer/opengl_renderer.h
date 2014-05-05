#ifndef ODIN_OPENGL_RENDERER_H
#define ODIN_OPENGL_RENDERER_H

#define GLSL(version, src) "#version " #version " core\n" #src

namespace Odin {
	
	class OpenGLRenderer{
		
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
			int32 m_activeTexture;
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
			
			inline void m_InitGL(void);
			inline void m_GetGPUInfo(void);

		protected:
			Window* p_window;
			SDL_Surface* p_screenSurface;
			
		public:
			
			inline OpenGLRenderer(void);
			inline ~OpenGLRenderer(void);
			
			inline void SetWindow(Window* window);
			inline Window* GetWindow(Window* window);

			inline uint32 CreateShader(uint32 shaderType, const std::string& shaderString);
			inline uint32 CreateProgram(uint32 vertexShader, uint32 fragmentShader);
			inline uint32 CreateProgram(std::string vertexShaderSource, std::string fragmentShaderSource);
			inline uint32 CreateProgram(Array<uint32>& shaderList);
			
			template <typename Type> inline uint32 CreateVertexBuffer(Array<Type>& items, uint32 type = GL_ARRAY_BUFFER, uint32 draw = GL_STATIC_DRAW);
			
			inline uint32 CreateTexture(Texture* texture);
			
			inline void ClearCanvas(bool color = true, bool depth = true, bool stencil = true);
			inline void ClearColor(void);
			inline void ClearDepth(void);
			inline void ClearStencil(void);
			
			inline void EnableAttribute(uint32 attribute);
			inline void DisableAttribute(uint32 attribute);
			inline void DisableAttributes(void);
			
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