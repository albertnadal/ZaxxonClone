#include <entity_sprite_sheet.h>

EntitySpriteSheet::EntitySpriteSheet() {
}

void EntitySpriteSheet::AddAnimation(std::unique_ptr<EntitySpriteSheetAnimation> animation) {
  if (!animation) return;
  uint16_t id = animation->Id;
  animations.emplace(id, std::move(animation));
}

EntitySpriteSheetAnimation* EntitySpriteSheet::GetAnimationWithId(uint16_t AnimationId) const {
    auto it = animations.find(AnimationId);
    if (it != animations.end()) {
        return it->second.get();
    }

    return nullptr;
}
