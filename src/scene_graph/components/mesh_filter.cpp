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
		Transform* transform = GetComponent<Transform>();
		Array<MeshBone*> meshBones = mesh->bones;
		uint32 i = 0, il = meshBones.Length();

		if (il == 0) return;

		for (; i < il; i++) {
			MeshBone* meshBone = meshBones[i];

			GameObject* gameObject = new GameObject();
			
			Bone* bone = new Bone();
			bone->m_name = meshBone->name;
			bone->m_parentIndex = meshBone->parentIndex;
			bone->m_skinned = meshBone->skinned;
			bone->m_bindPose = meshBone->bindPose;
			gameObject->AddComponent(bone);
			
			Transform* boneTransform = new Transform();
			boneTransform->position = meshBone->position;
			boneTransform->rotation = meshBone->rotation;
			boneTransform->scale = meshBone->scale;
			gameObject->AddComponent(boneTransform);
			
			m_bones.Push(bone);
		}

		transform->AddChild(m_bones[0]->GetComponent<Transform>());

		for (i = 0; i < il; i++) {
			Bone* bone = m_bones[i];
			
			if (bone != NULL && bone->m_parentIndex != -1) {
				Bone* parent = m_bones[bone->m_parentIndex];
				if (parent == NULL) continue;
				
				Transform* transform = parent->GetComponent<Transform>();
				if (transform != NULL) transform->AddChild(bone->GetComponent<Transform>());
			}
		}
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

		m_bones.Clear();
	}
}

#endif