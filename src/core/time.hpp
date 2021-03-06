#ifndef ODIN_TIME_HPP
#define ODIN_TIME_HPP

namespace Odin {

	class Time {

		private:
			static constexpr float32 TIME_DELTA_MIN = 0.000000001f, TIME_DELTA_MAX = 1.0f;

			float32 m_fpsTime, m_fpsLast, m_time, m_last, m_delta;
			uint32 m_frameCount, m_frames;

			float64 m_start;

		public:
			uint32 frameCount;
			float32 delta, fixedDelta, scale, fps, time;

			Time(void) {
				m_start = Stamp64();

				fixedDelta = 1.0f / 60.0f;
				delta = 1.0f / 60.0f;
				fps = 60.0f;
				scale = 1.0f;
				time = 0.0f;

				m_fpsTime = 0.0f;
				m_fpsLast = -1.0f;

				m_time = 0.0f;
				m_last = -1.0f / 60.0f;
				m_delta = 1.0f / 60.0f;
			}

			~Time(void) {}

			inline void Update(void) {
				frameCount = m_frameCount++;

				m_last = m_time;
				m_time = Now();
				m_delta = (m_time - m_last) * scale;

				delta = m_delta < TIME_DELTA_MIN ? TIME_DELTA_MIN : m_delta > TIME_DELTA_MAX ? TIME_DELTA_MAX : m_delta;
				time = m_time * scale;

				m_fpsTime = m_time;
				m_frames++;

				if (m_fpsLast + 1.0f < m_fpsTime) {
					fps = (m_frames) / (m_fpsTime - m_fpsLast);

					m_fpsLast = m_fpsTime;
					m_frames = 0.0f;
				}
			}

			inline float64 Now64(void) {

				return Stamp64() - m_start;
			}
			inline float64 Stamp64(void) {

				return (std::chrono::high_resolution_clock::now().time_since_epoch() / std::chrono::nanoseconds(1)) * 0.000000001;
			}

			inline float32 Now(void) {

				return static_cast<float32>(Now64());
			}
			inline float32 Stamp(void) {

				return static_cast<float32>(Stamp64());
			}
	} Time;
}

#endif