#pragma once
#include <raylib.h>
#include <map>
#include "utils.hpp"

enum class ImageIndex {

    PLAYER = 0,
    TILE,
    GUI_PLATE
};

struct TextureData {
    
    Texture2D texture;
    Vector2 amountOfFrames;

    Vector2 GetFrameSize() {

       return {texture.width / amountOfFrames.x, texture.height / amountOfFrames.y};
    }
};

namespace Textures {
    
    extern std::map<ImageIndex, TextureData> texture;

    void loadTextures();
}
