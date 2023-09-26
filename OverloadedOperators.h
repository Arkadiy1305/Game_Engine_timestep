#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <iomanip>
#include <numbers>

std::ostream& operator<<(std::ostream& out, const glm::vec2& vec2comp)
{
    out << "x = " << vec2comp.x << " y = " << vec2comp.y << '\n';
    return out;
}

std::ostream& operator<<(std::ostream& out, const glm::mat4& mat4comp)
{    
    out << "printing matrix 4 x 4\n________________________________________________\n" << std::setprecision(3);
    for (size_t i = 0; i < 4; i++) {
        out << "x" << i + 1 << " = " << mat4comp[i].x << '\t'
            << " y" << i + 1 << " = " << mat4comp[i].y << '\t'
            << " z" << i + 1 << " = " << mat4comp[i].z << '\t'
            << " w" << i + 1 << " = " << mat4comp[i].w
            << '\n';
    }
    out << "________________________________________________\n" << std::setprecision(6);
    return out;
}