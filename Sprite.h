#pragma once
#include <glm/glm.hpp>

class Sprite {
public:
    Sprite(const glm::vec2& position, const float angle, const glm::vec2& size);
    Sprite() = delete;

private:
    glm::vec2 m_position;
    float m_angle;
    glm::vec2 m_size;
};