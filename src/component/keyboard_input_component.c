#include <stdlib.h>

#include "component.h"

KeyboardInputComponent CreateKeyboardInputComponent(void) {
    KeyboardInputComponent component = malloc(sizeof(struct keyboardInputComponent));

    return component;
}

void FreeKeyboardInputComponent(KeyboardInputComponent positionComponent) {
    free(positionComponent);
}
