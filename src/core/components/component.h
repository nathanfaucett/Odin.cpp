#ifndef ODIN_COMPONENT_H
#define ODIN_COMPONENT_H

namespace Odin {

	class Component : public Object {

		private:

		protected:

		public:

			inline explicit Component(void);

			inline ~Component(void);

			inline void virtual Deconstructor(void);

			inline void virtual Update(void);
			
			inline void Destroy(void);
	};
}

#endif