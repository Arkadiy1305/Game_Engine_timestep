#pragma once
#include <array>
#include <iostream>

#include "Timer.h"

class Game {
public:
    Game() { m_keys.fill(false); };
    ~Game() = default;
    void init();
    void update();
    void render();

    void set_key(int key, int action) { m_keys[key] = action; }

private:
    int m_count_frame { 0 };
    Timer m_timer;
    std::array<bool, 348> m_keys;
};
