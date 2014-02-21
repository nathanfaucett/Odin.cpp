#ifndef ODIN_COMPONENT_H
#define ODIN_COMPONENT_H

namespace Odin {

	class Component : public Object {

		private:

		protected:

		public:

			Component();

			~Component() {
				Deconstructor();
			}

			inline void virtual Deconstructor() {
				
			}

			inline void Destroy() {
				
			}

			inline void virtual Update() {
				
			}
	};
}

#endif