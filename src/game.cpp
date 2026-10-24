#include "game.hpp"

Game::Game() {

    SetExitKey(KEY_NULL);

    data.readData(DataMapIndex::DEV_MAP);
}
 
// I should be revising than doing coding. LOL

Game::~Game() {

    // data.writeData(DataMapIndex::DEV_MAP);
}

void Game::updateNK() {

    // See the raylib-nk docs, it will help: https://github.com/Immediate-Mode-UI/Nuklear/wiki/Window 

    UpdateNuklear(nk);

        if(
            nk_begin(nk, "THIS", nk_rect(100, 100, 420, 720),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE)
        ) {

            nk_layout_row_static(nk, 50, 150, 1);

            nk_label(nk, "RECT", NK_TEXT_LEFT);
            Utils::THE_DEBUG_RECT.x = nk_slide_float(nk, -400, Utils::THE_DEBUG_RECT.x, 400.0f, 1.0f);
            Utils::THE_DEBUG_RECT.y = nk_slide_float(nk, -400, Utils::THE_DEBUG_RECT.y, 400.0f, 1.0f);
            Utils::THE_DEBUG_RECT.width = nk_slide_float(nk, -400, Utils::THE_DEBUG_RECT.width, 400.0f, 1.0f);
            Utils::THE_DEBUG_RECT.height = nk_slide_float(nk, 0, Utils::THE_DEBUG_RECT.height, 400.0f, 1.0f);
            

            nk_label(nk, "VECTOR", NK_TEXT_LEFT);
            Utils::THE_DEBUG_VECTOR.x = nk_slide_float(nk, -400, Utils::THE_DEBUG_VECTOR.x, 400.0f, 1.0f);
            Utils::THE_DEBUG_VECTOR.y = nk_slide_float(nk, -400, Utils::THE_DEBUG_VECTOR.y, 400.0f, 1.0f);

            const char *tileItems[] = {"WALL", "CLOCK", "COUCH", "STAND"};

            nk_combobox(nk, tileItems, 4, &Utils::selectedtileTypeIndex, 20, {100, 100});

            // Hacker mode, enables for player to go flying

            nk_checkbox_label(nk, "Hacker Mode", &Utils::hackerMode);

            world.setpickedTile((TileType) Utils::selectedtileTypeIndex);
        }
    nk_end(nk);
}

void Game::drawNK() {

    DrawNuklear(nk);
}

void Game::gameLoop() {

    SetTargetFPS(60);

    int locAxis = GetShaderLocation(Shaders::shader[ShaderIndex::BLUR], "axis");

    Vector2 axis = {1.0f, 0.0f};

    while(!WindowShouldClose()) {

#if DEBUG_ENABLED
        updateNK();
#endif

        // Stuff you want in the shader

        BeginTextureMode(screenBuffer);
        {

            DrawRectangleRec({800, 600, 100, 100}, RED);
            DrawRectangleRec({600, 800, 100, 100}, YELLOW);
        }
        EndTextureMode();
        
        // Horizotal Bluring

        axis = HORIZONTAL_VEC;

        SetShaderValueV(
            Shaders::shader[ShaderIndex::BLUR],
            locAxis,
            &axis, SHADER_UNIFORM_VEC2,
            1
        );

        BeginTextureMode(processedBuffer);
        {

            ClearBackground(BLANK);

            BeginShaderMode(Shaders::shader[ShaderIndex::BLUR]);
            {
                

                // You could do some upscaling with this

                DrawTexturePro(
                    screenBuffer.texture,
                    {
                        0, 0, 
                        (float) screenBuffer.texture.width, 
                        -(float) screenBuffer.texture.height,
                    },
                    Utils::getScreenRect(), {0, 0}, 0.0f,
                    WHITE
                );
            }
            EndShaderMode();
        }
        EndTextureMode();

        // Vertical Bluring
        
        axis = VERTICAL_VEC;

        SetShaderValueV(
            Shaders::shader[ShaderIndex::BLUR],
            locAxis,
            &axis, SHADER_UNIFORM_VEC2,
            1
        );

        BeginDrawing();
        {

            ClearBackground(backgroundColor);

            BeginShaderMode(Shaders::shader[ShaderIndex::BLUR]);
            {
                DrawTexturePro(
                    processedBuffer.texture,
                    {
                        0, 0, 
                        (float) processedBuffer.texture.width, 
                        -(float) processedBuffer.texture.height,
                    },
                    Utils::getScreenRect(), {0, 0}, 0.0f,
                    WHITE
                );

            }
            EndShaderMode();

            // Stuff you don't want in Shader

            updateGame();

#if DEBUG_ENABLED
    drawNK();
#endif
        }   
        EndDrawing();
    }

    UnloadNuklear(nk);

    CloseWindow();
}

void Game::updateGame() {

    handleFps();

    world.update(player.getCameraMovement());
    player.update();

    UI::drawBases({Utils::THE_DEBUG_RECT.x, Utils::THE_DEBUG_RECT.y}, {6, 3});

    button.update(Utils::THE_DEBUG_VECTOR);

    button.active = button.getState(UI::Button_State::MOUSE_HOVER);
}

void Game::handleFps() {

    if(IsKeyPressed(KEY_P)) {
        
        GlobalVar::toggleMaxFPS = !GlobalVar::toggleMaxFPS;

        if(GlobalVar::toggleMaxFPS)
            SetTargetFPS(0);
        else
            SetTargetFPS(60);
    }

    if(!IsWindowFocused() && !GlobalVar::isWindowInactive) {

        SetTargetFPS(30);
        GlobalVar::isWindowInactive = true;

    } else if(IsWindowFocused() && GlobalVar::isWindowInactive) {

        SetTargetFPS(60);
        GlobalVar::isWindowInactive = false;
    }

    DrawFPS(GetScreenHeight() - 40.0f, 40);
}