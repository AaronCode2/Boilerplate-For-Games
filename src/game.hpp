#pragma once
#include <iostream>
#include <cstddef>
#include <memory>
#include <raylib.h>
#include "utility/global_vars.hpp"
#include "entity_classes/sprite.hpp"
#include "entity_classes/player.hpp"
#include "utility/assets.hpp"
#include "utility/data.hpp"
#include "manager_classes/world.hpp"
#include "ui/ui.hpp"

#if DEBUG_ENABLED
    #include "raylib-nuklear.h"
#endif

class Game {

    public:

        Game();
        ~Game();

        void run() { gameLoop(); };

    private:

        Color backgroundColor = {100, 100, 100, 155};

        World world = World();
        Player player = Player({500, 300, 100, 100}, world.giveTiles());
        UI::Button button;

        Data data = Data(world.giveTiles(), player.getObject_r(), world.getWorldPos_r());

        Texture2D classicImage = LoadTexture("../assets/example/circle.png");

        RenderTexture2D targetBuffer;

        RenderTexture2D renderbuffers[NUM_OF_FRAME_BUFFERS];
        
        void initRenderBuffers();

        void drawTargetBuffer();
        void handleChainBuffers();

        void gameLoop();
        void updateGame();
        void handleFps();

    // thirdparty lib

#if DEBUG_ENABLED
        struct nk_context *nk = InitNuklear(FONT_SIZE_FOR_NUK);

        void updateNK();
        void drawNK();

#endif


};