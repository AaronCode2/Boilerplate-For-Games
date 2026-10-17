#pragma once
#include <raylib.h>
#include <map>
#include "../utility/assets.hpp"

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

    enum class BaseType {

        NORMAL = 0,
        MARGINAL
    };

    enum class GuiType {

        CORNER_TOP_LEFT = 0,
        TOP_MIDDLE,
        CORNER_TOP_RIGHT,

        MIDDLE_LEFT_SIDE,
        MIDDLE,
        MIDDLE_RIGHT_SIDE,

        CORNER_BOTTOM_LEFT,
        BOTTOM_MIDDLE,
        CORNER_BOTTOM_RIGHT,

        SMALL_BUTTON_UNPRESSED,
        SMALL_BUTTON_PRESSED,

        LARGE_BUTTON_UNPRESSED,
        LARGE_BUTTON_PRESSED,

        MAR_CORNER_TOP_LEFT,
        MAR_TOP_MIDDLE,
        MAR_CORNER_TOP_RIGHT,

        MAR_MIDDLE_LEFT_SIDE,
        MAR_MIDDLE,
        MAR_MIDDLE_RIGHT_SIDE,

        MAR_CORNER_BOTTOM_LEFT,
        MAR_BOTTOM_MIDDLE,
        MAR_CORNER_BOTTOM_RIGHT,

        XL_BUTTON_UNPRESSED,
        XL_BUTTON_PRESSED,

        XL_ORANGE_BUTTON_UNPRESSED,
        XL_ORANGE_BUTTON_PRESSED
    };

    // There's no private members in namespaces

    extern std::map<GuiType, FrameArea> _guiMapping;

    void init();

    void _mapGui();

    void drawBases(const Vector2 position, const Vector2 size, const BaseType type = BaseType::NORMAL);

    void drawSingleBase(const Vector2 position, GuiType type);

    Rectangle _configureBaseSrcRect(const Vector2 posFrame, Vector2 size, const BaseType type = BaseType::NORMAL);

    Rectangle _getGuiSrcRect(const GuiType type);

    // A struct is a class, I use structs for simple data types

    class Button {

        public:

            Button(GuiType buttonType = GuiType::SMALL_BUTTON_UNPRESSED);

            void update(const Vector2 position);

            bool active = false;
            bool getState(const Button_State wantedState);

        private:

            void draw();
            void handleStates();

            GuiType buttonType;

            Rectangle srcRect;
            Rectangle object;
    };
}