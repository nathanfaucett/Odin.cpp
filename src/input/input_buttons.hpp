#ifndef ODIN_INPUT_BUTTONS_HPP
#define ODIN_INPUT_BUTTONS_HPP

namespace Odin {

	class InputButtons {

		private:
			friend class Input;
			std::unordered_map<std::string, InputButton*> m_buttons;

		public:
			
			inline InputButtons(void) {
				
			}
			inline ~InputButtons(void) {
				m_buttons.clear();
			}
			
			inline InputButton* Get(std::string name) {
				return m_buttons[name];
			}
			
			inline InputButton* On(const char* name) {
				InputButton* button = m_buttons[name];
				
				if (button == NULL) {
					button = new InputButton(name);
					m_buttons[name] = button;
				}
				
				if (button->m_first) {
					button->frameDown = Time.frameCount + 1;
					button->timeDown = Time.Stamp();
					button->m_first = false;
				}
				button->value = true;
				
				return button;
			}
			
			inline InputButton* Off(const char* name) {
				InputButton* button = m_buttons[name];
				
				if (button == NULL) {
					button = new InputButton(name);
					m_buttons[name] = button;
				}
				
				if (!button->m_first) {
					button->frameUp = Time.frameCount + 1;
					button->timeUp = Time.Stamp();
					button->value = false;
					button->m_first = true;
				}
				
				return button;
			}
	};
}

#endif