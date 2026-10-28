#include "renderer.hpp"

// Thirdparty lib for debugging purposes

#if ENABLE_RENDERDOC

pRENDERDOC_GetAPI RendererDebugger::RENDERDOC_GetAPI;
RENDERDOC_API_1_1_2* RendererDebugger::renderDocAPI = nullptr; 
void *RendererDebugger::renderDocDLL = nullptr;

void *RendererDebugger::loadRenderDoc() {

    void *renderDocDLL = (void *) LoadLibraryA("renderdoc.dll");

    if(renderDocDLL == nullptr)
        Utils::exitApp("RenderDoc DLL was not found!");

    // This some sloppy code, even I coudld't understand it.

    pRENDERDOC_GetAPI RENDERDOC_GetAPI = 
    (pRENDERDOC_GetAPI)GetProcAddress((HMODULE)renderDocDLL, "RENDERDOC_GetAPI");
    RENDERDOC_GetAPI(eRENDERDOC_API_Version_1_7_0, (void **)&renderDocAPI);

    if(renderDocAPI == nullptr)
        Utils::exitApp("RenderDoc API was injected and didn't init right");

    return renderDocDLL;
}

void RendererDebugger::unloadRenderDoc() {

    // renderDocAPI->Shutdown();
}

void RendererDebugger::beginRenderDocCapture() {

    if(renderDocAPI != nullptr)
        renderDocAPI->StartFrameCapture(nullptr, nullptr);
}

void RendererDebugger::endRenderDocCapture() {

    if(renderDocAPI != nullptr)
        renderDocAPI->EndFrameCapture(nullptr, nullptr);
}

bool RendererDebugger::isRenderDocFrameCapturing() {

    if(renderDocAPI != nullptr) return renderDocAPI->IsFrameCapturing();

    return false;
}

#endif

Renderer::Renderer() {

    initBuffers();
}

Renderer::~Renderer() {

#if ENABLE_RENDERDOC

    RendererDebugger::unloadRenderDoc();

#endif
}

void Renderer::setCurrentShader(const ShaderIndex newCurrentShader) {

    currentShader = newCurrentShader;
}

// The playerVel is optional, only use for shaders that need it.
void Renderer::applyShader(Vector2 playerVel_arg) {

    switch(currentShader) {

        case ShaderIndex::GREYSCALE:

            applyShaderDirectly = true;
            break;

        case ShaderIndex::FOG: {

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
            
            applyShaderDirectly = true;
            break;
        }

        case ShaderIndex::BLUR: {

            // X-axis bluring

            Vector2 axis = {1.0f, 0.0f};
            Shaders::uniforms[UniformIndex::BLUR_AXIS].data = &axis;

            SetShaderValueV(
                Shaders::shader[currentShader],
                Shaders::uniforms[UniformIndex::BLUR_AXIS].loc,
                Shaders::uniforms[UniformIndex::BLUR_AXIS].data,
                SHADER_UNIFORM_VEC2, 1
            );

            applyShaderToBuffer(0, 1);

            // Y-axis bluring

            axis = {0.0f, 1.0f};
            Shaders::uniforms[UniformIndex::BLUR_AXIS].data = &axis;

            SetShaderValueV(
                Shaders::shader[currentShader],
                Shaders::uniforms[UniformIndex::BLUR_AXIS].loc,
                Shaders::uniforms[UniformIndex::BLUR_AXIS].data,
                SHADER_UNIFORM_VEC2, 1
            );

            applyShaderToBuffer(0, 0);

            // Merge Y-axis and X-axis Textures Together

            blendBuffers(0, 1, NUM_OF_RENDER_BUFFERS - 1);
            break;
        }

        case ShaderIndex::BLOOM: {

            // Apply affects on second buffer
            copyBuffer(TARGET_BUFFER, 1);

            for(int i = 1; i < NUM_OF_RENDER_BUFFERS - 1; i++)
                downSampleBuffer(i, i + 1);

            //  i = 5,

            BeginBlendMode(BLEND_ADDITIVE);
            {
                for(int i = NUM_OF_RENDER_BUFFERS - 1; i > 1; i--)
                    upSampleBuffer(i, i - 1);
            }
            EndBlendMode();

            BeginBlendMode(BLEND_ADDITIVE);
            {
                upSampleBuffer(NUM_OF_RENDER_BUFFERS - 1, TARGET_BUFFER);
            }
            EndBlendMode();

            BeginTextureMode(renderBuffers[0]);
            {
                // ClearBackground(BLACK);
                BeginShaderMode(Shaders::shader[ShaderIndex::BLOOM]);
                {
                    DrawTextureRec(
                        renderBuffers[0].texture,
                        {
                            0, 0,
                            (float) renderBuffers[0].texture.width,
                            (float) -renderBuffers[0].texture.height
                        },
                        {0, 0},
                        WHITE
                    );
                }   
                EndShaderMode();
            }   
            EndTextureMode();

            break;
        }
    }
}

