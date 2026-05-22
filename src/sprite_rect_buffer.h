#ifndef _SPRITE_RECT_BUFFER_H
#define _SPRITE_RECT_BUFFER_H

#include <defines.h>
#include <entity.h>
#include <raylib/raylib.h>

struct SpriteRect {
    Rectangle source;
    Vector2 position;
#if DEBUG
    ProjectedBoundaries boundaries;
    Color tint;
    SpriteRect() : source({0,0,0,0}), position({0,0}), boundaries({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}), tint(WHITE) {}
    SpriteRect(Rectangle src, Vector2 pos, ProjectedBoundaries boundaries, Color tint) : source(src), position(pos), boundaries(boundaries), tint(tint) {}
#else
    SpriteRect() : source({0,0,0,0}), position({0,0}) {}
    SpriteRect(Rectangle src, Vector2 pos) : source(src), position(pos) {}
#endif
};

class SpriteRectBuffer {

public:
  uint32_t maxLength;
  uint32_t bufferLength;
  SpriteRect* buffer = nullptr;

  SpriteRectBuffer(uint32_t);
  uint32_t bufferSize() const;
  ~SpriteRectBuffer();
};


#endif
