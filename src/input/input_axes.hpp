#ifndef ODIN_AXES_HPP
#define ODIN_AXES_HPP

namespace Odin {

	class InputAxes {

		private:
			friend class Input;
			std::unordered_map<std::string, InputAxis*> m_axes;

		public:
			
			inline InputAxes(void) {
				
				InputAxis* Horizontal = new InputAxis();
				Horizontal->name = "Horizontal";
				Horizontal->posInputButton = "Right";
				Horizontal->negInputButton = "Left";
				Horizontal->altPosInputButton = "A";
				Horizontal->altNegInputButton = "D";
				Add(Horizontal);
				
				InputAxis* Vertical = new InputAxis();
				Vertical->name = "Vertical";
				Vertical->posInputButton = "Up";
				Vertical->negInputButton = "Down";
				Vertical->altPosInputButton = "W";
				Vertical->altNegInputButton = "S";
				Add(Vertical);
				
				InputAxis* Fire = new InputAxis();
				Fire->name = "Fire";
				Fire->posInputButton = "Crtl";
				Fire->negInputButton = "";
				Fire->altPosInputButton = "Mouse0";
				Fire->altNegInputButton = "";
				Add(Fire);
				
				InputAxis* MouseX = new InputAxis();
				MouseX->name = "MouseX";
				MouseX->type = InputAxisType::Mouse;
				MouseX->axis = 0;
				Add(MouseX);
				
				InputAxis* MouseY = new InputAxis();
				MouseY->name = "MouseY";
				MouseY->type = InputAxisType::Mouse;
				MouseY->axis = 1;
				Add(MouseY);
				
				InputAxis* MouseWheel = new InputAxis();
				MouseWheel->name = "MouseWheel";
				MouseWheel->type = InputAxisType::MouseWheel;
				Add(MouseWheel);
			}
			inline ~InputAxes(void) {
				m_axes.clear();
			}
			
			inline InputAxis* Add(InputAxis* axis) {
				if (m_axes.count(axis->name) != 0) {
					LogError("InputAxis* Add(InputAxis* axis) InputAxis already member of InputAxis");
					return NULL;
				}
				m_axes[axis->name] = axis;
				
				return axis;
			}
			inline InputAxis* Get(std::string name) {
				return m_axes[name];
			}
	};
}

#endif