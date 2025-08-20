#pragma once

#include <raylib.h>
#include <string>
#include "util.h"
using std::string;

class ItemData {
public:
    ItemData(string fileName, string name, string label="");
    ItemData();
    Dimentions GetDims();
    int width, height;
    string name;
    Texture2D image;
    Texture2D highlightedImage;
};