#ifndef ODIN_TIME_H
#define ODIN_TIME_H

namespace Odin {
	
	class Time{
		static constexpr double TIME_DELTA_MIN = 0.000000001, TIME_DELTA_MAX = 1;
		
		private:
			double m_start, m_fpsTime, m_fpsLast, m_time, m_last, m_delta;
			unsigned int m_frameCount, m_frames;
			
		public:
			unsigned int frameCount;
			double delta, fixedDelta, scale, fps, time;
			
			Time() {
				fixedDelta = 1/60;
				delta = 1/60;
				fps = 60;
				scale = 1;
				time = 0;
				
				m_fpsTime = 0;
				m_fpsLast = -1;
				
				m_start = stamp();
				m_time = 0;
				m_last = -1/60;
				m_delta = 1/60;
			}
			
			~Time() {}
			
			inline void update() {
				frameCount = m_frameCount++;
			
				m_last = m_time;
				m_time = now();
				m_delta = (m_time - m_last) * scale;
			
				delta = m_delta < TIME_DELTA_MIN ? TIME_DELTA_MIN : m_delta > TIME_DELTA_MAX ? TIME_DELTA_MAX : m_delta;
				time = m_time * scale;
				
				m_fpsTime = m_time;
				m_frames++;
			
				if (m_fpsLast + 1 < m_fpsTime) {
					fps = (m_frames) / (m_fpsTime - m_fpsLast);
				
					m_fpsLast = m_fpsTime;
					m_frames = 0;
				}
			}
			
			inline double now() {
				
				return stamp() - m_start;
			}
			
			inline double stamp() {
				
				return (std::chrono::high_resolution_clock::now().time_since_epoch() / std::chrono::nanoseconds(1)) * 0.000000001;
			}
	};
    
    Time Time;
}

#endif