void Renderer::drawResult() {

    if(applyShaderDirectly) {

        applyShaderToTarget();
        applyShaderDirectly = false;
        return;
    }

    if(currentShader == ShaderIndex::BLOOM) {

        DrawTextureRec(
            renderBuffers[TARGET_BUFFER].texture,
            {
                0, 0, 
                (float) renderBuffers[TARGET_BUFFER].texture.width, 
                -(float) renderBuffers[TARGET_BUFFER].texture.height
            }, {0, 0}, 
            WHITE
        );
        return;
    }

    DrawTextureRec(
        renderBuffers[NUM_OF_RENDER_BUFFERS - 1].texture,
        {
            0, 0, 
            (float) renderBuffers[NUM_OF_RENDER_BUFFERS - 1].texture.width, 
            -(float) renderBuffers[NUM_OF_RENDER_BUFFERS - 1].texture.height
        }, {0, 0}, 
        WHITE
    );
}

void Renderer::applyShaderToBuffer(int inputBuffer, int ouputBuffer) {

    BeginTextureMode(renderBuffers[ouputBuffer]);
    {

        BeginShaderMode(Shaders::shader[currentShader]);
        {
            DrawTextureRec(
                renderBuffers[inputBuffer].texture,
                {
                    0, 0, 
                    (float) renderBuffers[inputBuffer].texture.width, 
                    -(float) renderBuffers[inputBuffer].texture.height
                }, {0, 0}, 
                WHITE
            );
        }
        EndShaderMode();
    }
    EndTextureMode();
}

void Renderer::applyShaderToTarget() {

    BeginShaderMode(Shaders::shader[currentShader]);
    {
        DrawTextureRec(
            renderBuffers[TARGET_BUFFER].texture,
            {
                0, 0, 
                (float) renderBuffers[TARGET_BUFFER].texture.width, 
                -(float) renderBuffers[TARGET_BUFFER].texture.height
            }, {0, 0}, 
            WHITE
        );
    }
    EndShaderMode();
}

