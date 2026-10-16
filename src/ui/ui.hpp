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

    enum class Button_State {

        INACTIVE = 0,
        MOUSE_HOVER,
        MOUSE_L_CLICKED,
        MOUSE_R_CLICKED
    };

    enum class Button_Type {

        SMALL_BUTTON_UNACTIVE = 0,
        SMALL_BUTTON_ACTIVE,
        LARGE_BUTTON_UNACTIVE,
        LARGE_BUTTON_ACTIVE,
        XL_LARGE_BUTTON_UNACTIVE,
        XL_LARGE_BUTTON_ACTIVE,
    };

    // There's no private members in namespaces

    extern std::map<Button_Type, FrameArea> _buttonMapping;

    void init();

    // A struct is a class, I use structs for simple data types

    class Button {

        public:

            Button(Button_Type buttonType = Button_Type::SMALL_BUTTON_UNACTIVE);

            void update(const Vector2 position);

            bool active = false;
            bool getState(Button_State wantedState);

        private:

            void draw();
            void handleStates();

            Button_Type buttonType;

            Rectangle srcRect;
            Rectangle object;
    };
}