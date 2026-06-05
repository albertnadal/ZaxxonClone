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

Vector2 Position::AddAndGetProjectedCoordinate(const Position& _p, float _x, float _y, float _z) {
    const float absoluteX = _p.x + _p.x_offset + _x;
    const float absoluteY = _p.y + _p.y_offset + _y;
    const float absoluteZ = _p.z + _p.z_offset + _z;
    return ProjectFromAbsolute(absoluteX, absoluteY, absoluteZ);
}

Vector3 Position::GetCoordinates() const {
    return { x, y, z };
}

Vector3 Position::GetCoordinatesWithOffset() const {
    return { x + x_offset, y + y_offset, z + z_offset };
}

void Position::CalculateProjectionCoordinate() {
    const float absoluteX = x + x_offset;
    const float absoluteY = y + y_offset;
    const float absoluteZ = z + z_offset;
    Vector2 p = ProjectFromAbsolute(absoluteX, absoluteY, absoluteZ);
    projected_x = p.x;
    projected_y = p.y;
}

Vector2 Position::ProjectFromAbsolute(float absoluteX, float absoluteY, float absoluteZ) {
    // 0.5 is the tangent of 26.565 degrees, which is used for calculating the isometric projection
    const float projY = absoluteY + absoluteX * 0.5f - absoluteZ * 0.5f;
    const float projX = absoluteX + absoluteZ;
    return { projX, projY };
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

void Position::Copy(const Position& position) {
    x = position.x;
    y = position.y;
    z = position.z;
    x_offset = position.x_offset;
    y_offset = position.y_offset;
    z_offset = position.z_offset;
    CalculateProjectionCoordinate();
}
