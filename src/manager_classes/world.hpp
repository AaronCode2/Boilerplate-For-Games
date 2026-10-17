#pragma once
#include <raylib.h>
#include <vector>
#include "../entity_classes/tile.hpp"
#include <math.h>

// Bored, Bored, Boredom.

class World {

    public:

        World();

        void update(const Vector2 cameraMovement);

        std::vector<Tile> &giveTiles();

        Vector2 &getWorldPos_r() { return worldPos; };
        Vector2 getWorldPos() { return worldPos; };

        void setpickedTile(TileType newPickedTile) { pickedTile = newPickedTile; };

    private:

        void dev_tilePlacer();

        void updateTiles(const Vector2 cameraMovement);

        std::vector<Tile> tiles;

        const Vector2 tileSize = {
            Textures::texture[ImageIndex::TILE].GetFrameSize().x,
            Textures::texture[ImageIndex::TILE].GetFrameSize().y
        };

        Rectangle tilePlacerRect;
        TileType pickedTile = TileType::COUCH;
        
        bool enableTilePlacer = false;

        Vector2 worldPos = {0, 0};
        Vector2 tempWorldVec = {0, 0};
};