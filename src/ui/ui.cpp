#include "ui.hpp"

std::map<UI::GuiType, UI::FrameArea> UI::_guiMapping;

// When I grow old, I'm gonna go to California for holiday.


void UI::init() {

    _mapGui();
}

void UI::_mapGui() {

    _guiMapping[GuiType::CORNER_TOP_LEFT] = {0, 0};
    _guiMapping[GuiType::TOP_MIDDLE] = {1, 0};
    _guiMapping[GuiType::CORNER_TOP_RIGHT] = {2, 0};

    _guiMapping[GuiType::MIDDLE_LEFT_SIDE] = {0, 1};
    _guiMapping[GuiType::MIDDLE] = {1, 1};
    _guiMapping[GuiType::MIDDLE_RIGHT_SIDE] = {2, 1};

    _guiMapping[GuiType::CORNER_BOTTOM_LEFT] = {0, 2};
    _guiMapping[GuiType::BOTTOM_MIDDLE] = {1, 2};
    _guiMapping[GuiType::CORNER_BOTTOM_RIGHT] = {2, 2};

    _guiMapping[GuiType::SMALL_BUTTON_UNPRESSED] = {0, 3};
    _guiMapping[GuiType::SMALL_BUTTON_PRESSED] = {1, 3};

    _guiMapping[GuiType::LARGE_BUTTON_UNPRESSED] = {0, 4, 2, 1};
    _guiMapping[GuiType::LARGE_BUTTON_PRESSED] = {2, 4, 2, 1};

    _guiMapping[GuiType::MAR_CORNER_TOP_LEFT] = {0, 5};
    _guiMapping[GuiType::MAR_TOP_MIDDLE] = {1, 5};
    _guiMapping[GuiType::MAR_CORNER_TOP_RIGHT] = {2, 5};

    _guiMapping[GuiType::MAR_MIDDLE_LEFT_SIDE] = {0, 6};
    _guiMapping[GuiType::MAR_MIDDLE] = {1, 6};
    _guiMapping[GuiType::MAR_MIDDLE_RIGHT_SIDE] = {2, 6};

    _guiMapping[GuiType::MAR_CORNER_BOTTOM_LEFT] = {0, 7};
    _guiMapping[GuiType::MAR_BOTTOM_MIDDLE] = {1, 7};
    _guiMapping[GuiType::MAR_CORNER_BOTTOM_RIGHT] = {2, 7};

    _guiMapping[GuiType::XL_BUTTON_UNPRESSED] = {0, 8, 3, 1},
    _guiMapping[GuiType::XL_BUTTON_PRESSED] = {3, 8, 3, 1},

    _guiMapping[GuiType::XL_ORANGE_BUTTON_UNPRESSED] = {0, 9, 3, 1};
    _guiMapping[GuiType::XL_ORANGE_BUTTON_PRESSED] = {3, 9, 3, 1};
}

void UI::drawBases(const Vector2 position, const Vector2 size, const BaseType type) {

    // Just empty, nothing to do, don't know what to do, kinda lost you know?

    for(float y = 0; y < size.y; y++) {
        for(float x = 0; x < size.x; x++) {

            const Vector2 singleBasePos = Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize() 
            * (Vector2) {x, y} + position;

            DrawTextureRec(
                Textures::texture[ImageIndex::GUI_PLATE].texture,
                _configureBaseSrcRect({x, y}, size),
                singleBasePos,
                WHITE
            );
        }
    }
}

void UI::drawSingleBase(const Vector2 position, const GuiType type) {

    DrawTextureRec(
        Textures::texture[ImageIndex::GUI_PLATE].texture,
        _getGuiSrcRect(type), position,
        WHITE
    );
}

