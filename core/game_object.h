#ifndef ODIN_GAME_OBJECT_H
#define ODIN_GAME_OBJECT_H

namespace Odin {

	struct Scene;

	class GameObject : public Object {

		private:
			friend class Scene;
			std::vector<GameObject*> m_children;

			Scene* m_scene;

			GameObject* m_parent;
			GameObject* m_root;
			unsigned int m_depth;
			unsigned int m_childCount;

			inline void m_RemoveParent() {

				m_depth = 0;
				m_root = this;
				m_parent = NULL;
			}

			inline void m_UpdateDepth(unsigned int depth) {
				m_depth = depth;

				for (unsigned i = m_children.size(); i-- > 0;) {
					m_children[i]->m_UpdateDepth(depth + 1);
				}
			}

		protected:

		public:
			Vec3 position, scale;
			Quat rotation;

			Mat4 matrix, matrixWorld;

			GameObject() : Object() {
				m_depth = 0;
				m_childCount = 0;
				m_parent = NULL;
				m_root = this;
			}

			~GameObject() {
				Deconstructor();
			}

			inline void virtual Deconstructor() {
				m_children.clear();
				m_parent = NULL;
				m_root = NULL;
			}

			inline void Update() {
				matrix.Compose(position, scale, rotation);
				matrixWorld = matrix;
			}

			inline GameObject* operator [] (int i) {
				return m_children[i];
			}

			inline GameObject* GetParent() const {

				return m_parent;
			}

			inline unsigned int GetDepth() const {

				return m_depth;
			}

			inline void SetParent(GameObject* parent) {

				if (m_parent != NULL) {
					m_parent->RemoveChild(this);
				}

				if (parent != m_parent) {
					parent->AddChild(this);
				}
			}

			inline void AddChild(GameObject* child) {

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

					m_childCount++;
				}
			}

			inline void RemoveChild(GameObject* child) {

				if (NULL != child) {

					for (unsigned i = m_children.size(); i-- > 0;) {

						if (m_children[i] == child) {
							m_children.erase(m_children.begin() + i);
							child->m_RemoveParent();
							m_childCount--;
							break;
						}
					}
				}
			}

			inline void DetachChildren() {
				GameObject* child;

				for (unsigned i = m_children.size(); i-- > 0;) {
					child = m_children[i];

					m_children.erase(m_children.begin() + i);
					child->m_RemoveParent();
					m_childCount--;
				}
			}

			inline int IndexOf(GameObject* child) {

				if (NULL != child) {

					for (unsigned i = m_children.size(); i-- > 0;) {

						if (m_children[i] == child) {
							return i;
						}
					}
				}

				return -1;
			}
	};
}

#endif