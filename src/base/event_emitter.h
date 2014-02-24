#ifndef ODIN_EVENT_EMITTER_H
#define ODIN_EVENT_EMITTER_H

namespace Odin {

	class EventArg() {
			int type;
			int value;

			inline explicit EventArg() {
				type = D_EVENT_INTEGER;
				value = 0;
			}
	}

	class EventEmitter {

		private:
			unsigned int m_id;

		protected:


		public:
			inline explicit EventEmitter(void);
			inline EventEmitter(const EventEmitter& other);
			inline EventEmitter(const EventEmitter&& other);
			inline ~EventEmitter(void);

			inline std::string ToString(void);
	};
}

#endif