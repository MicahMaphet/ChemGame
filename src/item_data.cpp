#include "item_data.h"

ItemData::ItemData(string fileName, string name, string label) : name(name) {
    int imageFilePeriod = fileName.find_last_of(".");
    width = height = 125;

    if (label.length() > 0) {
        Image img = LoadImage(fileName.c_str());
        Image highlightedImg = LoadImage(
            (fileName.substr(0, imageFilePeriod) + "Highlighted" +
            fileName.substr(imageFilePeriod, fileName.length())).c_str());

        ImageDrawTextEx(&img, GetFontDefault(), label.c_str(), Vector2{5.0f, img.height/2.0f}, 8.0f, 2.0f, BLACK);
        ImageDrawTextEx(&highlightedImg, GetFontDefault(), label.c_str(), Vector2{5.0f, img.height/2.0f}, 8.0f, 2.0f, BLACK);

        image = LoadTextureFromImage(img);
        highlightedImage = LoadTextureFromImage(highlightedImg);

        UnloadImage(img);
        UnloadImage(highlightedImg);
    } else {
        image = LoadTexture(fileName.c_str());
        highlightedImage = LoadTexture(
            (fileName.substr(0, imageFilePeriod) + "Highlighted" +
            fileName.substr(imageFilePeriod, fileName.length())).c_str());
    }
}

ItemData::ItemData() : ItemData("", "noitem") {}

Dimentions ItemData::GetDims() {
    return {width, height};
}