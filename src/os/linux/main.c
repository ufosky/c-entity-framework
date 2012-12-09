#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"

#include "entity_manager.h"
#include "component_manager.h"
#include "entity.h"
#include "component.h"
#include "world.h"
#include "resource_manager.h"

int main(int argc, char *argv[]) {

    if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0 ) {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Surface* screen;

    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( screen == NULL ) {
        fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
        exit(1);
    }

    ResourceManager resourceManager= CreateResourceManager();
    AddResource(resourceManager, "assets/character/player.bmp", BMP);

    World world = CreateWorld();

    EntityManager entityManager = CreateEntityManager();
    LinkEntityManagerToWorld(world, entityManager);

    ComponentManager componentManager = CreateComponentManager();
    LinkComponentManagerToWorld(world, componentManager);

    Component positionComponent = CreateComponent(POSITION, 0, 0);
    Component spriteComponent = CreateComponent(SPRITE, resourceManager, "assets/character/player.bmp");
    Component keyboardInputComponent = CreateComponent(KEYBOARD_INPUT);

    Entity entity = CreateEntity(entityManager);

    AddComponentToEntity(componentManager, entity, positionComponent);
    AddComponentToEntity(componentManager, entity, spriteComponent);
    AddComponentToEntity(componentManager, entity, keyboardInputComponent);

    AddEntity(world, entity);
    EnableWorld(world);

    while (IsWorldEnabled(world)) {
        //Render
        SDL_FillRect(screen,NULL, SDL_MapRGB(screen->format, 100, 100, 100));

        //Pump messages
        SDL_PumpEvents();

        Process(world);

        SDL_Flip(screen);
    }

    RemoveComponentFromEntity(componentManager, entity, positionComponent);
    RemoveComponentFromEntity(componentManager, entity, spriteComponent);

    FreeComponent(positionComponent);
    FreeComponent(spriteComponent);
    FreeComponent(keyboardInputComponent);

    FreeComponentManager(componentManager);
    FreeEntityManager(entityManager);
    FreeWorld(world);

    FreeResourceManager(resourceManager);

    SDL_FreeSurface(screen);

    SDL_Quit();
}
