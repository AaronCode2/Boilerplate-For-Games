#include "renderer.hpp"

Renderer::Renderer() {

}

void Renderer::setCurrentShader(const ShaderIndex newCurrentShader) {

    currentShader = newCurrentShader;
}

// The playerVel is optional, only use for shaders that need it.
void Renderer::drawTargetWithShader(Vector2 playerVel_arg) {

    switch(currentShader) {

        case ShaderIndex::GREYSCALE:

            applyShader();

        case ShaderIndex::FOG:

            Shaders::uniforms[UniformIndex::FOG_POS].data = &playerVel_arg;

            SetShaderValueV(
                Shaders::shader[ShaderIndex::FOG],
                Shaders::uniforms[UniformIndex::FOG_POS].loc,
                Shaders::uniforms[UniformIndex::FOG_POS].data,
                SHADER_UNIFORM_VEC2, 1
            );
            
            Vector2 size = Utils::getScreenSizeV();
            Shaders::uniforms[UniformIndex::FOG_WINDOW_SIZE].data = &size;

            SetShaderValueV(
                Shaders::shader[currentShader],
                Shaders::uniforms[UniformIndex::FOG_WINDOW_SIZE].loc,
                Shaders::uniforms[UniformIndex::FOG_WINDOW_SIZE].data,
                SHADER_UNIFORM_VEC2, 1
            );
            
            float time = GetTime();
            Shaders::uniforms[UniformIndex::FOG_TIME].data = &time;

            SetShaderValue(
                Shaders::shader[currentShader],
                Shaders::uniforms[UniformIndex::FOG_TIME].loc,
                Shaders::uniforms[UniformIndex::FOG_TIME].data,
                SHADER_UNIFORM_FLOAT
            );

            applyShader();
    }
}

void Renderer::applyShader() {

    BeginShaderMode(Shaders::shader[currentShader]);
    {
        DrawTextureRec(
            targetBuffer.texture,
            {
                0, 0, 
                (float) targetBuffer.texture.width, 
                -(float) targetBuffer.texture.height
            }, {0, 0}, 
            WHITE
        );
    }
    EndShaderMode();
}
