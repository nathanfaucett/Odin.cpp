#ifndef ODIN_BONE_CPP
#define ODIN_BONE_CPP

namespace Odin {

	inline Bone::Bone(void) : Component() {
		m_parentIndex = -1;
		m_name = "Bone_"+ GetInstanceID();

		m_skinned = true;

		m_inheritPosition = true;
		m_inheritRotation = true;
		m_inheritScale = true;
	}

	inline Bone::~Bone(void) {
		Clear();
	}
	
	inline Bone* Bone::Clone(void) {
		return &((new Bone())->Copy(*this));
	}
	
	inline Bone& Bone::Copy(const Bone& other) {
		
		m_parentIndex = other.m_parentIndex;

		m_bindPose = other.m_bindPose;
		m_skinned = other.m_skinned;

		m_inheritPosition = other.m_inheritPosition;
		m_inheritRotation = other.m_inheritRotation;
		m_inheritScale = other.m_inheritScale;
		
		return *this;
	}
	
	inline void Bone::p_Sort(void) {
		Array<Bone*>* components = GetScene()->GetComponents<Bone>();
		components->Sort(Sort);
	}

	inline void Bone::Update(void) {
		if (!m_skinned) return;
		Transform* transform = GetComponent<Transform>();
		Transform* parent = transform->GetParent();

		if (transform == NULL) return;
		m_uniform = transform->matrix;
		
		if (parent != NULL && m_parentIndex != -1) {
			Bone* bone = parent->GetComponent<Bone>();
			
			if (bone != NULL) {
				m_updateMatrix = bone->m_uniform;
	
				if (!m_inheritPosition || !m_inheritScale || !m_inheritRotation) {
					m_updateMatrix.Decompose(m_updatePosition, m_updateScale, m_updateRotation);
	
					if (!m_inheritPosition) m_updatePosition.Set(0.0f, 0.0f, 0.0f);
					if (!m_inheritScale) m_updateScale.Set(1.0f, 1.0f, 1.0f);
					if (!m_inheritRotation) m_updateRotation.Set(0.0f, 0.0f, 0.0f, 1.0f);
	
					m_updateMatrix.Compose(m_updatePosition, m_updateScale, m_updateRotation);
				}
				
				Mat4Mul<float32>(m_updateMatrix, m_uniform, m_uniform);
			}
		}
	}

	inline void Bone::Clear(void) {
		m_parentIndex = -1;

		m_skinned = true;

		m_inheritPosition = true;
		m_inheritRotation = true;
		m_inheritScale = true;
	}
	
	inline float32 Bone::Sort(Bone* a, Bone* b) {
		return static_cast<float32>(a->m_parentIndex) - static_cast<float32>(b->m_parentIndex);
	}
}

#endif