#pragma once
#include <raylib.h>
#include "../utility/utils.hpp"
#include "../utility/assets.hpp"

class Sprite {

    public:

        Sprite(Rectangle object, ImageIndex index);

        void update();

        Rectangle getObject() const { return object; };



        Rectangle getSrcRect() const { return srcRect; };
        
    protected:
        
        Rectangle object;
        Vector2 velocity = {0, 0};
        Rectangle srcRect;

        void draw(Texture2D image = Textures::texture[ImageIndex::PLAYER].texture);
        void animate(const int frameEnd = 6, const float frameDuration = 0.1f, const int frameStart = 0);

        int currentFrame = 0;
        float elapsedFrame = 0;
};