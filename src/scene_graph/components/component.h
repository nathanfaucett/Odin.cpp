#ifndef ODIN_COMPONENT_H
#define ODIN_COMPONENT_H

namespace Odin {
	
	class Scene;
	class GameObject;
	
	class Component : public Object {
		private:
			friend class Scene;
			friend class GameObject;

		protected:
			GameObject* p_gameObject;
			
			inline virtual void p_Init(void);
			inline virtual void p_Start(void);
			inline virtual void p_Sort(void);

		public:
			inline Component(void);
			inline Component(const Component&) = default;
			inline Component(Component&&) = default;
			inline virtual ~Component(void);

			inline virtual Component* Clone(void);
			inline virtual Component& Copy(const Component& other);

			inline virtual void Update(void);
			inline virtual void Clear(void);
			inline static float32 Sort(Component* a, Component* b);
			
			inline GameObject* GetGameObject(void);
			inline Scene* GetScene(void);
			template <typename Type>inline Type* GetComponent(void);
			
			inline Component& operator=(const Component&)& = default;
			inline Component& operator=(Component&&)& = default;
	};
}

#endif