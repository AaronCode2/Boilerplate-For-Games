#include "world.hpp"

World::World() {


}

void World::updateTiles(const Vector2 cameraMovement) {

    // Camera movement is opposite to player movement -> Fake Scrolling used since the 1900s

    if(cameraMovement != (Vector2) {0, 0}) {

        for(Tile &tile : tiles) {

            tile.move({cameraMovement.x, cameraMovement.y});
        }
    }

    for(Tile &tile : tiles) {

        tile.update();
    }    
}

void World::update(const Vector2 cameraMovement) {

    updateTiles(cameraMovement);

    if(cameraMovement != (Vector2) {0, 0})
        worldPos <<= cameraMovement * GetFrameTime();

#if DEBUG_ENABLED

    if(IsKeyPressed(KEY_T))
        enableTilePlacer = !enableTilePlacer;

    if(enableTilePlacer)
        dev_tilePlacer();

#endif
}

std::vector<Tile> &World::giveTiles() {

    return tiles;
}

void World::dev_tilePlacer() {

    if((GetMouseDelta() != (Vector2) {0, 0}) || worldPos != tempWorldVec) {

        tempWorldVec = worldPos;

        for(float x = 0; x < tileSize.x * WORLD_SIZE; x += tileSize.x) {
            for(float y = 0; y < tileSize.y * WORLD_SIZE; y += tileSize.y) {

                if(CheckCollisionPointRec(
                    GetMousePosition(), 
                    {x + worldPos.x, y + worldPos.y, tileSize.x, tileSize.y}
                )) {
                    tilePlacerRect = {x + worldPos.x, y + worldPos.y, tileSize.x, tileSize.y};
                    break;
                }
            }
        }
    }

    // Deleting and adding tiles - Tile Editor

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

        for(auto &tile : tiles) {

            if(CheckCollisionPointRec(GetMousePosition(), tile.getObject()) && pickedTile == tile.getType())
                return;
        }

        tiles.push_back(Tile({tilePlacerRect.x, tilePlacerRect.y}, pickedTile));
    } else if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {

        for(auto it = tiles.begin(); it < tiles.end(); it++) {

            if(CheckCollisionPointRec(GetMousePosition(), it->getObject())) {
                it = tiles.erase(it);
                return;
            }
        }
    }

    Utils::debugRect(tilePlacerRect);
}
