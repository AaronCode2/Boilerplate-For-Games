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

void UI::drawBase(Vector2 position, Vector2 size, BaseType type) {


}

void UI::_configureBaseSelection(Vector2 posFrame, Vector2 size, BaseType type) {
    

    // TODO: Get srcRect working & redsign button with that
    // TODO 2: Get the bases working!

    // if(type == BaseType::NORMAL) {
    //     if(posFrame.y == 0 && posFrame.x != 0 && posFrame.x != size.x - 1)
    //         return getGuiPlatesSrcRect(utils.GuiPlates.TOP_MIDDLE)
    //     elif(posFrame.y == 0 && posFrame.x == size.x - 1)
    //         return getGuiPlatesSrcRect(utils.GuiPlates.CORNER_TOP_RIGHT)
    //     elif(posFrame.y != 0 && posFrame.x == 0 && y != size.y - 1)
    //         return getGuiPlatesSrcRect(utils.GuiPlates.MIDDLE_LEFT_SIDE)
    //     elif(posFrame.y != 0 && posFrame.x != 0 && y != size.y - 1 && posFrame.x != size.x - 1)
    //         return getGuiPlatesSrcRect(utils.GuiPlates.MIDDLE)
    //     elif(posFrame.y != 0 && y != size.y - 1 && posFrame.x == size.x - 1)
    //         return getGuiPlatesSrcRect(utils.GuiPlates.MIDDLE_RIGHT_SIDE)
    //     elif(posFrame.y == size.y - 1 && posFrame.x == 0)
    //         return getGuiPlatesSrcRect(utils.GuiPlates.CORNER_BOTTOM_LEFT)
    //     elif(posFrame.y == size.y - 1 && posFrame.x != 0 && posFrame.x != size.x - 1)
    //         return getGuiPlatesSrcRect(utils.GuiPlates.BOTTOM_MIDDLE)

    //     elif(posFrame.y == size.y - 1 && posFrame.x == size.x - 1)
    //         return getGuiPlatesSrcRect(utils.GuiPlates.CORNER_BOTTOM_RIGHT)

    //     return getGuiPlatesSrcRect(utils.GuiPlates.CORNER_TOP_LEFT)
    // } else {

    //     if(posFrame.y == 0 && posFrame.x != 0 && posFrame.x != size.x - 1)
    //         return getGuiPlatesSrcRect(utils.GuiPlates.MAR_TOP_MIDDLE)
    //     elif(posFrame.y == 0 && posFrame.x == size.x - 1)
    //         return getGuiPlatesSrcRect(utils.GuiPlates.MAR_CORNER_TOP_RIGHT)
    //     elif(posFrame.y != 0 && posFrame.x == 0 && y != size.y - 1)
    //         return getGuiPlatesSrcRect(utils.GuiPlates.MAR_MIDDLE_LEFT_SIDE)
    //     elif(posFrame.y != 0 && posFrame.x != 0 && y != size.y - 1 && posFrame.x != size.x - 1)
    //         return getGuiPlatesSrcRect(utils.GuiPlates.MAR_MIDDLE)
    //     elif(posFrame.y != 0 && y != size.y - 1 && posFrame.x == size.x - 1)
    //         return getGuiPlatesSrcRect(utils.GuiPlates.MAR_MIDDLE_RIGHT_SIDE)
    //     elif(posFrame.y == size.y - 1 && posFrame.x == 0)
    //         return getGuiPlatesSrcRect(utils.GuiPlates.MAR_CORNER_BOTTOM_LEFT)
    //     elif(posFrame.y == size.y - 1 && posFrame.x != 0 && posFrame.x != size.x - 1)
    //         return getGuiPlatesSrcRect(utils.GuiPlates.MAR_BOTTOM_MIDDLE)

    //     elif(posFrame.y == size.y - 1 && posFrame.x == size.x - 1)
    //         return getGuiPlatesSrcRect(utils.GuiPlates.MAR_CORNER_BOTTOM_RIGHT)

    //     return getGuiPlatesSrcRect(utils.GuiPlates.MAR_CORNER_TOP_LEFT)
    // }
}

UI::Button::Button(GuiType buttonType) {

    this->buttonType = buttonType;

    srcRect = {
        Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().x * _guiMapping[buttonType].x,
        Textures::texture[ImageIndex::GUI_PLATE].GetFrameSize().y * _guiMapping[buttonType].y,
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
