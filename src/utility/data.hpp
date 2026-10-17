#pragma once
#include <raylib.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>
#include <math.h>
#include <map>
#include <string>
#include "../entity_classes/tile.hpp"
#include "../utility/utils.hpp"

// Using thirdparty lib called json for data, README: [https://github.com/nlohmann/json]

using Json = nlohmann::json;

enum class DataMapIndex {

    DEV_MAP = -1,
    MAP_1 = 0,
    MAP_2,
};

class Data {

    public:

        Data(std::vector<Tile> &tiles, Rectangle &playerObject, Vector2 &worldPos);

        void writeData(DataMapIndex mapIndex);
        void readData(DataMapIndex mapIndex);

    private:

        Json data;

        std::vector<Tile> &tiles;
        Rectangle &playerObject;
        Vector2 &worldPos;

        std::map<DataMapIndex, std::string> dataMap;
};