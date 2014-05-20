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
	
	inline void MeshFilter::p_Sort(void) {
		Array<MeshFilter*>* components = GetScene()->GetComponents<MeshFilter>();
		components->Sort(Sort);
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
	
	inline float32 MeshFilter::Sort(MeshFilter* a, MeshFilter* b) {
		return (a->mesh == b->mesh) ? 0.0f : 1.0;
	}

	inline void MeshFilter::Clear(void) {
		mesh = NULL;
		material = NULL;
	}
}

#endif