#ifndef POSITION_H
#define POSITION_H

#include <defines.h>

class Position
{
private:
  float x, y, z;
  float x_offset, y_offset, z_offset;
  float projected_x, projected_y;

  void CalculateProjectionCoordinate();
public:
  Position();
  ~Position();
  Vector2 GetProjectedCoordinate() const;
  static Vector2 AddAndGetProjectedCoordinate(Position, float, float, float);
  Vector3 GetCoordinates() const;
  Vector3 GetOffset() const;
  Vector3 GetCoordinatesWithOffset() const;
  void SetXYZ(float, float, float);
  void SetXYZOffset(float, float, float);
  void AddX(float);
  void AddY(float);
  void AddZ(float);
  void Copy(Position);
};

#endif
