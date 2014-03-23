#ifndef _ODIN_COMPONENT_H_
#define _ODIN_COMPONENT_H_

namespace Odin {

	class Scene;
	class GameObject;

	class Component : public Object {

		private:
			friend class Scene;
			friend class GameObject;

		protected:
			int32 p_order;
			GameObject* p_gameObject;

			inline virtual void p_Clear(void);

			inline virtual void p_Init(void);
			inline virtual void p_Start(void);
			inline virtual void p_Update(void);

			inline static float32 p_Sort(Component* a, Component* b);

		public:
			inline Component(void);
			inline ~Component(void);

			inline GameObject* GetGameObject(void);
			inline Scene* GetScene(void);
	};
}

#endif