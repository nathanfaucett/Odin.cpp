#ifndef ODIN_INPUT_HPP
#define ODIN_INPUT_HPP

namespace Odin {
	
	class Input {
		
		private:
			const char* MOUSE0 = "Mouse0";
			const char* MOUSE1 = "Mouse1";
			const char* MOUSE2 = "Mouse2";
			
			uint32 m_frameCount;
			InputButtons m_buttons;
			InputAxes m_axes;
			InputTouches m_inputTouches;
			
		public:
			int32 mouseWheel;
			Vec2f mousePosition, mouseDelta;
			
			inline Input(void) {
				m_frameCount = 0;
			}
			
			inline void HandleEvents(const SDL_Event* event) {
				const char* name;
				float lastX, lastY;
				
				switch (event->type) {
					case SDL_MOUSEMOTION:
						lastX = mousePosition.x;
						lastY = mousePosition.y;
						
						mousePosition.x = event->motion.x;
						mousePosition.y = event->motion.y;
						mouseDelta.x = lastX - mousePosition.x;
						mouseDelta.y = lastY - mousePosition.y;
						break;
					
					case SDL_MOUSEBUTTONDOWN:
						switch(event->button.button) {
							case SDL_BUTTON_LEFT:
								m_buttons.On(MOUSE0);
								break;
							case SDL_BUTTON_MIDDLE:
								m_buttons.On(MOUSE1);
								break;
							case SDL_BUTTON_RIGHT:
								m_buttons.On(MOUSE2);
								break;
						}
						break;
					
					case SDL_MOUSEBUTTONUP:
						switch(event->button.button) {
							case SDL_BUTTON_LEFT:
								m_buttons.Off(MOUSE0);
								break;
							case SDL_BUTTON_MIDDLE:
								m_buttons.Off(MOUSE1);
								break;
							case SDL_BUTTON_RIGHT:
								m_buttons.Off(MOUSE2);
								break;
						}
						break;
					
					case SDL_MOUSEWHEEL:
						mouseWheel = event->wheel.y;
						break;
					
					case SDL_FINGERDOWN:
						m_inputTouches.Start(
							event->tfinger.fingerId,
							event->tfinger.touchId,
							event->tfinger.x,
							event->tfinger.y,
							event->tfinger.pressure
						);
						break;
					
					case SDL_FINGERUP:
						m_inputTouches.End(event->tfinger.fingerId);
						break;
					
					case SDL_FINGERMOTION:
						m_inputTouches.Move(
							event->tfinger.fingerId,
							event->tfinger.x,
							event->tfinger.y,
							event->tfinger.pressure
						);
						break;
					
					case SDL_KEYDOWN:
						name = SDL_GetKeyName(event->key.keysym.sym);
						m_buttons.On(name);
		
						break;
					
					case SDL_KEYUP:
						name = SDL_GetKeyName(event->key.keysym.sym);
						m_buttons.Off(name);
		
						break;
				}
			}
			
			inline void Update(void) {
				float32 dt = Time.delta;
				
				m_frameCount = Time.frameCount;
				
				for (auto it = m_axes.m_axes.begin(); it != m_axes.m_axes.end(); ++it) {
					InputAxis* axis = it->second;
					if (axis == NULL) continue;
					
					float32 value = axis->value,
							sensitivity = axis->sensitivity;
					
					InputButton* button;
					InputButton* altInputButton;
					bool pos = false, neg = false;
					
					switch(axis->type) {
						case InputAxisType::Button:
							
							button = m_buttons.Get(axis->negInputButton);
							altInputButton = m_buttons.Get(axis->altNegInputButton);
							neg = (button != NULL && button->value) || (altInputButton != NULL && altInputButton->value);
		
							button = m_buttons.Get(axis->posInputButton);
							altInputButton = m_buttons.Get(axis->altPosInputButton);
							pos = (button != NULL && button->value) || (altInputButton != NULL && altInputButton->value);
							break;
						
						case InputAxisType::Mouse:
							if (axis->axis < 0 || axis->axis > 1) continue;
							axis->value = mouseDelta[axis->axis];
							continue;
						
						case InputAxisType::MouseWheel:
							value += mouseWheel;
							break;
						
						default:
							continue;
					}
					
					if (neg) value -= sensitivity * dt;
					if (pos) value += sensitivity * dt;
	
					if (!pos && !neg && value != 0.0f) {
						float32 tmp = abs(value);
						value -= Mathf.Clamp(Mathf.Sign(value) * axis->gravity * dt, -tmp, tmp);
					}
	
					value = Mathf.Clamp(value, -1.0f, 1.0f);
					if (Mathf.Abs(value) <= axis->dead) value = 0.0f;
	
					axis->value = value;
				}
			}
			
			inline float32 Axis(std::string name) {
				InputAxis* axis = m_axes.Get(name);
				return (axis != NULL) ? axis->value : 0.0f;
			}
		
			inline bool MouseButton(int32 mouseID) {
				InputButton* button;
				
				switch(mouseID) {
					case 0:
						button = m_buttons.Get(MOUSE0);
						break;
					case 1:
						button = m_buttons.Get(MOUSE1);
						break;
					case 2:
						button = m_buttons.Get(MOUSE2);
						break;
				}
				
				return button != NULL && button->value;
			}
			inline bool MouseButtonDown(int32 mouseID) {
				InputButton* button;
				
				switch(mouseID) {
					case 0:
						button = m_buttons.Get(MOUSE0);
						break;
					case 1:
						button = m_buttons.Get(MOUSE1);
						break;
					case 2:
						button = m_buttons.Get(MOUSE2);
						break;
				}
				
				return button != NULL && button->value && (button->frameDown >= m_frameCount);
			}
			inline bool MouseButtonUp(int32 mouseID) {
				InputButton* button;
				
				switch(mouseID) {
					case 0:
						button = m_buttons.Get(MOUSE0);
						break;
					case 1:
						button = m_buttons.Get(MOUSE1);
						break;
					case 2:
						button = m_buttons.Get(MOUSE2);
						break;
				}
				
				return button != NULL && button->value && (button->frameUp >= m_frameCount);
			}
		
			inline bool AnyKey(void) {
				for (auto it = m_buttons.m_buttons.begin(); it != m_buttons.m_buttons.end(); ++it) {
					if (it->second->value) return true;
				}
				
				return false;
			}
			inline bool AnyKeyDown(void) {
				for (auto it = m_buttons.m_buttons.begin(); it != m_buttons.m_buttons.end(); ++it) {
					if (it->second->value && (it->second->frameDown >= m_frameCount)) return true;
				}
				
				return false;
			}
			inline bool AnyKeyUp(void) {
				for (auto it = m_buttons.m_buttons.begin(); it != m_buttons.m_buttons.end(); ++it) {
					if (it->second->value && (it->second->frameUp >= m_frameCount)) return true;
				}
				
				return false;
			}
			
			inline bool Key(std::string name) {
				InputButton* button = m_buttons.Get(name);
				return button != NULL && button->value;
			}
			inline bool KeyDown(std::string name) {
				InputButton* button = m_buttons.Get(name);
				return button != NULL && button->value && (button->frameDown >= m_frameCount);
			}
			inline bool KeyUp(std::string name) {
				InputButton* button = m_buttons.Get(name);
				return button != NULL && button->value && (button->frameUp >= m_frameCount);
			}
	} Input;
}

#endif