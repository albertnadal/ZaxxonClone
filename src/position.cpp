#include <iostream>
#include <position.h>

Position::Position() {
    x = y = z = 0.0f;
    x_offset = y_offset = z_offset = 0.0f;
    projected_x = projected_y = 0.0f;
}

Vector2 Position::GetProjectedCoordinate() const {
    return { projected_x, projected_y };
}

Vector2 Position::AddAndGetProjectedCoordinate(Position _p, float _x, float _y, float _z) {
    Position p;
    p.Copy(_p);
    p.AddX(_x);
    p.AddY(_y);
    p.AddZ(_z);
    return p.GetProjectedCoordinate();
}

Vector3 Position::GetCoordinates() const {
    return { x, y, z };
}

Vector3 Position::GetOffset() const {
    return { x_offset, y_offset, z_offset };
}

void Position::CalculateProjectionCoordinate() {
    // 0.5 is the tangent of 26.565 degrees, which is used for calculating the isometric projection
    projected_y = y + x * 0.5; // Projection on the Y axis from the X axis
    projected_y = projected_y + z * -0.5; // Projection on the Y axis from the Z axis
    projected_x = x + z; // Projection on the X axis from the Z axis
}

void Position::SetXYZ(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
    CalculateProjectionCoordinate();
}

void Position::SetXYZOffset(float _x, float _y, float _z) {
    x_offset = _x;
    y_offset = _y;
    z_offset = _z;
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

void Position::Copy(Position position) {
    Vector3 coordinates = position.GetCoordinates();
    Vector3 coordinatesOffset = position.GetOffset();
    x = coordinates.x;
    y = coordinates.y;
    z = coordinates.z;
    x_offset = coordinatesOffset.x;
    y_offset = coordinatesOffset.y;
    z_offset = coordinatesOffset.z;
    CalculateProjectionCoordinate();
}

Position::~Position() {
}
