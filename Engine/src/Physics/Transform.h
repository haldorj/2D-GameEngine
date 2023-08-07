#pragma once

#include <iostream>
#include <string>

#include "glm/glm.hpp"

class Transform
{
public:
    float X,Y;

    Transform(float x=0, float y=0): X(x), Y(y) {}
    void Log(std::string msg = "")
    {
        std::cout << msg << "(X Y) = " << "(" << X << " " << Y << ")\n";
    }
private:
    void TranslateX(float x) { X += x; }
    void TranslateY(float x) { X += x; }
    void Translate(glm::vec2 v) { X += v.x; Y += v.y; }
};