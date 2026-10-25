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

std::map<ShaderIndex, Shader> Shaders::shader;
std::map<UniformIndex, Uniform> Shaders::uniforms;

void __stdcall Shaders::compileShaders() {

    // There is no Vertex shader, we use default raylib vertex, please don't make your own

    shader[ShaderIndex::GREYSCALE] = LoadShader(RAYLIB_SHADER, GREYSCALE_FRAG_PATH);
    shader[ShaderIndex::FOG] = LoadShader(RAYLIB_SHADER, FOG_FRAG_PATH);
    shader[ShaderIndex::BLUR] = LoadShader(RAYLIB_SHADER, BLUR_FRAG_PATH);
    shader[ShaderIndex::BLOOM] = LoadShader(RAYLIB_SHADER, BLOOM_FRAG_PATH);

    shader[ShaderIndex::DOWN_SAMPLING] = LoadShader(RAYLIB_SHADER, DOWN_SAMPLING_FRAG_PATH);
    shader[ShaderIndex::UP_SAMPLING] = LoadShader(RAYLIB_SHADER, UP_SAMPLING_FRAG_PATH);

    _getUniforms();
}

void Shaders::_getUniforms() {

    uniforms[UniformIndex::DOWN_SAMPLE_TEXTURE_SIZE].loc = GetShaderLocation(shader[ShaderIndex::DOWN_SAMPLING], "textureSize");
    uniforms[UniformIndex::UP_SAMPLE_TEXTURE_SIZE].loc = GetShaderLocation(shader[ShaderIndex::UP_SAMPLING], "textureSize");
}

void AssetsLoader::load() {

    Textures::loadTextures();
    Shaders::compileShaders();
}
