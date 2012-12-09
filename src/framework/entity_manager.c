#include <stdlib.h>
#include <assert.h>

#include "entity_manager.h"

typedef struct entityManager {
    Entity* entities;
    unsigned int* reclaimedIds;
    unsigned int entityCount;
    unsigned int reclaimedIdCount;
} internalEntityManager;

typedef struct entity internalEntity;

unsigned int GetNextAvailableEntityId(EntityManager entityManager) {
    unsigned int reclaimedId = 0;

    if (entityManager->reclaimedIdCount > 0) {
        reclaimedId = entityManager->reclaimedIds[entityManager->reclaimedIdCount];
        entityManager->reclaimedIds[entityManager->reclaimedIdCount--] = 0;
    } else {
        reclaimedId = entityManager->entityCount++;
        assert(reclaimedId < MAX_ENTITY_NUM);
    }

    return reclaimedId;
}

EntityManager CreateEntityManager(void) {
    EntityManager obj = malloc(sizeof(internalEntityManager));
    obj->entities = malloc(MAX_ENTITY_NUM * sizeof(Entity));
    obj->reclaimedIds = malloc(MAX_ENTITY_NUM * sizeof(unsigned int));
    obj->entityCount = 0;
    obj->reclaimedIdCount = 0;

    return obj;
}

void FreeEntityManager(EntityManager entityManager) {
    for(unsigned int i = 0; i < entityManager->entityCount; ++i) {
        FreeEntity(entityManager, entityManager->entities[i]);
    }

    free(entityManager);
}

Entity CreateEntity(EntityManager entityManager) {
    Entity newEntity = malloc(sizeof(internalEntity));
    newEntity->componentDescriptor = CreateBitSet(NUM_COMPONENT_TYPES);
    newEntity->id = GetNextAvailableEntityId(entityManager);

    entityManager->entities[newEntity->id] = newEntity;
    entityManager->entityCount++;

    return newEntity;
}

void FreeEntity(EntityManager entityManager, Entity entity) {
    //Remove entity from all intrusive lists
    Remove(&(entity->renderSystemListNode));
    Remove(&(entity->keyboardInputSystemListNode));

    //Remove the entity from the entity managers registry
    entityManager->entities[entity->id] = NULL;
    entityManager->entityCount--;

    //Add the entities ID back to the entity managers pool
    entityManager->reclaimedIds[entityManager->reclaimedIdCount++] = entity->id;

    //Free memory used by the entity
    FreeBitSet(entity->componentDescriptor);
    free(entity);
}
