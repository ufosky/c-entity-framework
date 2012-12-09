#include <stdlib.h>

#include "component.h"

PositionComponent CreatePositionComponent(unsigned int x, unsigned int y) {
    PositionComponent positionComponent = malloc(sizeof(struct positionComponent));
    positionComponent->x = x;
    positionComponent->y = y;

    return positionComponent;
}

void FreePositionComponent(PositionComponent positionComponent) {
    free(positionComponent);
}
