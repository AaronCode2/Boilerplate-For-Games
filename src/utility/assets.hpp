#pragma once
#include <raylib.h>
#include <map>
#include <math.h>
#include "utils.hpp"

enum class ImageIndex {

    PLAYER = 0,
    TILE,
    GUI_PLATE
};

// storing both vs and fs together

enum class ShaderIndex {

    GREYSCALE = 0,
    FOG,
    BLUR,
    BLOOM,
    DOWN_SAMPLING,
    UP_SAMPLING
};

enum class UniformIndex {

    DOWN_SAMPLE_TEXTURE_SIZE = 0,
    UP_SAMPLE_TEXTURE_SIZE
};

struct Uniform {

    int loc;
    void *data;
};

struct TextureData {
    
    Texture2D texture;
    Vector2 amountOfFrames;

    Vector2 GetFrameSize() {

       return {texture.width / amountOfFrames.x, texture.height / amountOfFrames.y};
    }
};

namespace AssetsLoader {

    void load();
}

namespace Textures {
    
    extern std::map<ImageIndex, TextureData> texture;

    void loadTextures();

    Texture2D getScaledTexture(std::string path, int scale);
}

namespace Shaders {

    extern std::map<ShaderIndex, Shader> shader;
    extern std::map<UniformIndex, Uniform> uniforms;

    // Using fast calling reg

    void __stdcall  compileShaders();

    void _getUniforms();
}