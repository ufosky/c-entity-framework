/**
 * tile_map.h
 */
#ifndef TILEMAP_HEADER_SEEN
#define TILEMAP_HEADER_SEEN

typedef struct tile* Tile;

typedef struct tileMap* TileMap;

TileMap CreateTileMap(void);
void FreeTileMap();

#endif
