#include <stdlib.h>
#include <assert.h>

#include "component_manager.h"
#include "component.h"

typedef struct componentManager {
    Component** componetsByType;
} internalComponentManager;

ComponentManager CreateComponentManager(void) {
    ComponentManager obj = malloc(sizeof(internalComponentManager));
    obj->componetsByType = malloc(NUM_COMPONENT_TYPES * sizeof(Component));

    for (unsigned int i = 0; i < NUM_COMPONENT_TYPES; ++i) {
        obj->componetsByType[i] = malloc(MAX_ENTITY_NUM * sizeof(Component));
    }

    return obj;
}

void FreeComponentManager(ComponentManager componentManager) {
    for (unsigned int i = 0; i < NUM_COMPONENT_TYPES; ++i) {
        free(componentManager->componetsByType[i]);
    }

    free(componentManager->componetsByType);
    free(componentManager);
}

Component CreateComponent(ComponentType componentType, ...) {
    Component newComponent = malloc(sizeof(struct component));
    newComponent->componentType = componentType;

    va_list initValues;

    va_start(initValues, componentType);

    //Position component init values
    unsigned int x, y = 0;

    //Sprite component init values
    ResourceManager resourceManager = NULL;
    char* spriteName = NULL;

    switch (componentType) {
    case POSITION:
        x = va_arg(initValues, unsigned int);
        y = va_arg(initValues, unsigned int);
        newComponent->positionComponent = CreatePositionComponent(0, 0);
        break;
    case SPRITE:
        resourceManager = va_arg(initValues, ResourceManager);
        spriteName = va_arg(initValues, char *);
        newComponent->spriteComponent = CreateSpriteComponent(resourceManager, spriteName);
        break;
    case KEYBOARD_INPUT:
        newComponent->keyboardInputComponent = CreateKeyboardInputComponent();
        break;
    default:
        assert(0);
    }

    va_end(initValues);

    return newComponent;
}

void FreeComponent(Component component) {
    switch (component->componentType) {
    case POSITION:
        FreePositionComponent(component->positionComponent);
        break;
    case SPRITE:
        FreeSpriteComponent(component->spriteComponent);
        break;
    case KEYBOARD_INPUT:
        FreeKeyboardInputComponent(component->keyboardInputComponent);
        break;
    default:
        assert(0);
    }

    free(component);
}

void AddComponentToEntity(ComponentManager componentManager, Entity entity, Component component) {
    componentManager->componetsByType[component->componentType][entity->id] = component;
    SetBit(entity->componentDescriptor, component->componentType);
}

void RemoveComponentFromEntity(ComponentManager componentManager, Entity entity, Component component) {
    componentManager->componetsByType[component->componentType][entity->id] = NULL;
    ClearBit(entity->componentDescriptor, component->componentType);
}

Component GetComponentForEntity(ComponentManager componentManager, Entity entity, ComponentType componentType) {
    return componentManager->componetsByType[componentType][entity->id];
}
