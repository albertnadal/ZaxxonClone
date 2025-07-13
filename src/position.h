#ifndef POSITION_H
#define POSITION_H

#include <defines.h>

class Position
{
private:
  float x, y, z;
  float projected_x, projected_y;

  void CalculateProjectionCoordinate();
public:
  Position();
  ~Position();

  Vector2 GetProjectedCoordinate() const;
  void SetXYZ(float, float, float);
  void AddX(float);
  void AddY(float);
  void AddZ(float);
  float GetProjectedX() const;
  float GetProjectedY() const;
};

#endif
