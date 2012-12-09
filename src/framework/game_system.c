#include <stdlib.h>
#include <assert.h>

#include "game_system.h"
#include "component.h"

/*Forward declaration of system specific process methods.*/
void RenderSystemProcess(World world, IntrusiveList entities);
void KeyboardInputSystemProcess(World world, IntrusiveList entities);

GameSystem CreateSystem(SystemType systemType) {
    GameSystem obj = NULL;

    switch (systemType) {
    case RENDER_SYSTEM:
        obj = malloc(sizeof(struct gameSystem));
        obj->processFunction = &RenderSystemProcess;
        obj->listNode = CreateIntrusiveListNodeWithDebugDescriptor("RenderSystem");
        obj->componentDescriptor = CreateBitSet(NUM_COMPONENT_TYPES);
        //Render system is interested in all entities with position and sprite components
        SetBit(obj->componentDescriptor, POSITION);
        SetBit(obj->componentDescriptor, SPRITE);
        obj->type = RENDER_SYSTEM;
        obj->entities = CreateIntrusiveList();
        break;
    case KEYBOARD_INPUT_SYSTEM:
        obj = malloc(sizeof(struct gameSystem));
        obj->processFunction = &KeyboardInputSystemProcess;
        obj->listNode = CreateIntrusiveListNodeWithDebugDescriptor("KeyboardInputSystem");
        obj->componentDescriptor = CreateBitSet(NUM_COMPONENT_TYPES);
        //Render system is interested in all entities with position and sprite components
        SetBit(obj->componentDescriptor, POSITION);
        SetBit(obj->componentDescriptor, KEYBOARD_INPUT);
        obj->type = KEYBOARD_INPUT_SYSTEM;
        obj->entities = CreateIntrusiveList();
        break;
    default:
        assert(0);
    }

    assert(NULL != obj);

    return obj;
}

void FreeSystem(GameSystem system) {
    FreeIntrusiveList(system->entities);
    FreeBitSet(system->componentDescriptor);
    free(system);
}

void AddEntityToSystem(GameSystem system, Entity entity) {
    switch (system->type) {
    case RENDER_SYSTEM:
        AddHead(system->entities, &(entity->renderSystemListNode));
        break;
    case KEYBOARD_INPUT_SYSTEM:
        AddHead(system->entities, &(entity->keyboardInputSystemListNode));
        break;
    default:
        assert(0);
    }
}

void RemoveEntityFromSystem(GameSystem system, Entity entity) {
    switch (system->type) {
    case RENDER_SYSTEM:
        Remove(&(entity->renderSystemListNode));
        break;
    case KEYBOARD_INPUT_SYSTEM:
        Remove(&(entity->keyboardInputSystemListNode));
        break;
    default:
        assert(0);
    }
}
