#ifndef _ODIN_COMPONENT_H
#define _ODIN_COMPONENT_H

namespace Odin {

	class GameObject;

	enum ComponentType {
		CameraComponent,
	};

	class Component : public Object {

		private:
			friend class GameObject;
			ComponentType m_type;
			GameObject* m_gameObject;

		protected:

		public:

			inline explicit Component(void);

			inline ~Component(void);

			inline void virtual Deconstructor(void);

			inline void virtual Update(void);

			inline void Destroy(void);

			inline GameObject* GetGameObject(void);
	};
}

#endif