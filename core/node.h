#ifndef ODIN_NODE_H
#define ODIN_NODE_H

namespace Odin {
	
    class Node : public Object{
		
		private:
			std::vector<Node*> m_children;
			
			Node* m_parent;
			Node* m_root;
			unsigned int m_depth;
			unsigned int m_childCount;
			
			inline void m_RemoveParent() {
				
				m_depth = 0;
				m_root = this;
				m_parent = NULL;
			}
			
			inline void m_UpdateDepth(unsigned int depth) {
				m_depth = depth;
				for (unsigned i = m_children.size(); i-- > 0;) m_children[i]->m_UpdateDepth(depth + 1);
			}
			
		protected:
		
		public:
			
			Node() {
				m_depth = 0;
				m_childCount = 0;
				m_parent = NULL;
				m_root = this;
			}
			
			~Node() {
				Destroy();
			}
			
			inline void virtual Destroy() {
				m_children.clear();
				m_parent = NULL;
				m_root = NULL;
			}
			
			inline Node* operator [] (int i) {
				return m_children[i];
			}
			
			inline Node* GetParent() const {
				
				return m_parent;
			}
			
			inline unsigned int GetDepth() const {
				
				return m_depth;
			}
			
			inline void SetParent(Node* parent) {
				
				if (m_parent != NULL) {
					m_parent->RemoveChild(this);
				}
				if (parent != m_parent) {
					parent->AddChild(this);
				}
			}
			
			inline void AddChild(Node* child) {
				
				if(child != NULL) {
					if (child->m_parent != NULL) {
						child->m_parent->RemoveChild(child);
					}
					
					m_children.push_back(child);
					child->m_parent = this;
					
					Node* root = this;
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
			
			inline void RemoveChild(Node* child) {
				
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
				Node* child;
				
				for (unsigned i = m_children.size(); i-- > 0;) {
					child = m_children[i];
			
					m_children.erase(m_children.begin() + i);
					child->m_RemoveParent();
					m_childCount--;
				}
			}
			
			inline int IndexOf(Node* child) {
				
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