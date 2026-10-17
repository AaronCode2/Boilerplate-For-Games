#pragma once
#include "sprite.hpp"
#include "../utility/utils.hpp"
#include "../utility/assets.hpp"
#include "tile.hpp"
#include <raylib.h>
#include <vector>
#include <math.h>

class Player : public Sprite {


    public:

        Player(Rectangle object, std::vector<Tile> &tiles);

        void update();

        Vector2 getVelocity() const { return velocity; };
        Vector2 getCameraMovement() const { return cameraMovement; };

        Rectangle &getObject_r() { return object; };
        Rectangle getObject() { return object; };

    private:

        void draw();
        void move();
        void handleAnimation();
        void handleFraming();
        void addressInput();
        void handleDirection();

        void applyGravity();
        void updateHitBox();
        
        void collisionX();
        void collisionY();

        void moveCameraX();
        void moveCameraY();
        void updateCamera();

        Dir direction = Dir::RIGHT;
        PlayerAnimState state = PlayerAnimState::IDLE;

        std::vector<Tile> &tiles;

        Rectangle cameraBox;
        Rectangle hitBox;

        Vector2 cameraMovement = {0, 0};
};