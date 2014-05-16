#ifndef ODIN_INPUT_TOUCHES_HPP
#define ODIN_INPUT_TOUCHES_HPP

namespace Odin {

	class InputTouches {

		private:
			friend class Input;
			Array<InputTouch*> m_touches;
			
		public:
			
			inline InputTouches(void) {
				
			}
			inline ~InputTouches(void) {
				
			}
			
			inline void Start(int32 fingerId, int32 touchId, float32 x, float32 y, float32 pressure) {
				InputTouch* touch = m_touches[fingerId];
				if (touch == NULL) {
					m_touches.Push((touch = new InputTouch()));
				} else {
					touch->Clear();
				}
				
				touch->m_id = touchId;
				touch->position.x = x;
				touch->position.y = y;
				touch->force = pressure;
			}
			
			inline void End(int32 fingerId) {
				InputTouch* touch = m_touches[fingerId];
				touch->Clear();
			}
			
			inline void Move(int32 fingerId, float32 x, float32 y, float32 pressure) {
				InputTouch* touch = m_touches[fingerId];
				if (touch == NULL) {
					m_touches.Push((touch = new InputTouch()));
				} else {
					touch->Clear();
				}
				float32 lastX = touch->position.x,
						lastY = touch->position.y;
				
				touch->delta.x = lastX - x;
				touch->delta.y = lastY - y;
				touch->position.x = x;
				touch->position.y = y;
				touch->force = pressure;
			}
	};
}

#endif