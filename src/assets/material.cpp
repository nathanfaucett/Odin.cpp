#ifndef ODIN_MATERIAL_CPP
#define ODIN_MATERIAL_CPP
namespace Odin {
	
	inline Material::Material(std::string name, std::string src) : Asset(name, src) {
		m_openGLShader = NULL;
		m_needsUpdate = true;
		
		m_blending = Blending::Default;
		m_wireframe = false;
		m_wireframeLineWidth = 1.0f;
		
		m_receiveShadow = true;
		m_castShadow = true;
		
		uniforms["diffuseColor"] = new MaterialUniform3f(Vec3f(1.0f));
		uniforms["shininess"] = new MaterialUniform1f(8.0f);
		uniforms["normalScale"] = new MaterialUniform1f(1.0f);
	}
	inline Material::Material(std::string name, std::string Vertex, std::string Fragment) : Asset(name, "") {
		vertex = Vertex;
		fragment = Fragment;
		
		m_openGLShader = NULL;
		m_needsUpdate = true;
		
		m_side = Side::Front;
		m_blending = Blending::Default;
		m_wireframe = false;
		m_wireframeLineWidth = 1.0f;
		
		m_receiveShadow = true;
		m_castShadow = true;
		
		uniforms["diffuseColor"] = new MaterialUniform3f(Vec3f(1.0f));
		uniforms["shininess"] = new MaterialUniform1f(8.0f);
		uniforms["normalScale"] = new MaterialUniform1f(1.0f);
	}
	inline Material::~Material(void) {
		m_openGLShader = NULL;
		uniforms.clear();
	}
	
	inline void Material::Load(void) {
		
	}
	
	inline OpenGLShader* Material::GetOpenGLShader(void) {
		return m_openGLShader;
	}
	
	inline void Material::SetSide(Side side) {
		m_side = side;
		m_needsUpdate = true;
	}
	inline Side Material::GetSide(void) {
		return m_side;
	}
	
	inline void Material::SetBlending(Blending blending) {
		m_blending = blending;
		m_needsUpdate = true;
	}
	inline Blending Material::GetBlending(void) {
		return m_blending;
	}
	
	inline void Material::SetWireframe(bool wireframe) {
		m_wireframe = wireframe;
		m_needsUpdate = true;
	}
	inline bool Material::GetWireframe(void) {
		return m_wireframe;
	}
	
	inline void Material::SetWireframeLineWidth(float32 wireframeLineWidth) {
		m_wireframeLineWidth = wireframeLineWidth;
		m_needsUpdate = true;
	}
	inline float32 Material::GetWireframeLineWidth(void) {
		return m_wireframeLineWidth;
	}
	
	inline void Material::SetReceiveShadow(bool receiveShadow) {
		m_receiveShadow = receiveShadow;
		m_needsUpdate = true;
	}
	inline bool Material::GetReceiveShadow(void) {
		return m_receiveShadow;
	}
	
	inline void Material::SetCastShadow(bool castShadow) {
		m_castShadow = castShadow;
		m_needsUpdate = true;
	}
	inline bool Material::SetCastShadow(void) {
		return m_castShadow;
	}
}

#endif