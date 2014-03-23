#ifndef _ODIN_TRANSFORM_CPP_
#define _ODIN_TRANSFORM_CPP_

namespace Odin {

	inline Transform::Transform(void) : Component() {
		m_matricesNeedsUpdate = true;
		scale.Set(1.0f, 1.0f, 1.0f);

		p_updateOrder = -9999;
	}

	inline Transform::~Transform(void) {
		p_Clear();
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

	inline void Transform::p_Clear(void) {
		Component::p_Clear();

		m_parent = NULL;
		m_root = NULL;
		m_depth = 0;
		m_children.Clear();
	}

	inline void Transform::p_Init(void) {

	}

	inline void Transform::p_Start(void) {

	}

	inline void Transform::p_Update(void) {

		matrix.Compose(position, scale, rotation);

		if (m_parent != NULL) {
			Mat4Mul<float32>(m_parent->matrixWorld, matrix, matrixWorld);

		} else {
			matrixWorld = matrix;
		}

		m_matricesNeedsUpdate = true;
	}

	inline void Transform::UpdateMatrices(const Mat4f& viewMatrix) {
		if (!m_matricesNeedsUpdate) {
			return;
		}

		Mat4Mul<float32>(viewMatrix, matrixWorld, modelView);
		Mat3InverseMat4<float32>(modelView, normalMatrix).Transpose();

		m_matricesNeedsUpdate = false;
	}

	inline void Transform::p_Sort(void) {
		p_order = float32(m_depth);
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

		}

		return *this;
	}
}

#endif