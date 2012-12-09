/**
 * system.h
 */
#ifndef GAMESYSTEM_HEADER_SEEN
#define GAMESYSTEM_HEADER_SEEN

#include "intrusive_linked_list.h"
#include "bitset.h"
#include "entity.h"

//Forward Declaration
typedef struct world* World;

typedef void (*ProcessFunctionPtr)(World world, IntrusiveList entities);

typedef enum {
    RENDER_SYSTEM,
    KEYBOARD_INPUT_SYSTEM,
    NUM_SYSTEM_TYPES
} SystemType;

typedef struct gameSystem* GameSystem;

struct gameSystem {
    SystemType type;
    ComponentDescriptor componentDescriptor;
    IntrusiveList entities;
    ProcessFunctionPtr processFunction;
    IntrusiveListNode listNode;
};

GameSystem CreateSystem(SystemType systemType);
void FreeSystem(GameSystem system);

void AddEntityToSystem(GameSystem system, Entity entity);
void RemoveEntityFromSystem(GameSystem system, Entity entity);

#endif
