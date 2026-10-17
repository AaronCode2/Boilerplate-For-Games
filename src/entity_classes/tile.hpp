#pragma once
#include <raylib.h>
#include "sprite.hpp"
#include "../utility/assets.hpp"
#include "../utility/utils.hpp"

class Tile : public Sprite {

    public:

        Tile(Vector2 position, TileType type);

        void update();
        void move(const Vector2 newVelocity);

        Rectangle getHitBox() const { return hitBox; };

        TileType getType() const { return type; };

    private:

        void draw();
        void updateHitBox();

        TileType type;
        Rectangle hitBox;
};