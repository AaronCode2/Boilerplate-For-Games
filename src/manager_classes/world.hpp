#pragma once
#include <raylib.h>
#include <vector>
#include "../entity_classes/tile.hpp"
#include <math.h>

class World {

    public:

        World();

        void update(const Vector2 cameraMovement);

        std::vector<Tile> &giveTiles();

    private:

        void dev_tilePlacer();

        void updateTiles(const Vector2 cameraMovement);

        std::vector<Tile> tiles;

        const Vector2 tileSize = {
            Textures::texture[ImageIndex::TILE].GetFrameSize().x,
            Textures::texture[ImageIndex::TILE].GetFrameSize().y
        };

        Rectangle tilePlacerRect;
        TileType pickedTile = TileType::WALL;
        
        bool enableTilePlacer = false;

        Vector2 worldPos = {0, 0};
        Vector2 tempWorldVec = {0, 0};
};