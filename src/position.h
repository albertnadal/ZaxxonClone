#ifndef POSITION_H
#define POSITION_H

#include <defines.h>

class Position
{
private:
  float x, y, z;
  float projected_x, projected_y;

  inline float CalculateProjectedY() const;
public:
  Position();
  ~Position();

  Vector2 GetProjectedCoordinate() const;
  void SetXYZ(float, float, float);
  void AddX(float);
  void AddY(float);
  float GetProjectedX() const;
  float GetProjectedY() const;
};

#endif
