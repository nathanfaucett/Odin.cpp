#ifndef ODIN_MATERIAL_H
#define ODIN_MATERIAL_H

namespace Odin {
	
	class MaterialUniform {
		public:
			inline MaterialUniform(void) {}
			inline ~MaterialUniform(void) {}
	};
	
	template <typename Type> class BaseMaterialUniform : public MaterialUniform {
		public:
			Type value;
			inline BaseMaterialUniform(Type Value) : MaterialUniform() {
				value = Value;
			}
			inline ~BaseMaterialUniform(void) {}
	};
	
	typedef BaseMaterialUniform<int32> MaterialUniform1i;
	typedef BaseMaterialUniform<Vec2i> MaterialUniform2i;
	typedef BaseMaterialUniform<Vec3i> MaterialUniform3i;
	typedef BaseMaterialUniform<Vec4i> MaterialUniform4i;
	
	typedef BaseMaterialUniform<float32> MaterialUniform1f;
	typedef BaseMaterialUniform<Vec2f> MaterialUniform2f;
	typedef BaseMaterialUniform<Vec3f> MaterialUniform3f;
	typedef BaseMaterialUniform<Vec4f> MaterialUniform4f;
	
	typedef BaseMaterialUniform<Mat2f> MaterialUniformMatrix2fv;
	typedef BaseMaterialUniform<Mat3f> MaterialUniformMatrix3fv;
	typedef BaseMaterialUniform<Mat4f> MaterialUniformMatrix4fv;
	
	typedef BaseMaterialUniform<Texture*> MaterialUniformSampler2D;
	typedef BaseMaterialUniform<Texture*> MaterialUniformSamplerCube;
	
	
	class OpenGLShader;
	
	class Material : public Asset {
		
		private:
			friend class OpenGLRenderer;
			OpenGLShader* m_openGLShader;
			
			Side m_side;
			Blending m_blending;
			bool m_wireframe;
			bool m_receiveShadow, m_castShadow; 
			float32 m_wireframeLineWidth;
			
			bool m_needsUpdate;
		protected:

		public:
			std::string vertex, fragment;
			std::unordered_map<std::string, MaterialUniform*> uniforms;
			
			inline Material(std::string name, std::string src = "");
			inline Material(std::string name, std::string Vertex, std::string Fragment);
			inline virtual ~Material(void);
			
			inline virtual void Load(void);
			
			inline OpenGLShader* GetOpenGLShader(void);
	
			inline void SetSide(Side side);
			inline Side GetSide(void);
	
			inline void SetBlending(Blending blending);
			inline Blending GetBlending(void);
			
			inline void SetWireframe(bool wireframe);
			inline bool GetWireframe(void);
			
			inline void SetWireframeLineWidth(float32 wireframeLineWidth);
			inline float32 GetWireframeLineWidth(void);
			
			inline void SetReceiveShadow(bool receiveShadow);
			inline bool GetReceiveShadow(void);
			
			inline void SetCastShadow(bool castShadow);
			inline bool SetCastShadow(void);
	};
}

#endif