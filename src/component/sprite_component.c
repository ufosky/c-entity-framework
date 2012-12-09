#include <stdlib.h>

#include "component.h"
#include "resource_manager.h"

SpriteComponent CreateSpriteComponent(ResourceManager resourceManager, char* spriteName) {
    SpriteComponent obj = malloc(sizeof(struct spriteComponent));
    obj->spriteName = spriteName;
    obj->image = GetResource(resourceManager, spriteName, BMP);

    return obj;
}

void FreeSpriteComponent(SpriteComponent spriteComponent) {
    free(spriteComponent);
}
