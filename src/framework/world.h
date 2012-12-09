/**
 * world.h
 *
 */
#ifndef WORLD_HEADER_SEEN
#define WORLD_HEADER_SEEN

#include "component_manager.h"
#include "entity_manager.h"
#include "entity.h"

typedef struct world* World;

World CreateWorld(void);
void FreeWorld(World);

void Process(World world);

void LinkComponentManagerToWorld(World world, ComponentManager componentManager);
void LinkEntityManagerToWorld(World world, EntityManager entityManager);

Component GetComponentByType(World world, Entity entity, ComponentType componentType);

void AddEntity(World world, Entity entity);
void RemoveEntity(World world, Entity entity);
void EntityComponentsChanged(World world, Entity entity);

void EnableWorld(World world);
void DisableWorld(World world);
unsigned int IsWorldEnabled(World world);

#endif
