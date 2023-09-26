#pragma once
#include <chrono>

class Timer {
public:
    Timer() = default;
    ~Timer() = default;

    void start() { m_lasttime = std::chrono::system_clock::now(); }
    void tick()
    {
        auto now = std::chrono::system_clock::now();
        m_frame_time = std::chrono::duration_cast<std::chrono::microseconds>(now - m_lasttime).count();
        if (m_frame_time > m_max_frame_time) {
            m_frame_time = m_max_frame_time;
        }
        m_lasttime = now;
        m_accumulator += m_frame_time;
     };

    inline time_t get_accumulator() { return m_accumulator; }
    inline const time_t get_m_max_fps_frame_time() { return m_max_fps_frame_time; }
    inline void reduce_accumulator() { m_accumulator -= m_max_fps_frame_time; }

    inline double get_alpha() { return static_cast<double>(m_accumulator) / m_max_fps_frame_time; }


private:
    const time_t m_fps { 30 };
    const time_t m_max_frame_time { 1000000 / 10 };
    time_t m_frame_time { 0 };
    time_t m_accumulator { 0 };
    const time_t m_max_fps_frame_time { 1000000 / m_fps };
    std::chrono::time_point<std::chrono::system_clock> m_lasttime { std::chrono::system_clock::now() };
};
