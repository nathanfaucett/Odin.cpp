#ifndef ODIN_COMPONENT_H
#define ODIN_COMPONENT_H

namespace Odin {

	class Scene;
	class GameObject;
	class Renderer;

	class Component : public Object {

		private:
			friend class Scene;
			friend class GameObject;

		protected:
			int32 p_updateOrder;
			float32 p_order;
			GameObject* p_gameObject;

			inline virtual void p_Clear(void);

			inline virtual void p_Init(void);
			inline virtual void p_Start(void);
			inline virtual void p_Update(void);

			inline virtual void p_Sort(void);

		public:
			inline Component(void);
			inline Component(std::string Name);
			inline Component(const Component& other);
			inline Component(const Component&& other);
			inline ~Component(void);

			inline virtual Component& Copy(const Component& other);
			inline virtual Component& Move(const Component&& other);
			
			inline GameObject* GetGameObject(void);
			inline Scene* GetScene(void);
			
			inline Component& operator =(const Component& other);
			inline Component& operator =(const Component&& other);
	};
}

#endif