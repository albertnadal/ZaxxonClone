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

void Position::CalculateProjectionCoordinate() {
    // 0.5 is the tangent of 26.565 degrees, which is used for calculating the isometric projection
    projected_y = y + 100.0f + x * 0.5; // Projection on the Y axis from the X axis
    projected_y = projected_y + z * -0.5; // Projection on the Y axis from the Z axis
    projected_x = x + z; // Projection on the X axis from the Z axis
}

void Position::SetXYZ(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
    CalculateProjectionCoordinate();
}

void Position::AddX(float _x) {
    x += _x;
    CalculateProjectionCoordinate();
}

void Position::AddY(float _y) {
    y += _y;
    CalculateProjectionCoordinate();
}

void Position::AddZ(float _z) {
    z += _z;
    CalculateProjectionCoordinate();
}

Position::~Position() {
}
