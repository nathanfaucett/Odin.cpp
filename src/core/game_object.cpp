#ifndef ODIN_GAME_OBJECT_CPP
#define ODIN_GAME_OBJECT_CPP

namespace Odin {

	inline void GameObject::m_RemoveParent(void) {

		m_depth = 0;
		m_root = this;
		m_parent = NULL;
	}

	inline void GameObject::m_UpdateDepth(unsigned int depth) {
		m_depth = depth;

		for (unsigned i = m_children.size(); i-- > 0;) {
			m_children[i]->m_UpdateDepth(depth + 1);
		}
	}

	inline GameObject::GameObject(void) : Object() {
		m_depth = 0;
		m_childCount = 0;
		m_parent = NULL;
		m_root = this;
	}

	inline GameObject::GameObject(const GameObject& other) : Object(other) {
		Copy(other);
	}

	inline GameObject::~GameObject(void) {
		Deconstructor();
	}

	inline void GameObject::Deconstructor(void) {
		m_children.clear();
		m_parent = NULL;
		m_root = NULL;
	}

	inline GameObject* GameObject::Clone(void) {

		return new GameObject(*this);
	}

	inline GameObject& GameObject::Copy(const GameObject& other) {

		m_depth = 0;
		m_childCount = 0;
		m_parent = NULL;
		m_root = this;

		return *this;
	}

	inline void GameObject::Update(void) {
		matrix.Compose(position, scale, rotation);
		matrixWorld = matrix;
	}

	inline GameObject* GameObject::operator [] (int i) {
		return m_children[i];
	}

	inline GameObject* GameObject::GetParent(void) const {

		return m_parent;
	}

	inline unsigned int GameObject::GetDepth(void) const {

		return m_depth;
	}

	inline void GameObject::SetParent(GameObject* parent) {

		if (m_parent != NULL) {
			m_parent->RemoveChild(this);
		}

		if (parent != m_parent) {
			parent->AddChild(this);
		}
	}

	inline void GameObject::AddChild(GameObject* child) {

		if (child != NULL) {
			if (child->m_parent != NULL) {
				child->m_parent->RemoveChild(child);
			}

			m_children.push_back(child);
			child->m_parent = this;

			GameObject* root = this;
			unsigned int depth = 0;

			while (root->m_parent != NULL) {
				root = root->m_parent;
				depth++;
			}

			child->m_root = root;
			this->m_root = root;
			m_UpdateDepth(depth);

			if (child->m_scene != m_scene) {
				m_scene->AddGameObject(child);
			}

			m_childCount++;
		}
	}

	inline void GameObject::RemoveChild(GameObject* child) {

		if (NULL != child) {

			for (unsigned i = m_children.size(); i-- > 0;) {

				if (m_children[i] == child) {
					m_children.erase(m_children.begin() + i);
					child->m_RemoveParent();

					if (child->m_scene != m_scene) {
						m_scene->RemoveGameObject(child);
					}

					m_childCount--;
					break;
				}
			}
		}
	}

	inline void GameObject::DetachChildren(void) {
		GameObject* child;

		for (unsigned i = m_children.size(); i-- > 0;) {
			child = m_children[i];

			m_children.erase(m_children.begin() + i);
			child->m_RemoveParent();
			m_childCount--;
		}
	}

	inline int GameObject::IndexOf(GameObject* child) {

		if (NULL != child) {

			for (unsigned i = m_children.size(); i-- > 0;) {

				if (m_children[i] == child) {
					return i;
				}
			}
		}

		return -1;
	}
}

#endif