#ifndef ODIN_MESH_FILTER_CPP
#define ODIN_MESH_FILTER_CPP

namespace Odin {

	inline MeshFilter::MeshFilter(void) : Component() {
		m_visible = true;
		
		mesh = NULL;
		material = NULL;
	}

	inline MeshFilter::~MeshFilter(void) {
		Clear();
	}
	
	inline MeshFilter* MeshFilter::Clone(void) {
		return &((new MeshFilter())->Copy(*this));
	}
	
	inline MeshFilter& MeshFilter::Copy(const MeshFilter& other) {
		
		mesh = other.mesh;
		material = other.material;
		
		return *this;
	}

	inline void MeshFilter::p_Init(void) {
		Component::p_Init();
	}

	inline void MeshFilter::p_Start(void) {
		Component::p_Start();
	}

	inline void MeshFilter::Update(void) {

	}

	inline void MeshFilter::Clear(void) {
		mesh = NULL;
		material = NULL;
	}
}

#endif