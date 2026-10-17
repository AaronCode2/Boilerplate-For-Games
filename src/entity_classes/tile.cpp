#include "tile.hpp"

Tile::Tile(Vector2 position, TileType type): 
    Sprite({
        position.x, position.y, 
        (float) Textures::texture[ImageIndex::TILE].GetFrameSize().x, 
        (float) Textures::texture[ImageIndex::TILE].GetFrameSize().y
    }, ImageIndex::TILE)
{

    this->type = type;

    srcRect.x = Textures::texture[ImageIndex::TILE].GetFrameSize().x * (int) type;
}

void Tile::update() {

    draw();
    updateHitBox();
}

void Tile::move(const Vector2 newVelocity) {

    velocity = newVelocity;

    object <<= velocity * GetFrameTime();

    velocity = {0, 0};
}

void Tile::draw() {

    DrawTextureRec(
        Textures::texture[ImageIndex::TILE].texture,
        srcRect, {std::floorf(object.x), std::floorf(object.y)},
        WHITE
    );
}

void Tile::updateHitBox() {

    if(type == TileType::WALL) {

        hitBox = {
            object.x + TILE_WALL_HITBOX_ADJ.x,
            object.y + TILE_WALL_HITBOX_ADJ.y,
            object.width + TILE_WALL_HITBOX_ADJ.width,
            object.height + TILE_WALL_HITBOX_ADJ.height,
        };
    }

    // Utils::debugRect(hitBox);
}
