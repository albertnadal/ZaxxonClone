#include <sprite_rect_buffer.h>

SpriteRectBuffer::SpriteRectBuffer(uint32_t _maxLength) {
        maxLength = _maxLength;
        bufferLength = 0;
        buffer = new SpriteRect[maxLength];
}

uint32_t SpriteRectBuffer::bufferSize() const
{
        return (maxLength * sizeof(SpriteRect));
}

SpriteRectBuffer::~SpriteRectBuffer() {
        if(buffer != nullptr) {
                delete[] buffer;
        }
}
