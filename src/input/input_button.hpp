#ifndef ODIN_INPUT_BUTTON_HPP
#define ODIN_INPUT_BUTTON_HPP

namespace Odin {

	class InputButton {

		private:
			friend class InputButtons;
			friend class Input;
			
            bool m_first;
			std::unordered_map<const char*, InputButton*> m_components;

		public:
			const char* name;

            float32 timeDown, timeUp;
			uint32 frameDown, frameUp;

            bool value;
			
			inline InputButton(const char* Name) {
				name = Name;
				
				timeDown = 0.0f;
				timeUp = 0.0f;
	
				frameDown = 0;
				frameUp = 0;
	
				value = false;
				m_first = true;
			}
			inline ~InputButton(void) {
				
			}
	};
}

#endif