#include "player.hpp"

Player::Player(Rectangle object, std::vector<Tile> &tiles):
    Sprite(object, ImageIndex::PLAYER), tiles(tiles)     
{

    object.width = srcRect.width;
    object.height = srcRect.height;
}

void Player::update() {
    
    addressInput();
    applyGravity();
    move();

    draw();
}

void Player::draw() {

    
    handleAnimation();

    DrawTextureRec(
        Textures::texture[ImageIndex::PLAYER].texture,
        srcRect, 
        {object.x, object.y},
        WHITE
    );

}

void Player::move() {

    updateCamera();

    object.x += velocity.x * GetFrameTime();

    if(!Utils::hackerMode)
        collisionX();
    moveCameraX();

    object.y += velocity.y  * GetFrameTime();

    if(!Utils::hackerMode)
        collisionY();
    moveCameraY();
}

void Player::handleAnimation() {

    // My python is against me

    if(velocity.x == 0) {

        if(state != PlayerAnimState::IDLE) {

            state = PlayerAnimState::IDLE;
            currentFrame = 0;
            srcRect.y = 0;
        }
        
        handleDirection();
        animate(PLAYER_IDLE_MAX_FRAMES, PLAYER_IDLE_FRAME_DURATION);
        handleFraming();
    } else {        

        if(state != PlayerAnimState::WALK) {

            state = PlayerAnimState::WALK;
            currentFrame = 0;
            srcRect.y = srcRect.height;
        }

        handleDirection();
        handleFraming();
        animate(PLAYER_WALK_MAX_FRAMES, PLAYER_WALK_FRAME_DURATION);
    }
}

void Player::handleFraming() {

    if(direction == Dir::RIGHT)
        srcRect.x = srcRect.width * currentFrame;
    else
        srcRect.x = srcRect.width * (IMAGE_PLAYER_MAX_FRAMES.x - currentFrame);
}

void Player::addressInput() {

    cameraMovement = {0, 0};
    velocity.x = 0;

    if(Utils::hackerMode)
        velocity.y = 0;

    if(getInput().goingLeft)
        velocity.x = -PLAYER_SPEED;
    if(getInput().goingRight)
        velocity.x = PLAYER_SPEED;

    if(getInput().isJumping && !Utils::hackerMode)
        velocity.y = PLAYER_JUMP_SPEED;

    if(IsKeyDown(KEY_W) && Utils::hackerMode)
        velocity.y = -PLAYER_SPEED;

    if(IsKeyDown(KEY_S) && Utils::hackerMode)
        velocity.y = PLAYER_SPEED;
}

void Player::handleDirection() {

    if(velocity.x < 0 && direction == Dir::RIGHT) {

        direction = Dir::LEFT;
        srcRect.width = -srcRect.width;
    } else if(velocity.x > 0 && direction == Dir::LEFT) {

        direction = Dir::RIGHT;
        srcRect.width = abs(srcRect.width);
    }
}

void Player::applyGravity() {

    if(Utils::hackerMode)
        return;

    if(object.y + object.height <= GetScreenHeight() - 100)
        velocity.y += GRAVITY * GetFrameTime();
    else
        velocity.y = 0;
}

void Player::updateHitBox() {

    hitBox = {

        object.x + PLAYER_HITBOX_ADJ.x,
        object.y + PLAYER_HITBOX_ADJ.y,
        object.width + PLAYER_HITBOX_ADJ.width,
        object.height + PLAYER_HITBOX_ADJ.height,   
    };

    // Utils::debugRect(hitBox);
}

void Player::collisionX() {

    updateHitBox();

    for(auto &tile : tiles) {

        if(CheckCollisionRecs(hitBox, tile.getHitBox())) {
            
            if(velocity.x > 0) {
                
                const float offset = hitBox.x - object.x + hitBox.width;
                
                object.x = tile.getHitBox().x - offset - COL_ADJUST;
            }
            
            if(velocity.x < 0) {
                
                const float offset = hitBox.x - object.x;
                
                object.x = tile.getHitBox().x + tile.getHitBox().width - offset + COL_ADJUST;
            }

            velocity.x = 0;
        }
    }
}

void Player::collisionY() {

    updateHitBox();

    for(auto &tile : tiles) {

        if(CheckCollisionRecs(hitBox, tile.getHitBox())) {

            if(velocity.y > 0) {
                
                velocity.y = 0;
                
                const float offset = hitBox.y - object.y + hitBox.height;
                
                object.y = tile.getHitBox().y - offset - COL_ADJUST;
            }

            if(velocity.y < 0) {

                velocity.y = 0;

                const float offset = hitBox.y - object.y;

                object.y = tile.getHitBox().y + tile.getHitBox().height - offset + COL_ADJUST;
            }
        }
    }
}

void Player::moveCameraX() {  

    updateHitBox();

    if(hitBox.x + hitBox.width >= cameraBox.x + cameraBox.width && velocity.x >= 0) {

        cameraMovement.x = -velocity.x;

        const float offset = hitBox.x - object.x + hitBox.width; 
        object.x = cameraBox.x + cameraBox.width - offset;
    }

    if(hitBox.x <= cameraBox.x && velocity.x <= 0) {

        cameraMovement.x = -velocity.x;

        const float offset = hitBox.x - object.x;
        object.x = cameraBox.x - offset;
    }

    updateHitBox();
}

void Player::moveCameraY() {

    updateHitBox();

    if(hitBox.y + hitBox.height >= cameraBox.y + cameraBox.height && velocity.y >= 0) {

        cameraMovement.y = -velocity.y;
        
        const float offset = hitBox.y - object.y + hitBox.height; 
        object.y = cameraBox.y + cameraBox.height - offset;
    }

    if(hitBox.y <= cameraBox.y && velocity.y <= 0) {

        cameraMovement.y = -velocity.y;
        
        const float offset = hitBox.y - object.y;
        object.y = cameraBox.y - offset;
    }

    updateHitBox();
}

// Life got a bit dull, coding is the only happiness I get nower days :(

void Player::updateCamera() {

    cameraBox = {

        CAMERA_BOX_ADJ.x,
        CAMERA_BOX_ADJ.y,
        GetScreenWidth() - CAMERA_BOX_ADJ.width,
        GetScreenHeight() - CAMERA_BOX_ADJ.height,
    };

    // Utils::debugRect(cameraBox);
}