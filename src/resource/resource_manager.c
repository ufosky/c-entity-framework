#include "resource_manager.h"

#include <stdlib.h>
#include <assert.h>

typedef struct resourceManager {
    ResourceHandle* resources; //Should be a hash map.
    unsigned int numberOfResources;
} internalResourceManager;

ResourceHandle CreateResourceHandle(ResourceType resourceType) {
    ResourceHandle rh = malloc(sizeof(struct resourceHandle));
    rh->resourceType = resourceType;

    switch (resourceType) {
    case BMP:
        rh->bitmap = malloc(sizeof(struct bitmapResource));
        break;
    default:
        assert(0);
    }

    return rh;
}

void FreeResourceHandle(ResourceManager resourceManager, ResourceHandle resourceHandle) {
    //TODO: remove self from resource manager;
    switch (resourceHandle->resourceType) {
    case BMP:
        SDL_free(resourceHandle->bitmap->surface);
        free(resourceHandle->bitmap);
        break;
    default:
        assert(0);
    }

    free(resourceHandle);
}

ResourceManager CreateResourceManager(void) {
    ResourceManager obj = malloc(sizeof(internalResourceManager));
    obj->resources = malloc(sizeof(struct resourceHandle));
    obj->numberOfResources = 0;

    //Temporary until hash
    obj->resources[0] = NULL;

    return obj;
}

void FreeResourceManager(ResourceManager resourceManager) {
    for (unsigned int i = 0; i < resourceManager->numberOfResources; ++i) {
        //Temporary
        if (NULL != resourceManager->resources[i]) {
            FreeResourceHandle(resourceManager, resourceManager->resources[i]);
        }
    }
    free(resourceManager);
}

void AddResource(ResourceManager resourceManager, char* identifier, ResourceType resourceType) {
    //Hard code for now;
    SDL_Surface* tempSurface = NULL;
    SDL_Surface* bitmapSurface = NULL;

    if((tempSurface = SDL_LoadBMP(identifier)) == NULL) {
        fprintf(stderr, "Unable to load resource: %s\n", SDL_GetError());
        exit(1);
    }

    bitmapSurface = SDL_DisplayFormat(tempSurface);
    SDL_FreeSurface(tempSurface);

    ResourceHandle resourceHandle = CreateResourceHandle(resourceType);
    resourceHandle->bitmap->name = identifier;
    resourceHandle->bitmap->surface = bitmapSurface;

    resourceManager->resources[resourceManager->numberOfResources++] = resourceHandle;
}

ResourceHandle GetResource(ResourceManager resourceManager, char* identifier, ResourceType resourceType) {
    //Hard code for now.
    return resourceManager->resources[0];
}
