#include "textures.hpp"

std::map<ImageIndex, TextureData> Textures::texture;

void Textures::loadTextures() {

    texture[ImageIndex::PLAYER] = {

        LoadTexture(IMAGE_PLAYER_PATH),
        IMAGE_PLAYER_MAX_FRAMES
    };

    texture[ImageIndex::TILE] = {

        LoadTexture(IMAGE_TILE_PATH),
        IMAGE_TILE_MAX_FRAMES
    };

    texture[ImageIndex::GUI_PLATE] = {

        LoadTexture(IMAGE_GUI_PLATE_PATH),
        IMAGE_GUI_PLATE_MAX_FRAMES
    };
}
