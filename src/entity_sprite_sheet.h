#ifndef ENTITY_SPRITE_SHEET_H
#define ENTITY_SPRITE_SHEET_H

#include <map>
#include <memory>
#include <optional>
#include <defines.h>
#include <entity_sprite_sheet_animation.h>


class EntitySpriteSheet
{
        std::map<uint16_t, std::unique_ptr<EntitySpriteSheetAnimation>> animations;
public:
        EntitySpriteSheet();
        ~EntitySpriteSheet() = default;
        void AddAnimation(std::unique_ptr<EntitySpriteSheetAnimation>);
        EntitySpriteSheetAnimation* GetAnimationWithId(uint16_t) const;
};

#endif
