#include "intrusive_linked_list.h"
#include "entity.h"
#include "component.h"
#include "world.h"
#include "SDL/SDL.h"

#include <stdio.h>

void KeyboardInputSystemProcess(World world, IntrusiveList entities) {
    IntrusiveListNodePtr iter = Next(Head(entities));
    IntrusiveListNodePtr head = Head(entities);

    while (iter != head) {
        Entity entity = container_of(iter, struct entity, keyboardInputSystemListNode);

        PositionComponent positionComponent = GetComponentByType(world, entity, POSITION)->positionComponent;
        KeyboardInputComponent keyboardInputComponent = GetComponentByType(world, entity, KEYBOARD_INPUT)->keyboardInputComponent;

        Uint8* keystate = SDL_GetKeyState(NULL);

        if (keystate[SDLK_ESCAPE]) {
            DisableWorld(world);
            keystate[SDLK_ESCAPE] = 0;
        } else if (keystate[SDLK_UP]) {
            positionComponent->y--;
            keystate[SDLK_UP] = 0;
        } else if (keystate[SDLK_DOWN]) {
            positionComponent->y++;
            keystate[SDLK_DOWN] = 0;
        } else if (keystate[SDLK_LEFT]) {
            positionComponent->x--;
            keystate[SDLK_LEFT] = 0;
        } else if (keystate[SDLK_RIGHT]) {
            positionComponent->x++;
            keystate[SDLK_RIGHT] = 0;
        }

        iter = Next(iter);
    }
}
