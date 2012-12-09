/**
 * entity_manager.h
 */
#ifndef ENTITY_MANAGER_HEADER_SEEN
#define ENTITY_MANAGER_HEADER_SEEN

#include "entity.h"
#include "component.h"

typedef struct entityManager* EntityManager;

EntityManager CreateEntityManager(void);
void FreeEntityManager(EntityManager entityManager);

Entity CreateEntity(EntityManager entityManager);
void FreeEntity(EntityManager entityManager, Entity entity);

Component GetComponent(ComponentType type);

#endif
