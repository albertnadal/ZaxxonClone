#include <cmath>
#include <limits>
#include <iostream>
#include <position.h>

Position::Position() {
    x = y = z = 0.0f;
    projected_x = projected_y = 0.0f;
}

Vector2 Position::GetProjectedCoordinate() const {
    return { projected_x, projected_y };
}

float Position::GetProjectedX() const {
    return projected_x;
}

float Position::GetProjectedY() const {
    return projected_y;
}

inline float Position::CalculateProjectedY() const {
    return y + 100.0f + x * 0.57735f; // Projection on the Y axis for isometric view
}

void Position::SetXYZ(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
    projected_x = x;
    projected_y = CalculateProjectedY();
}

void Position::AddX(float _x) {
    x += _x;
    projected_x = x;
    projected_y = CalculateProjectedY();
}

void Position::AddY(float _y) {
    y += _y;
    projected_y = CalculateProjectedY();
}

Position::~Position() {
}
