/**
 * component.h
 *
 * Component management
 */

#ifndef COMPONENT_HEADER_SEEN
#define COMPONENT_HEADER_SEEN

#include "resource_manager.h"

typedef enum {
    POSITION,
    SPRITE,
    KEYBOARD_INPUT,
    NUM_COMPONENT_TYPES
} ComponentType;

typedef struct positionComponent* PositionComponent;
struct positionComponent {
    unsigned int x;
    unsigned int y;
};

typedef struct spriteComponent* SpriteComponent;
struct spriteComponent {
    char* spriteName;
    ResourceHandle image;
};

typedef struct keyboardInputComponent* KeyboardInputComponent;
struct keyboardInputComponent {

};

typedef struct component* Component;
struct component {
    ComponentType componentType;

    union {
        PositionComponent positionComponent;
        SpriteComponent spriteComponent;
        KeyboardInputComponent keyboardInputComponent;
    };
};


SpriteComponent CreateSpriteComponent(ResourceManager resourceManager, char* spriteName);
void FreeSpriteComponent(SpriteComponent spriteComponent);

PositionComponent CreatePositionComponent(unsigned int x, unsigned int y);
void FreePositionComponent(PositionComponent positionComponent);

KeyboardInputComponent CreateKeyboardInputComponent(void);
void FreeKeyboardInputComponent(KeyboardInputComponent positionComponent);

#endif
