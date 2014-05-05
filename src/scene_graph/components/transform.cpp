#ifndef ODIN_TRANSFORM_CPP
#define ODIN_TRANSFORM_CPP

namespace Odin {

	inline Transform::Transform(void) : Component() {
		m_parent = NULL;
		m_root = this;
		
		scale.Set(1.0f, 1.0f, 1.0f);
		p_updateOrder = -9999;
	}
	
	inline Transform::Transform(std::string name) : Component(name) {
		m_parent = NULL;
		m_root = this;
		
		scale.Set(1.0f, 1.0f, 1.0f);
		p_updateOrder = -9999;
	}
	
	inline Transform::Transform(const Transform& other) : Component() {
		Copy(other);
	}
	
	inline Transform::Transform(const Transform&& other) : Component() {
		Move(std::move(other));
	}

	inline Transform::~Transform(void) {
		p_Clear();
	}
	
	inline Transform* Transform::Clone(void) {
		return new Transform(*this);
	}
	
	inline Transform& Transform::Copy(const Transform& other) {
		Component::Copy(static_cast<Component>(other));
		
		if (other.m_parent != NULL) {
			other.m_parent->AddChild(this);
		}
		for (uint32 i = 0, length = other.m_childCount; i < length; i++) {
			AddChild(other.m_children[i]);
		}
		
		position = other.position;
		scale = other.scale;
		rotation = other.rotation;

		matrix = other.matrix;
		matrixWorld = other.matrixWorld;
		modelView = other.modelView;
		normalMatrix = other.normalMatrix;
		
		return *this;
	}
	
	inline Transform& Transform::Move(const Transform&& other) {
		Component::Move(std::move(static_cast<Component>(other)));
		
		if (other.m_parent != NULL) {
			other.m_parent->AddChild(this);
		}
		for (uint32 i = 0, length = other.m_childCount; i < length; i++) {
			AddChild(other.m_children[i]);
		}
		
		position = std::move(other.position);
		scale = std::move(other.scale);
		rotation = std::move(other.rotation);

		matrix = std::move(other.matrix);
		matrixWorld = std::move(other.matrixWorld);
		modelView = std::move(other.modelView);
		normalMatrix = std::move(other.normalMatrix);
		
		return *this;
	}

	inline void Transform::m_UpdateDepth(Transform* transform, int32 depth) {
		int32 i = m_children.Length();
		transform->m_depth = depth;
		Transform* child;

		while (i--) {
			child = m_children[i];
			child->m_UpdateDepth(child, depth + 1);
		}
	}

	inline void Transform::p_Init(void) {

	}

	inline void Transform::p_Start(void) {

	}

	inline void Transform::p_Clear(void) {
		Component::p_Clear();

		m_parent = NULL;
		m_root = this;
		m_depth = 0;
		m_children.Clear();
	}

	inline void Transform::p_Sort(void) {
		p_order = float32(m_depth);
	}

	inline void Transform::Update(void) {

		matrix.Compose(position, scale, rotation);

		if (m_parent != NULL) {
			Mat4Mul<float32>(m_parent->matrixWorld, matrix, matrixWorld);

		} else {
			matrixWorld = matrix;
		}
	}

	inline void Transform::UpdateMatrices(const Mat4f& viewMatrix) {

		Mat4Mul<float32>(viewMatrix, matrixWorld, modelView);
		Mat3InverseMat4<float32>(modelView, normalMatrix).Transpose();
	}

	inline int32 Transform::GetDepth(void) {

		return m_depth;
	}

	inline Transform& Transform::AddChild(Transform* child) {
		if (child == NULL) {
			return *this;
		}

		int32 index = m_children.IndexOf(child),
		      depth;

		Transform* root;
		Scene* scene;

		if (index == -1) {
			child->m_parent = this;
			m_children.Push(child);
			m_childCount++;

			root = this;
			depth = 0;

			while (root->m_parent != NULL) {
				root = root->m_parent;
				depth++;
			}

			child->m_root = root;
			m_root = root;

			m_UpdateDepth(this, depth);

			if ((scene = GetScene()) != NULL) {
				scene->SortType(this);
			}

		} else {
			Log("Transform::RemoveChild child already child of this Transform", __LINE__);
		}

		return *this;
	}

	inline Transform& Transform::RemoveChild(Transform* child) {
		if (child == NULL) {
			return *this;
		}

		int32 index = m_children.IndexOf(child),
		      depth;

		Transform* root;

		if (index != -1) {
			child->m_parent = NULL;
			m_children.Splice(index, 1);
			m_childCount--;

			root = this;
			depth = 0;

			while (root->m_parent != NULL) {
				root = root->m_parent;
				depth++;
			}

			child->m_root = child;
			m_root = root;

			m_UpdateDepth(this, depth);

		} else {
			Log("Transform::RemoveChild child not a child of this Transform", __LINE__);
		}

		return *this;
	}

	inline Transform& Transform::operator =(const Transform& other) {
		return Copy(other);
	}
	
	inline Transform& Transform::operator =(const Transform&& other) {
		return Move(std::move(other));
	}
}

#endif