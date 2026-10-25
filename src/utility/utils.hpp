#pragma once
#include <raylib.h>
#include <iostream>
#include <fstream>

#define print(x) std::cout << x << '\n'
#define EMPTY_RECT (Rectangle) {0, 0, 0, 0}
#define WH_EMPTY_RECT (Rectangle) {0, 0, TILE_SIZE, TILE_SIZE}

#define SAVY_YELLOW (Color) {255, 209, 157, 255}
#define MOUSE_BROWN (Color) {163, 90, 66, 255}
#define SAVY_BROWN (Color) {215, 147, 106, 255}
#define DARK_BROWN (Color) {181, 108, 78, 255}

#define FONT_SIZE 30
#define FONT_SPACING 1
#define SLOT_SIZE 120

#define STACK_SIZE 255

// 200 Tiles -> World Size

#define WORLD_SIZE 200

// Some C++ operator magic

inline Vector2 operator<<=(Vector2 &v1, const Vector2 &v2) {

    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

inline Vector2 operator*(Vector2 vec, const float numf) {

    vec.x *= numf;
    vec.y *= numf;
    return vec;
}

inline Vector2 operator*(Vector2 vec1, Vector2 vec2) {

    vec1.x *= vec2.x;
    vec1.y *= vec2.y;
    return vec1;
}

inline Vector2 operator+(Vector2 vec1, Vector2 vec2) {

    vec1.x += vec2.x;
    vec1.y += vec2.y;
    return vec1;
}

inline Vector2 operator>>=(Vector2 &v1, const Vector2 &v2) {

    v1.x -= v2.x;
    v1.y -= v2.y;
    return v1;
}

// I wanna do something else than coding, It really is a concern. 

inline bool operator!=(const Vector2 &v1, const Vector2 &v2) {

    return (v1.x != v2.x || v1.y != v2.y);
}

inline bool operator==(const Vector2 &v1, const Vector2 &v2) {

    return (v1.x == v2.x && v1.y == v2.y);
}

inline Rectangle operator<<=(Rectangle &v1, const Vector2 &v2) {

    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

struct Input {

    bool goingLeft;
    bool goingRight;
    bool isJumping;
};

Input getInput();



enum class FPS_TYPE {

   THIRTY_FPS = 0, // Can't write nums in enum!
   SIXTY_FPS,
   HUNDRED_AND_TWENTY_FPS,
   MAXFPS
};

enum class Dir {

    LEFT = 0,
    RIGHT
};

enum class PlayerAnimState {

    IDLE = 0,
    WALK
};

enum class TileType {

    WALL = 0,
    CLOCK,
    COUCH,
    STAND
};

namespace Utils {

    extern float deltaTimeIt;
    extern Color const testColor;
    Rectangle getScreenRect();
    Vector2 getScreenSizeV();

    std::string formatZeros(int num, int width);
    extern int fontSize;

    bool isSameXY(const Rectangle aObject, const Rectangle bObject);
    bool isSameXY(const Vector2 aObject, const Vector2 bObject);
    bool isSameXY(const Vector2 aObject, const Vector2 bObject, const Vector2 bObject2);
    
    void collisionActionX(Rectangle &aObject, const Rectangle ahitBox, const Rectangle bHitBox, Vector2 &aVelocity, bool resetVelocity = true);
    void collisionActionY(Rectangle &aObject, const Rectangle ahitBox, const Rectangle bHitBox, Vector2 &aVelocity, bool resetVelocity = true);
    
    void debugRect(Rectangle object);

    void exitApp(const std::string errorInfo);

    extern Font font;

    // Did this for emphasis

    extern Rectangle THE_DEBUG_RECT;
    extern Vector2 THE_DEBUG_VECTOR;
    extern int selectedtileTypeIndex;

    extern bool hackerMode;

#if DEBUG_ENABLED

    extern float xdebugingvalue;
    extern float ydebugingvalue;

    void TheDebugFunc();
#endif
} 


namespace Mouse {

    bool isHovering(const Rectangle object);
    bool isClickedL(const Rectangle object);
    bool isClickedR(const Rectangle object);

    bool isClickedOnceR(const Rectangle object);
    bool isClickedOnceL(const Rectangle object);
}

// constants

#define GUI_SCALE 2

#define MAX_AMOUNT_OF_IMAGES 2

#define IMAGE_PLAYER_PATH "../assets/player/player.png"
#define IMAGE_PLAYER_MAX_FRAMES (Vector2) {8, 2}

#define IMAGE_TILE_PATH "../assets/tiles/tile.png"
#define IMAGE_TILE_MAX_FRAMES (Vector2) {4, 1}

#define IMAGE_GUI_PLATE_PATH "../assets/ui/gui_plates.png"
#define IMAGE_GUI_PLATE_MAX_FRAMES (Vector2) {6, 10}

#define PLAYER_IDLE_FRAME_DURATION 0.1f
#define PLAYER_IDLE_MAX_FRAMES 5

#define PLAYER_WALK_FRAME_DURATION 0.09f
#define PLAYER_WALK_MAX_FRAMES 8

#define PLAYER_SPEED 500
#define PLAYER_JUMP_SPEED -1000
#define GRAVITY 1800

#define TILE_WALL_HITBOX_ADJ (Rectangle) {0, 188, 0, -190}
#define PLAYER_HITBOX_ADJ (Rectangle) {15, 10, -57, 0}
#define COL_ADJUST 0.1f
#define CAMERA_BOX_ADJ (Rectangle) {170, 268, 400, 400}

#define DATA_PATH "../data/dat.json"
#define JSON_INDENT 4

#define GREYSCALE_FRAG_PATH (const char *) "../shaders/greyscale.frag"
#define FOG_FRAG_PATH (const char *) "../shaders/fog.frag"
#define BLUR_FRAG_PATH (const char *) "../shaders/blur.frag"
#define BLOOM_FRAG_PATH (const char *) "../shaders/bloom.frag"

#define UP_SAMPLING_FRAG_PATH (const char *) "../shaders/up_sampling.frag"
#define DOWN_SAMPLING_FRAG_PATH (const char *) "../shaders/down_sampling.frag"

#define HORIZONTAL_VEC (Vector2) {1.0f, 0.0f} 
#define VERTICAL_VEC (Vector2) {0.0f, 1.0f} 

#define RAYLIB_SHADER 0

#define NUM_OF_FRAME_BUFFERS 8

#define PLAYER_LIGHT_OFFSET (Vector2) {45.0f, -45.0f}

#if DEBUG_ENABLED
    #define FONT_SIZE_FOR_NUK 20
#endif