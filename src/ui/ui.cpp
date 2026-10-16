#include <ui.hpp>

std::map<UI::Button_Type, UI::FrameArea> UI::_buttonMapping;

// When I grow old, I'm gonna go to California for holiday.

enum class UI::Button_Type {

    SMALL_BUTTON_UNACTIVE = 0,
    SMALL_BUTTON_ACTIVE,
    LARGE_BUTTON_UNACTIVE,
    LARGE_BUTTON_ACTIVE,
    XL_LARGE_BUTTON_UNACTIVE,
    XL_LARGE_BUTTON_ACTIVE,
};

enum class UI::Button_State {

    INACTIVE = 0,
    MOUSE_HOVER,
    MOUSE_L_CLICKED,
    MOUSE_R_CLICKED
};

void UI::init() {

    UI::_buttonMapping[UI::Button_Type::SMALL_BUTTON_UNACTIVE] = {0, 3, 1, 1};
    UI::_buttonMapping[UI::Button_Type::SMALL_BUTTON_ACTIVE] = {1, 3, 1, 1};
    
    UI::_buttonMapping[UI::Button_Type::LARGE_BUTTON_UNACTIVE] = {0, 4, 2, 1};
    UI::_buttonMapping[UI::Button_Type::LARGE_BUTTON_ACTIVE] = {1, 4, 2, 1};
    
    UI::_buttonMapping[UI::Button_Type::XL_LARGE_BUTTON_UNACTIVE] = {0, 8, 3, 1};
    UI::_buttonMapping[UI::Button_Type::XL_LARGE_BUTTON_ACTIVE] = {1, 8, 3, 1};
}

UI::Button::Button(Button_Type buttonType, Button_State activeState) {

    this->buttonType = buttonType;
    this->activeState = activeState;

    srcRect = {
        Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().x * _buttonMapping[buttonType].x,
        Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().y * _buttonMapping[buttonType].y,
        Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().x,
        Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().y
    };
}

void UI::Button::update(const Vector2 position) {

    object = {
        position.x,
        position.y,
        srcRect.width,
        srcRect.height
    };

    draw();
}

UI::Button_State UI::Button::getState() {

    if(Mouse::isClickedL(object))
        return Button_State::MOUSE_L_CLICKED;
    
    if(Mouse::isClickedR(object))
        return Button_State::MOUSE_R_CLICKED;

    if(Mouse::isHovering(object))
        return Button_State::MOUSE_HOVER;

    return Button_State::INACTIVE;
}

void UI::Button::draw() {

    DrawTextureRec(
        Textures::texture[ImageIndex::GUI_PLATE].texture,
        srcRect, {object.x, object.y},
        WHITE
    );
}
