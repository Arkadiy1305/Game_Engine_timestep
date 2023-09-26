#include "Game.h"

void Game::init() { m_timer.start(); }

void Game::update()
{
    m_timer.tick();
    while (m_timer.get_accumulator() >= m_timer.get_m_max_fps_frame_time()) {
        ++m_count_frame;
        std::cout << "Count_frame = " << m_count_frame << '\n';
        m_timer.reduce_accumulator();
    }
}

void Game::render() { std::cout << "alpha = " << m_timer.get_alpha() << '\n'; }
