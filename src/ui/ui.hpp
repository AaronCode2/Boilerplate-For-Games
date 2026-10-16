#pragma once
#include <raylib.h>
#include <map>
#include "../utility/textures.hpp"

namespace UI {


    struct FrameArea {
        
        int x;
        int y;
        int width = 1;
        int height = 1;
    };

    enum class Button_State;
    enum class Button_Type;

    // There's no private members in namespaces

    std::map<Button_Type, FrameArea> _buttonMapping;

    void init();

    // A struct is a class, I use structs for simple data types

    class Button {

        public:

            Button(Button_Type buttonType = Button_Type::SMALL_BUTTON_ACTIVE, Button_State activeState);

            void update(const Vector2 position);

            Button_State getState();

        private:

            void draw();

            Button_Type buttonType;
            Button_State activeState;

            Rectangle srcRect;
            Rectangle object;
    };
}