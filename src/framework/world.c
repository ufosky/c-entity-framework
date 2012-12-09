#include <stdlib.h>
#include <stdio.h>

#include "world.h"
#include "intrusive_linked_list.h"
#include "game_system.h"

typedef struct world {
    EntityManager entityManager;
    ComponentManager componentManager;
    IntrusiveList systems;
    unsigned int processing;
} internalWorld;

World CreateWorld(void) {
    World newWorld = malloc(sizeof(internalWorld));
    newWorld->processing = 0;

    newWorld->systems = CreateIntrusiveList();

    GameSystem renderSystem = CreateSystem(RENDER_SYSTEM);
    AddHead(newWorld->systems, &(renderSystem->listNode));

    GameSystem inputSystem = CreateSystem(KEYBOARD_INPUT_SYSTEM);
    AddHead(newWorld->systems, &(inputSystem->listNode));

    return newWorld;
}

void FreeWorld(World world) {
    IntrusiveListNodePtr iter = Next(Head(world->systems));
    IntrusiveListNodePtr head = Head(world->systems);

    while (iter != head) {
        GameSystem system = container_of(iter, struct gameSystem, listNode);
        iter = Next(iter);
        Remove(&(system->listNode));
        FreeSystem(system);
    }

    FreeIntrusiveList(world->systems);
    free(world);
}

void Process(World world) {
    IntrusiveListNodePtr iter = Next(Head(world->systems));
    IntrusiveListNodePtr head = Head(world->systems);

    while (iter != head) {
        GameSystem system = container_of(iter, struct gameSystem, listNode);
        system->processFunction(world, system->entities);
        iter = Next(iter);
    }
}

void AddEntity(World world, Entity entity) {
    IntrusiveListNodePtr iter = Next(Head(world->systems));
    IntrusiveListNodePtr head = Head(world->systems);

    while (iter != head) {
        GameSystem system = container_of(iter, struct gameSystem, listNode);

        unsigned int compareResult = CompareBitSets(entity->componentDescriptor, system->componentDescriptor);

        //For now all of the components listed by the system have to be fulfilled.
        if (compareResult == IntValueOfBitSet(system->componentDescriptor)) {
            AddEntityToSystem(system, entity);
        }

        iter = Next(iter);
    }
}

void RemoveEntity(World world, Entity entity) {
    //Remove entity from all systems
    Remove(&(entity->renderSystemListNode));
}

void EntityComponentsChanged(World world, Entity entity) {
    //Readd entity to world
    RemoveEntity(world, entity);
    AddEntity(world, entity);
}

void LinkComponentManagerToWorld(World world, ComponentManager componentManager) {
    world->componentManager = componentManager;
}

void LinkEntityManagerToWorld(World world, EntityManager entityManager) {
    world->entityManager = entityManager;
}

Component GetComponentByType(World world, Entity entity, ComponentType componentType) {
    return GetComponentForEntity(world->componentManager, entity, componentType);
}

void EnableWorld(World world) {
    world->processing = 1;
}

void DisableWorld(World world) {
    world->processing = 0;
}

unsigned int IsWorldEnabled(World world) {
    return 1 == world->processing;
}
