#ifndef ODIN_INPUT_AXIS_HPP
#define ODIN_INPUT_AXIS_HPP

namespace Odin {

	class InputAxis {
		public:
			std::string name;
	
			std::string negInputButton, posInputButton;
			std::string altNegInputButton, altPosInputButton;
	
			float32 gravity, sensitivity;
			float32 dead;
	
			InputAxisType type;
			int32 axis;
			
			uint32 index;
			uint32 joyNum;
	
			float32 value;
			
			inline InputAxis(void) {
				name = "Unknown";
	
				negInputButton = "Left";
				posInputButton = "Right";
	
				altNegInputButton = "A";
				altPosInputButton = "D";
	
				gravity = 3.0f;
				sensitivity = 3.0f;
	
				dead = 0.001f;
	
				type = InputAxisType::Button;
				axis = 0;
				index = 0;
	
				joyNum = 0;
	
				value = 0.0f;
			}
	};
}

#endif