Rectangle UI::_configureBaseSrcRect(const Vector2 posFrame, const Vector2 size, const BaseType type) {
    

    ////  Get srcRect working & redsign button with that
    //// Get the bases working!

    // Some very good coding.

    if(type == BaseType::NORMAL) {

        if(posFrame.y == 0 && posFrame.x != 0 && posFrame.x != size.x - 1)
            return _getGuiSrcRect(GuiType::TOP_MIDDLE);
        else if(posFrame.y == 0 && posFrame.x == size.x - 1)
            return _getGuiSrcRect(GuiType::CORNER_TOP_RIGHT);
        else if(posFrame.y != 0 && posFrame.x == 0 && posFrame.y != size.y - 1)
            return _getGuiSrcRect(GuiType::MIDDLE_LEFT_SIDE);
        else if(posFrame.y != 0 && posFrame.x != 0 && posFrame.y != size.y - 1 && posFrame.x != size.x - 1)
            return _getGuiSrcRect(GuiType::MIDDLE);
        else if(posFrame.y != 0 && posFrame.y != size.y - 1 && posFrame.x == size.x - 1)
            return _getGuiSrcRect(GuiType::MIDDLE_RIGHT_SIDE);
        else if(posFrame.y == size.y - 1 && posFrame.x == 0)
            return _getGuiSrcRect(GuiType::CORNER_BOTTOM_LEFT);
        else if(posFrame.y == size.y - 1 && posFrame.x != 0 && posFrame.x != size.x - 1)
            return _getGuiSrcRect(GuiType::BOTTOM_MIDDLE);

        else if(posFrame.y == size.y - 1 && posFrame.x == size.x - 1)
            return _getGuiSrcRect(GuiType::CORNER_BOTTOM_RIGHT);

        return _getGuiSrcRect(GuiType::CORNER_TOP_LEFT);
    } else {

        if(posFrame.y == 0 && posFrame.x != 0 && posFrame.x != size.x - 1)
            return _getGuiSrcRect(GuiType::MAR_TOP_MIDDLE);
        else if(posFrame.y == 0 && posFrame.x == size.x - 1)
            return _getGuiSrcRect(GuiType::MAR_CORNER_TOP_RIGHT);
        else if(posFrame.y != 0 && posFrame.x == 0 && posFrame.y != size.y - 1)
            return _getGuiSrcRect(GuiType::MAR_MIDDLE_LEFT_SIDE);
        else if(posFrame.y != 0 && posFrame.x != 0 && posFrame.y != size.y - 1 && posFrame.x != size.x - 1)
            return _getGuiSrcRect(GuiType::MAR_MIDDLE);
        else if(posFrame.y != 0 && posFrame.y != size.y - 1 && posFrame.x == size.x - 1)
            return _getGuiSrcRect(GuiType::MAR_MIDDLE_RIGHT_SIDE);
        else if(posFrame.y == size.y - 1 && posFrame.x == 0)
            return _getGuiSrcRect(GuiType::MAR_CORNER_BOTTOM_LEFT);
        else if(posFrame.y == size.y - 1 && posFrame.x != 0 && posFrame.x != size.x - 1)
            return _getGuiSrcRect(GuiType::MAR_BOTTOM_MIDDLE);

        else if(posFrame.y == size.y - 1 && posFrame.x == size.x - 1)
            return _getGuiSrcRect(GuiType::MAR_CORNER_BOTTOM_RIGHT);

        return _getGuiSrcRect(GuiType::MAR_CORNER_TOP_LEFT);
    }
}

Rectangle UI::_getGuiSrcRect(const GuiType type) {

    return {
        Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().x * _guiMapping[type].x,
        Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().y * _guiMapping[type].y,
        Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().x * _guiMapping[type].width,
        Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().y * _guiMapping[type].height
    };
}

UI::Button::Button(GuiType buttonType) {

    this->buttonType = buttonType;

    srcRect = _getGuiSrcRect(buttonType);
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

bool UI::Button::getState(const Button_State wantedState) {

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
        _guiMapping[(GuiType) (1 + (int) buttonType)].x;

        srcRect.y = Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().y * 
        _guiMapping[(GuiType) (1 + (int) buttonType)].y;
    } else {

        srcRect.x = Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().x * 
        _guiMapping[(GuiType) (buttonType)].x;

        srcRect.y = Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().y * 
        _guiMapping[(GuiType) (buttonType)].y;
    }
}
