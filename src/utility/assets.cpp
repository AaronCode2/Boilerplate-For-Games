#include "assets.hpp"

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

        getScaledTexture(IMAGE_GUI_PLATE_PATH, GUI_SCALE),
        IMAGE_GUI_PLATE_MAX_FRAMES
    };
}

Texture2D Textures::getScaledTexture(std::string path, int scale) {

    // Using CPU up-scaling

    Image image = LoadImage(path.c_str());

    ImageResize(&image, std::floorf(image.width) * scale, std::floorf(image.height) * scale);

    Texture2D texture = LoadTextureFromImage(image);

    UnloadImage(image);

    return texture;
}
