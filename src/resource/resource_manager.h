/**
 * resource_manager.h
 */
#ifndef RESOURCEMANAGER_HEADER_SEEN
#define RESOURCEMANAGER_HEADER_SEEN

#include "SDL/SDL.h"

typedef enum {
    BMP,
    NUM_RESOURCE_TYPES
} ResourceType;

typedef struct resourceManager* ResourceManager;

typedef struct bitmapResource* BitmapResource;

struct bitmapResource {
    char* name;
    SDL_Surface* surface;
};

typedef struct resourceHandle* ResourceHandle;

struct resourceHandle {
    ResourceType resourceType;

    union {
        BitmapResource bitmap;
    };
};

ResourceManager CreateResourceManager(void);
void FreeResourceManager(ResourceManager resourceManager);

void AddResource(ResourceManager resourceManager, char* identifier, ResourceType resourceType);
ResourceHandle GetResource(ResourceManager resourceManager, char* identifier, ResourceType resourceType);

#endif
