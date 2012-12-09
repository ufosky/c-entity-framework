#include "intrusive_linked_list.h"
#include "entity.h"
#include "component.h"
#include "world.h"
#include "SDL/SDL.h"

#include <stdio.h>

void RenderSystemProcess(World world, IntrusiveList entities) {
    IntrusiveListNodePtr iter = Next(Head(entities));
    IntrusiveListNodePtr head = Head(entities);

    while (iter != head) {
        Entity entity = container_of(iter, struct entity, renderSystemListNode);

        PositionComponent positionComponent = GetComponentByType(world, entity, POSITION)->positionComponent;
        SpriteComponent spriteComponent = GetComponentByType(world, entity, SPRITE)->spriteComponent;

        SDL_Rect heroPos;
        heroPos.h = 32;
        heroPos.w = 32;
        heroPos.x = 32*positionComponent->x;
        heroPos.y = 32*positionComponent->y;

        SDL_BlitSurface(spriteComponent->image->bitmap->surface, NULL, SDL_GetVideoSurface(), &heroPos);

        iter = Next(iter);
    }
}
