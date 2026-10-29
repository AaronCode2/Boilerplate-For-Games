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

            nk_label(nk, "Shaders", NK_TEXT_LEFT);
            Utils::shaderIndex = nk_slide_int(nk, 0, Utils::shaderIndex, sizeof(ShaderIndex), 1);

            // Hacker mode, enables for player to go flying

            nk_checkbox_label(nk, "Hacker Mode", &Utils::hackerMode);

            world.setpickedTile((TileType) Utils::selectedtileTypeIndex);
        }
    nk_end(nk);
}

void Game::drawNK() {

#if DEBUG_ENABLED
    DrawNuklear(nk);
#endif
}

void Game::handleDrawing() {

// This is should be commented out, don't ask why. It the just works: idkh?
#if ENABLE_RENDERDOC

    // if(RendererDebugger::isRenderDocFrameCapturing())
    //     RendererDebugger::beginRenderDocCapture();

#endif

    BeginDrawing();
    {
        ClearBackground(BLACK);

        updateGame();

        BeginBlendMode(BLEND_ADDITIVE);
        {
            
            DrawTextureV(classicImage, {1800, 100}, WHITE);
            renderer.drawResult();
        }
        EndBlendMode();

        renderer.beginTargetRender();
        {
            ClearBackground(BLACK);
            
            DrawTextureV(classicImage, {800, 800}, WHITE);
            handleFps();
        }
        renderer.endTargetRender();

        renderer.setCurrentShader((ShaderIndex) Utils::shaderIndex);
        renderer.applyShader({player.getObject().x, GetScreenHeight() - player.getObject().y});

        // removes black overlay



        

#if ENABLE_RENDERDOC

        if(RendererDebugger::isRenderDocFrameCapturing())
            RendererDebugger::endRenderDocCapture();

#endif
        drawNK();
    }   
    EndDrawing();


}

void Game::gameLoop() {

    SetTargetFPS(60);

    while(!WindowShouldClose()) {

#if DEBUG_ENABLED
        updateNK();
#endif

        handleDrawing();
        
    }

    UnloadNuklear(nk);

    CloseWindow();
}

void Game::updateGame() {

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