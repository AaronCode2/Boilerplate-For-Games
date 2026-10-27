#pragma once
#include <raylib.h>
#include "../utility/utils.hpp"
#include "../utility/assets.hpp"

class Renderer {

    public:

        Renderer();

        RenderTexture2D targetBuffer = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

        // Make sure you add the appriotate Unifrom data with the shader, if it needs one
        void setCurrentShader(const ShaderIndex newCurrentShader); 

        void beginTargetRender() const { BeginTextureMode(targetBuffer); };
        void endTargetRender() const { EndTextureMode(); };

        void drawTargetWithShader(Vector2 playerVel_arg = {0, 0});

    private:

        void applyShader();

        ShaderIndex currentShader;

        RenderTexture2D renderBuffers[NUM_OF_RENDER_BUFFERS];
};