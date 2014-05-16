#ifndef ODIN_INPUT_TOUCH_HPP
#define ODIN_INPUT_TOUCH_HPP

namespace Odin {

	class InputTouch {

		private:
			friend class InputTouches;
			friend class Input;
			
			int32 m_id;
			bool m_first;
			
		public:
            float32 radiusX, radiusY, rotationAngle, force;
            Vec2f delta, position;
			
			inline InputTouch(void) {
				m_id = -1;
				m_first = false;
				
				radiusX = 0.0f;
				radiusY = 0.0f;
				rotationAngle = 0.0f;
				force = 0.0f;
			}
			
			inline void Clear(void) {
				m_id = -1;
				m_first = false;
				
				radiusX = 0.0f;
				radiusY = 0.0f;
				rotationAngle = 0.0f;
				force = 0.0f;
	
				delta.Set(0.0f, 0.0f);
				position.Set(0.0f, 0.0f);
			}
	};
}

#endif