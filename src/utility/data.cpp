#include "data.hpp"

Data::Data(std::vector<Tile> &tiles, Rectangle &playerObject, Vector2 &worldPos): 
    tiles(tiles), playerObject(playerObject), worldPos(worldPos)    
{

    // Using camelCase for json files, please do not mess it up

    dataMap[DataMapIndex::DEV_MAP] = "devMap";
    dataMap[DataMapIndex::MAP_1] = "map1";
    dataMap[DataMapIndex::MAP_2] = "map1";

}

void Data::writeData(DataMapIndex mapIndex) {

    const std::string mapName = dataMap[mapIndex];

    data[mapName]["playerPos"] = {

        {"x", std::floorf(playerObject.x)},
        {"y", std::floorf(playerObject.y)}
    };

    data[mapName]["worldPos"] = {

        {"x", std::floorf(worldPos.x)},
        {"y", std::floorf(worldPos.y)}
    };

    for(const auto tile : tiles) {

        Rectangle tileObject = tile.getObject();

        data[mapName]["tiles"].push_back(
            {
                {
                    "position", {
                        {"x", std::floorf(tileObject.x)}, 
                        {"y", std::floorf(tileObject.y)}
                    },
                },
                {
                    "type", tile.getType()
                }
            }
        );
    }

    std::ofstream file(DATA_PATH);

    // Did this for read-ablity, set JSON_INDENT to -1, for speed when building to release

    file << data.dump(JSON_INDENT);

    file.close();
}

void Data::readData(DataMapIndex mapIndex) {

    const std::string mapName = dataMap[mapIndex];

    std::ifstream file(DATA_PATH);

    Json data = Json::parse(file);

    playerObject.x = data[mapName]["playerPos"]["x"];
    playerObject.y = data[mapName]["playerPos"]["y"];

    worldPos = {data[mapName]["worldPos"]["x"], data[mapName]["worldPos"]["y"]}; 

    // Notch's post are kinda sad, he is getting a bit lost.

    for(Json::iterator it = data[mapName]["tiles"].begin(); it != data[mapName]["tiles"].end(); it++) {

        Json tiledata = *it;

        tiles.push_back(
            Tile(
                {tiledata["position"]["x"], tiledata["position"]["y"]},
                tiledata["type"]
            )
        );
    }
}
