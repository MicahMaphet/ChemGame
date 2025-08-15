#include "item_data.h"

ItemData::ItemData(string fileName, string name) : name(name) {
    int imageFilePeriod = fileName.find_last_of(".");
    width = height = 100;
    image = LoadTexture(fileName.c_str());

    highlightedImage = LoadTexture(
        (fileName.substr(0, imageFilePeriod) + "Highlighted" +
         fileName.substr(imageFilePeriod, fileName.length())).c_str());
}

ItemData::ItemData() : ItemData("", "noitem") {}

Dimentions ItemData::GetDims() {
    return {width, height};
}