#include "App.hpp"
#if DEBUG_ENABLED
    #define RAYLIB_NUKLEAR_IMPLEMENTATION
    #include "raylib-nuklear.h"
#endif

// I love Programing! Yeah 

void App::launch() {

    setup();

    Game game;
    game.run();
}

void App::setup() {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1440, 730, "Unamed Game");
    Image favicon = LoadImage("../assets/icon/favicon.png");

    // Sometimes it doesn't work don't know why?
    SetWindowIcon(favicon); 
    
    SetWindowState(FLAG_WINDOW_MAXIMIZED);
    
    SetTargetFPS(60);
    logInfo();
    InitAudioDevice();
    
    UnloadImage(favicon);

    AssetsLoader::load();
    UI::init();
}

void App::logInfo() {

#if DEBUG_ENABLED

    std::cout 
        << "\033[31mDo not close this window instead please close the other window which has the Game Context\n"
        << "If you find a bug or have a issue with the game please go and report an Issue\n"
        << "If you find that this game has contains malware you can send a report on gitHub\n"
        << "As from the Developer of this game: The game uses no information needed for the user\n"
        << "It is safe to say that the autosaving system will not use any personal data and is needed to run the game\n"
        << "Thank you for playing my game if you want to the 'how to play' go itch.io or gitHub :) \n\033[0m";
#endif

}