RenderTexture2D Renderer::LoadHDRRender(Vector2 size) {

    RenderTexture2D tempBuffer = {0};

    // Generate new buffer

    tempBuffer.id = rlLoadFramebuffer();

    rlEnableFramebuffer(tempBuffer.id);

    // This like advanced encoding and decoding - I don't understand half of this stuff
    
    //! WARNING: WHEN ON FULLSCREEN, IF THE SOMETHING IS NOT RIGHT, YOU CAN CAUSE A BLUE SCREEN.

    tempBuffer.texture.id = rlLoadTexture(
        NULL, 
        (int) size.x, 
        (int) size.y,
        PIXELFORMAT_UNCOMPRESSED_R32G32B32A32,
        1
    );

    tempBuffer.texture.width = (int) size.x;
    tempBuffer.texture.height = (int) size.y;
    tempBuffer.texture.format = PIXELFORMAT_UNCOMPRESSED_R32G32B32A32;
    tempBuffer.texture.mipmaps = 1;

    tempBuffer.depth.id = rlLoadTextureDepth((int) size.x, (int) size.y, true);
    tempBuffer.depth.width = (int) size.x;
    tempBuffer.depth.height = (int) size.y;
    tempBuffer.depth.format = 19;
    tempBuffer.depth.mipmaps = 1;

    rlFramebufferAttach(
        tempBuffer.id,
        tempBuffer.texture.id,
        RL_ATTACHMENT_COLOR_CHANNEL0,
        RL_ATTACHMENT_TEXTURE2D,
        0
    );

    rlFramebufferAttach(
        tempBuffer.id,
        tempBuffer.depth.id,
        RL_ATTACHMENT_DEPTH,
        RL_ATTACHMENT_RENDERBUFFER,
        0
    );

    if(!rlFramebufferComplete(tempBuffer.id))
        Utils::exitApp("Could Not Create Custom Buffer (DEV'S FAULT)");

    rlDisableFramebuffer();

    SetTextureFilter(tempBuffer.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureWrap(tempBuffer.texture, TEXTURE_WRAP_CLAMP);

    return tempBuffer;
}

void Renderer::blendBuffers(int inputBuffer1, int inputBuffer2, int ouputBuffer) {

    BeginTextureMode(renderBuffers[ouputBuffer]);
    {

        // The texture.height it negative since OpenGL flips y-axis. LOL

        DrawTextureRec(
            renderBuffers[inputBuffer1].texture,
            {
                0, 0, 
                (float) renderBuffers[inputBuffer1].texture.width, 
                -(float) renderBuffers[inputBuffer1].texture.height
            }, {0, 0}, 
            WHITE
        );

        DrawTextureRec(
            renderBuffers[inputBuffer2].texture,
            {
                0, 0, 
                (float) renderBuffers[inputBuffer2].texture.width, 
                -(float) renderBuffers[inputBuffer2].texture.height
            }, {0, 0}, 
            WHITE
        );

        EndBlendMode();
    }
    EndTextureMode();
}

void Renderer::initBuffers() {

    // Some Vendors can struggle with this many buffers. Use lower when in OpenGL-ES
    renderBuffers[TARGET_BUFFER] = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    Vector2 bufferSize = Utils::getScreenSizeV() / 2.0f;

    for(int i = 1; i < NUM_OF_RENDER_BUFFERS - 1; i++) {

        renderBuffers[i] = LoadRenderTexture(bufferSize.x, bufferSize.y);

        bufferSize /= 2.0f;
    }

    renderBuffers[NUM_OF_RENDER_BUFFERS - 1] = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
}

void Renderer::copyBuffer(int inputBuffer, int ouputBuffer) {

    BeginTextureMode(renderBuffers[ouputBuffer]);
    {
        DrawTextureRec(
            renderBuffers[inputBuffer].texture,
            {
                0, 0, 
                (float) renderBuffers[ouputBuffer].texture.width, 
                -(float) renderBuffers[ouputBuffer].texture.height
            }, {0, 0}, 
            WHITE
        );
    }
    EndTextureMode();
}

void Renderer::copyBufferWithDifferentSizes(int inputBuffer, int ouputBuffer) {

    BeginTextureMode(renderBuffers[ouputBuffer]);
    {
        DrawTexturePro(
            renderBuffers[inputBuffer].texture,
            {
                0, 0,
                (float) renderBuffers[inputBuffer].texture.width,
                (float) renderBuffers[inputBuffer].texture.height,
            },
            {
                0, 0, 
                (float) renderBuffers[ouputBuffer].texture.width, 
                -(float) renderBuffers[ouputBuffer].texture.height
            }, 
            {0, 0}, 0.0f,
            WHITE
        );
    }
    EndTextureMode();
}

void Renderer::downSampleBuffer(int inputBuffer, int ouputBuffer) {

    return;

    Vector2 bufferSize = {
        (float)  renderBuffers[ouputBuffer].texture.width,
        (float) renderBuffers[ouputBuffer].texture.height
    };

    Shaders::uniforms[UniformIndex::DOWN_SAMPLE_TEXTURE_SIZE].data = &bufferSize;

    SetShaderValueV(
        Shaders::shader[ShaderIndex::DOWN_SAMPLING],
        Shaders::uniforms[UniformIndex::DOWN_SAMPLE_TEXTURE_SIZE].loc,
        Shaders::uniforms[UniformIndex::DOWN_SAMPLE_TEXTURE_SIZE].data,
        SHADER_UNIFORM_VEC2, 1
    );

    BeginTextureMode(renderBuffers[ouputBuffer]);
    {
        ClearBackground(BLACK);
        BeginShaderMode(Shaders::shader[ShaderIndex::DOWN_SAMPLING]);
        {
            DrawTexturePro(
                renderBuffers[inputBuffer].texture,
                {
                    0, 0,
                    (float) renderBuffers[inputBuffer].texture.width,
                    -(float) renderBuffers[inputBuffer].texture.height,
                },
                {
                    0, 0,
                    (float) renderBuffers[ouputBuffer].texture.width,
                    (float) renderBuffers[ouputBuffer].texture.height,
                }, {0, 0}, 0.0f,
                WHITE
            );
        }
        EndShaderMode();
    }   
    EndTextureMode();
}

void Renderer::upSampleBuffer(int inputBuffer, int ouputBuffer) {

    Vector2 bufferSize = {
        (float) renderBuffers[ouputBuffer].texture.width,
        (float) renderBuffers[ouputBuffer].texture.height
    };

    Shaders::uniforms[UniformIndex::UP_SAMPLE_TEXTURE_SIZE].data = &bufferSize;

    SetShaderValueV(
        Shaders::shader[ShaderIndex::UP_SAMPLING],
        Shaders::uniforms[UniformIndex::UP_SAMPLE_TEXTURE_SIZE].loc,
        Shaders::uniforms[UniformIndex::UP_SAMPLE_TEXTURE_SIZE].data,
        SHADER_UNIFORM_VEC2, 1
    );

    BeginTextureMode(renderBuffers[ouputBuffer]);
    {
        BeginShaderMode(Shaders::shader[ShaderIndex::UP_SAMPLING]);
        {
            DrawTexturePro(
                renderBuffers[inputBuffer].texture,
                {
                    0, 0,
                    (float) renderBuffers[inputBuffer].texture.width,
                    -(float) renderBuffers[inputBuffer].texture.height,
                },
                {
                    0, 0,
                    (float) renderBuffers[ouputBuffer].texture.width,
                    (float) renderBuffers[ouputBuffer].texture.height,
                }, {0, 0}, 0.0f,
                WHITE
            );
        }
        EndShaderMode();
    }   
    EndTextureMode();
}
