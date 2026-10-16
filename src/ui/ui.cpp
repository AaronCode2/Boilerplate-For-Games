#include "ui.hpp"

std::map<UI::Button_Type, UI::FrameArea> UI::_buttonMapping;

// When I grow old, I'm gonna go to California for holiday.

void UI::init() {

    UI::_buttonMapping[UI::Button_Type::SMALL_BUTTON_UNACTIVE] = {0, 3};
    UI::_buttonMapping[UI::Button_Type::SMALL_BUTTON_ACTIVE] = {1, 3};
    
    UI::_buttonMapping[UI::Button_Type::LARGE_BUTTON_UNACTIVE] = {0, 4, 2, 1};
    UI::_buttonMapping[UI::Button_Type::LARGE_BUTTON_ACTIVE] = {1, 4, 2, 1};
    
    UI::_buttonMapping[UI::Button_Type::XL_LARGE_BUTTON_UNACTIVE] = {0, 8, 3, 1};
    UI::_buttonMapping[UI::Button_Type::XL_LARGE_BUTTON_ACTIVE] = {1, 8, 3, 1};
}

UI::Button::Button(Button_Type buttonType) {

    this->buttonType = buttonType;

    srcRect = {
        Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().x * _buttonMapping[buttonType].x,
        Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().y * _buttonMapping[buttonType].y,
        Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().x,
        Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().y
    };
}

void UI::Button::update(const Vector2 position) {

    handleStates();

    object = {
        position.x,
        position.y,
        srcRect.width,
        srcRect.height
    };

    draw();
}

bool UI::Button::getState(Button_State wantedState) {

    switch(wantedState) {

        case UI::Button_State::MOUSE_L_CLICKED:
            return Mouse::isClickedL(object);
        
        case UI::Button_State::MOUSE_R_CLICKED:
            return Mouse::isClickedR(object);
        
        case UI::Button_State::MOUSE_HOVER:
            return Mouse::isHovering(object);
    };

    return false;
}

void UI::Button::draw() {

    DrawTextureRec(
        Textures::texture[ImageIndex::GUI_PLATE].texture,
        srcRect, {object.x, object.y},
        WHITE
    );
}

void UI::Button::handleStates() {

    if(active) {

        srcRect.x = Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().x * 
        _buttonMapping[(Button_Type) (1 + (int) buttonType)].x;

        srcRect.y = Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().y * 
        _buttonMapping[(Button_Type) (1 + (int) buttonType)].y;
    } else {

        srcRect.x = Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().x * 
        _buttonMapping[(Button_Type) (buttonType)].x;

        srcRect.y = Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().y * 
        _buttonMapping[(Button_Type) (buttonType)].y;
    }
}
