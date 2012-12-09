/**
 * component_manager.h
 *
 * Component manager
 */
#ifndef COMPONENT_MANAGER_HEADER_SEEN
#define COMPONENT_MANAGER_HEADER_SEEN

#include "component.h"
#include "entity.h"
#include "resource_manager.h"

#include <stdarg.h>
typedef struct componentManager* ComponentManager;

ComponentManager CreateComponentManager(void);
void FreeComponentManager(ComponentManager componentManager);

Component CreateComponent(ComponentType componentType, ...);
void FreeComponent(Component component);

void AddComponentToEntity(ComponentManager componentManager, Entity entity, Component component);
void RemoveComponentFromEntity(ComponentManager componentManager, Entity entity, Component component);

Component GetComponentForEntity(ComponentManager componentManager, Entity entity, ComponentType componentType);

#endif
